#include <cstdio>
#include <vector>
#include <memory>
#include <thlang/thlang.h>
#include <thlang/codegen.h>
#include <thlang/node.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <lld/Common/Driver.h>
#include <lld/Common/ErrorHandler.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>



LLD_HAS_DRIVER(coff)
LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(mingw)
LLD_HAS_DRIVER(macho)
LLD_HAS_DRIVER(wasm)

std::vector<lld::DriverDef> drivers = {                                                                            
            {lld::WinLink, &lld::coff::link}, {lld::Gnu, &lld::elf::link},             
                {lld::MinGW, &lld::mingw::link}, {lld::Darwin, &lld::macho::link}, {   
            lld::Wasm, &lld::wasm::link                                              
            }                                                                          
     };

extern int yyparse(thlang::NModule &root_program, thlang::CodeGenContext &context);
extern FILE* yyin;

namespace thlang {
std::string compile_toir(const std::string& code) {
    // 创建临时文件
    FILE* temp_file = std::tmpfile();
    if (!temp_file) {
        throw std::runtime_error("Failed to create temporary file");
    }

    // 写入代码到临时文件
    std::fputs(code.c_str(), temp_file);

    // 重置文件指针到文件开头
    std::rewind(temp_file);

    // 调用 yyparse
    thlang::NModule root_module;
    thlang::CodeGenContext context;
    yyin = temp_file;
    // 假设 yyparse 接受 FILE* 类型
    yyparse(root_module, context);

    // 关闭临时文件
    std::fclose(temp_file);

    // 生成 LLVM IR
    root_module.codegen(context);

    std::string module_str;
    llvm::raw_string_ostream os(module_str);
    context.theModule->print(os, nullptr);
    os.flush();

    return module_str;
}

std::string compile_toir_from_file(const std::string& file_path) {
    // 打开文件并读取内容
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    file.close();

    // 调用现有的 compile 函数
    return compile_toir(code);
}

void compile_fir_to_asm(const std::string& llvmir,FILE* output_file){
    thlang::CodeGenContext context;
    std::unique_ptr<llvm::Module> module = parseIRFromString(context.getContext(), llvmir);
    context.theModule = std::move(module);
    context.asmgen(output_file);
}

void compile_fir_to_obj(const std::string& llvmir, FILE* output_file){
    thlang::CodeGenContext context;
    std::unique_ptr<llvm::Module> module = parseIRFromString(context.getContext(), llvmir);
    context.theModule = std::move(module);
    context.objgen(output_file);
}

std::string getDefaultLinkerName() {
    // 获取主机目标三元组
    std::string tripleStr = llvm::sys::getDefaultTargetTriple();
    llvm::Triple triple(tripleStr);
    
    // 根据操作系统判断链接器
    switch (triple.getOS()) {
        case llvm::Triple::OSType::Linux:
        case llvm::Triple::OSType::FreeBSD:
        case llvm::Triple::OSType::NetBSD:
        case llvm::Triple::OSType::OpenBSD:
            return "ld.lld";  // Unix-like 系统
            
        case llvm::Triple::OSType::Darwin:
        case llvm::Triple::OSType::MacOSX:
            return "ld64.lld"; // macOS
            
        case llvm::Triple::OSType::Win32:
            return "lld-link"; // Windows
            
        case llvm::Triple::OSType::WASI:
            return "wasm-ld"; // WebAssembly
            
        default:
            // 未知系统，默认使用 ld.lld
            return "ld.lld";
    }
}

// 自定义函数，接受命令行参数并调用LLD进行链接
bool link(const std::vector<const char*>& args) {
    std::vector<const char*> args_;
    args_.push_back(getDefaultLinkerName().c_str());
    args_.insert(args_.end(),args.begin(),args.end());
    llvm::ArrayRef<const char*> argArray(args_);
    lld::Result result = lld::lldMain(argArray, 
        llvm::outs(), 
        llvm::errs(), 
        drivers
    );
    return result.retCode == 0;
}


} // namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr) {
        std::free(ptr);
    }

    // 编译代码并返回 C 字符串
    char* compile_toir_code(const char* code) {
        try {
            std::string result = thlang::compile_toir(std::string(code));
            // 分配内存并复制字符串
            char* c_result = static_cast<char*>(std::malloc(result.size() + 1));
            std::strcpy(c_result, result.c_str());
            return c_result;
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // 从文件编译的 C 接口
    char* compile_toir_code_from_file(const char* file_path) {
        try {
            std::string result = thlang::compile_toir_from_file(std::string(file_path));
            char* c_result = static_cast<char*>(std::malloc(result.size() + 1));
            std::strcpy(c_result, result.c_str());
            return c_result;
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return nullptr;
        }
    }

    int compile_code_fir_to_asm(const char* llvmir, FILE* output_file) {
        try {
            thlang::compile_fir_to_asm(std::string(llvmir), output_file);
            return 0; // 成功
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return -1; // 失败
        }
    }

    // 新增: 将LLVM IR编译为目标文件的C接口
    int compile_code_fir_to_obj(const char* llvmir, FILE* output_file) {
        try {
            thlang::compile_fir_to_obj(std::string(llvmir), output_file);
            return 0; // 成功
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return -1; // 失败
        }
    }
}