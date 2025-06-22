#ifndef THLANG_H
#define THLANG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>


namespace thlang {
std::string compile_toir(const std::string& code);
std::string compile_toir_from_file(const std::string& file_path);
void compile_fir_to_asm(const std::string& llvmir, FILE* output_file);
void compile_fir_to_obj(const std::string& llvmir, FILE* output_file);
bool link(const std::vector<const char*>& args);
} //namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr);
    char* compile_toir_code(const char* code);
    char* compile_toir_code_from_file(const char* file_path);
    int compile_code_fir_to_asm(const char* llvmir, FILE* output_file);
    int compile_code_fir_to_obj(const char* llvmir, FILE* output_file);
}

#endif //THLANG_H