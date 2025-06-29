#include <cstdio>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
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
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Program.h>
#include <llvm/Support/MemoryBuffer.h>


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
bool link(const std::vector<const char*>& args, std::string targetTriple) {
    // 1. 用 string 存储所有参数（避免指针失效）
    std::vector<std::string> allArgsStr;
    
    // 添加基础参数
    allArgsStr.push_back(getDefaultLinkerName());
    
    // 2. 自动检测目标平台
    if (targetTriple.empty()) {
        targetTriple = llvm::sys::getDefaultTargetTriple();
    }
    const llvm::Triple triple(targetTriple);
    
    // 添加用户提供的参数（转换为 string）
    for (auto arg : args) {
        allArgsStr.push_back(arg ? std::string(arg) : "");
    }
    
    // 4. 平台特定参数配置
    if (triple.isOSWindows()) {
        allArgsStr.insert(allArgsStr.end(), {
            "/subsystem:console",
            "/entry:mainCRTStartup",
            "kernel32.lib",
            "ucrt.lib",
            "legacy_stdio_definitions.lib"
        });
    } 
    else if (triple.isOSLinux()) {
        const bool isMusl = (triple.getEnvironment() == llvm::Triple::Musl);
        const std::string musl_path = "../third_party/musl";
        
        allArgsStr.push_back("-static");
        allArgsStr.push_back("-lm");
        allArgsStr.push_back("-L" + musl_path + "/lib");  // 合并 -L 和路径
        allArgsStr.push_back(musl_path + "/lib/crt1.o");
        allArgsStr.push_back(musl_path + "/lib/libc.a");
    }
    else if (triple.isMacOSX()) {
        allArgsStr.insert(allArgsStr.end(), {
            "-lSystem",
            "-syslibroot",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
        });
    }
    else if (triple.getArch() == llvm::Triple::wasm32) {
        allArgsStr.insert(allArgsStr.end(), {
            "--export-all",
            "--no-entry",
            "-allow-undefined"
        });
    }

    // 2. 统一转换为 const char* 数组（此时所有 string 已固定）
    std::vector<const char*> args_;
    args_.reserve(allArgsStr.size());
    for (const auto& str : allArgsStr) {
        args_.push_back(str.c_str());
    }

    // 打印所有参数（用于调试）
    std::cout << "Linker arguments:" << std::endl;
    for(auto a : args_) {
        std::cout << (a ? a : "(null)") << std::endl;
    }

    lld::Result result = lld::lldMain(
        llvm::ArrayRef<const char*>(args_.data(), args_.size()),
        llvm::outs(),
        llvm::errs(),
        drivers
    );

    return result.retCode == 0;
}

bool compile_fobj_to_exe(const std::vector<const char*>&obj_paths, const char* output_file){
    std::vector<const char*> args;
    args.emplace_back("-o");
    args.emplace_back(output_file);
    for (auto obj_path : obj_paths){
        args.emplace_back(obj_path);
    }
    return thlang::link(args);
    
}

bool compile_fir_to_exe(const std::vector<std::string>& llvmir, const char* output_file) {
    std::vector<const char*> objs;
    std::vector<llvm::SmallString<128>> temp_files;
    std::string temp_dir = std::filesystem::temp_directory_path().string();
    // 1. 为每个IR生成临时对象文件
    for (const auto& llvm_ir : llvmir) {
        llvm::SmallString<128> temp_path;

        if (std::error_code ec = llvm::sys::fs::createUniqueFile(temp_dir + "temp-%%%%%%.o", temp_path)) {
            llvm::errs() << "Failed to create temp file: " << ec.message() << "\n";
            return false;
        }
        
        // 使用LLVM的文件抽象打开文件
        int file_fd;
        if (std::error_code ec = llvm::sys::fs::openFileForWrite(
                temp_path, 
                file_fd, 
                llvm::sys::fs::CD_OpenAlways, 
                llvm::sys::fs::OF_None)) {
            llvm::errs() << "Failed to open temp file: " << ec.message() << "\n";
            llvm::sys::fs::remove(temp_path);
            return false;
        }
        
        // 转换为标准FILE*以兼容原有接口
        FILE* tmpf = fdopen(file_fd, "w");
        if (!tmpf) {
            llvm::sys::fs::closeFile(file_fd);
            llvm::sys::fs::remove(temp_path);
            llvm::errs() << "Failed to convert file descriptor\n";
            return false;
        }
        
        // 使用原有函数编译到临时文件
        thlang::compile_fir_to_obj(llvm_ir, tmpf);
        fclose(tmpf);  // 会自动关闭file_fd
        
        // 保存路径用于后续链接
        char* path_copy = strdup(temp_path.c_str());
        if (!path_copy) {
            llvm::sys::fs::remove(temp_path);
            llvm::errs() << "Failed to allocate memory for path\n";
            return false;
        }
        objs.push_back(path_copy);
        temp_files.emplace_back(std::move(temp_path));
    }
    
    // 2. 添加启动文件
    objs.push_back("_start.o");
    
    // 3. 执行链接
    bool res = thlang::compile_fobj_to_exe(objs, output_file);
    
    // 4. 清理临时文件
    for (const auto& temp_path : temp_files) {
        if (std::error_code ec = llvm::sys::fs::remove(temp_path)) {
            llvm::errs() << "Warning: failed to remove temp file " 
                        << temp_path << ": " << ec.message() << "\n";
        }
    }
    
    // 5. 释放复制的字符串
    for (size_t i = 0; i < objs.size() - 1; ++i) { // 不释放"_start.o"
        free(const_cast<char*>(objs[i]));
    }
    
    return res;
}

bool compile_from_files_to_exe(const std::vector<std::string>& files, const std::string& output) {
    std::vector<std::string> object_files;
    std::vector<std::string> llvm_ir_files;
    
    for (const auto& file : files) {
        // Get file extension
        size_t dot_pos = file.rfind('.');
        if (dot_pos == std::string::npos) {
            std::cerr << "Error: File " << file << " has no extension\n";
            return false;
        }
        
        std::string ext = file.substr(dot_pos + 1);
        
        // Process based on file type
        if (ext == "th" || ext == "thlang") {
            // Source code file - compile to IR
            try {
                std::string ir = compile_toir_from_file(file);
                llvm_ir_files.push_back(ir);
            } catch (const std::exception& e) {
                std::cerr << "Error compiling " << file << ": " << e.what() << "\n";
                return false;
            }
        } else if (ext == "ll") {
            // LLVM IR text file - add to IR files
            llvm_ir_files.push_back(file);
        } else if (ext == "bc") {
            // LLVM bitcode file - convert to object file
            llvm::SmallString<128> temp_obj;
            std::vector<llvm::SmallString<128>> temp_files;
            std::string temp_dir = std::filesystem::temp_directory_path().string();
            if (std::error_code ec = llvm::sys::fs::createUniqueFile(temp_dir + "temp-%%%%%%.o", temp_obj)) {
                std::cerr << "Error creating temp file: " << ec.message() << "\n";
                return false;
            }
            
            // Use llc to convert bitcode to object file
            std::vector<llvm::StringRef> args = {
                "llc",
                "-filetype=obj",
                "-o", temp_obj.str(),
                file
            };
            
            if (llvm::sys::ExecuteAndWait(args[0], args) != 0) {
                std::cerr << "Error converting bitcode to object: " << file << "\n";
                llvm::sys::fs::remove(temp_obj);
                return false;
            }
            
            object_files.push_back(temp_obj.str().str());
        } else if (ext == "o" || ext == "obj") {
            // Object file - add directly to link list
            object_files.push_back(file);
        } else {
            std::cerr << "Error: Unknown file type " << file << "\n";
            return false;
        }
    }
    
    // Compile all IR files to object files
    for (const auto& ir_file : llvm_ir_files) {
        llvm::SmallString<128> temp_obj;
        std::vector<llvm::SmallString<128>> temp_files;
        std::string temp_dir = std::filesystem::temp_directory_path().string();
        if (std::error_code ec = llvm::sys::fs::createUniqueFile(temp_dir + "temp-%%%%%%.o", temp_obj)) {
            std::cerr << "Error creating temp file: " << ec.message() << "\n";
            return false;
        }
        
        // Open output file
        int fd;
        if (std::error_code ec = llvm::sys::fs::openFileForWrite(temp_obj, fd)) {
            std::cerr << "Error opening temp file: " << ec.message() << "\n";
            return false;
        }
        
        FILE* f = fdopen(fd, "wb");
        if (!f) {
            llvm::sys::fs::closeFile(fd);
            std::cerr << "Error converting file descriptor\n";
            return false;
        }
        
        // Compile IR to object
        compile_fir_to_obj(ir_file, f);
        
        
        fclose(f);
        object_files.push_back(temp_obj.str().str());
    }
    
    // Convert object file paths to const char* for linking
    std::vector<const char*> obj_paths;
    for (const auto& obj : object_files) {
        obj_paths.push_back(obj.c_str());
    }

    
    // Link all object files
    if (object_files.empty()) {
        std::cerr << "Error: No object files to link\n";
        return false;
    }
    
    return compile_fobj_to_exe(obj_paths, output.c_str());
}



} // namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr) {
        std::free(ptr);
    }

    // 编译代码并返回 C 字符串
    char* compile_code_to_ir(const char* code) {
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
    char* compile_code_to_ir_from_file(const char* file_path) {
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

    bool link_code(const char* const* obj_paths, int obj_count, const char* output_file) {
        try {
            std::vector<const char*> args(obj_paths, obj_paths + obj_count);
            return thlang::link(args);
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return false;
        }
    }

    // Compile object files to executable
    bool compile_code_fobj_to_exe(const char* const* obj_paths, int obj_count, const char* output_file) {
        try {
            std::vector<const char*> args(obj_paths, obj_paths + obj_count);
            return thlang::compile_fobj_to_exe(args, output_file);
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return false;
        }
    }

    // Compile LLVM IR to executable
    bool compile_code_fir_to_exe(const char* const* llvmirs, int ir_count, const char* output_file) {
        try {
            std::vector<std::string> irs(llvmirs, llvmirs + ir_count);
            return thlang::compile_fir_to_exe(irs, output_file);
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return false;
        }
    }
}