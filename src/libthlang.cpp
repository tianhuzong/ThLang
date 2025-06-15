#include <thlang/thlang.h>

namespace thlang {
std::string compile(const std::string& code) {
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

std::string compile_from_file(const std::string& file_path) {
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
    return compile(code);
}
} // namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr) {
        std::free(ptr);
    }

    // 编译代码并返回 C 字符串
    char* compile_code(const char* code) {
        try {
            std::string result = thlang::compile(std::string(code));
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
    char* compile_code_from_file(const char* file_path) {
        try {
            std::string result = thlang::compile_from_file(std::string(file_path));
            char* c_result = static_cast<char*>(std::malloc(result.size() + 1));
            std::strcpy(c_result, result.c_str());
            return c_result;
        } catch (const std::exception& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
            return nullptr;
        }
    }
}