#ifndef THLANG_H
#define THLANG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


namespace thlang {
std::string compile_toir(const std::string& code);
std::string compile_toir_from_file(const std::string& file_path);
void compile_fir_to_asm(const std::string& llvmir, FILE* output_file);
void compile_fir_to_obj(const std::string& llvmir, FILE* output_file);
bool link(const std::vector<const char*>& args, std::string targetTriple = "");
bool compile_fobj_to_exe(const std::vector<const char*>&obj_paths, const char* output_file);
bool compile_fir_to_exe(const std::vector<std::string>& llvmir, const char* output_file);
bool compile_from_files_to_exe(const std::vector<std::string>& files, const std::string& output);
} //namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr);
    char* compile_code_to_ir(const char* code);
    char* compile_code_to_ir_from_file(const char* file_path);
    int compile_code_fir_to_asm(const char* llvmir, FILE* output_file);
    int compile_code_fir_to_obj(const char* llvmir, FILE* output_file);
    bool link_code(const char* const* obj_paths, int obj_count, const char* output_file);
    bool compile_code_fobj_to_exe(const char* const* obj_paths, int obj_count, const char* output_file);
    bool compile_code_fir_to_exe(const char* const* llvmirs, int ir_count, const char* output_file);
}

#endif //THLANG_H