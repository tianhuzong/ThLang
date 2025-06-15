#ifndef THLANG_H
#define THLANG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <thlang/codegen.h>
#include <thlang/node.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

extern int yyparse(thlang::NModule &root_program, thlang::CodeGenContext &context);
extern FILE* yyin;
namespace thlang {
std::string compile(const std::string& code);
std::string compile_from_file(const std::string& file_path);
} //namespace thlang

// 为 外部 提供的 extern "C" 接口
extern "C" {
    void free_memory(char* ptr);
    char* compile_code(const char* code);
    char* compile_code_from_file(const char* file_path);
}

#endif //THLANG_H