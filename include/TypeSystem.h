#ifndef THLANG_TYPESYSTEM_H
#define THLANG_TYPESYSTEM_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include <iostream>
#include <unordered_map>
#include <vector>

namespace thlang {

class Type {
public:
    Type() {}
    Type(const std::string& type_name) : type_name(type_name) {}
    std::string type_name; // 类型名
    virtual std::string& get_type_name() ;
};

class FunctionType : public Type {
public:
    FunctionType() : Type("函数") {}
    virtual std::string& get_type_name() override ;
};

class ClassType : public Type {
private:
    std::vector<std::string> methods; // 类的方法
    std::vector<std::pair<thlang::Type, std::string>> members; // 类的成员变量 pair<类型, 字段名>
public:
    ClassType(const std::string& type_name) : Type(type_name) {}
    virtual std::string& get_type_name() override ;
    void add_method(const std::string& method_name) ;
    void add_member(const thlang::Type& type, const std::string& member_name) ;
};

class StructType : public Type {
private:
    std::vector<std::pair<thlang::Type, std::string>> members; // 结构体的成员变量 pair<类型, 字段名>
public:
    StructType(const std::string& type_name) : Type(type_name) {}
    virtual std::string& get_type_name() ;
    void add_member(const thlang::Type& type, const std::string& member_name);
};

class TypeSystem {
private:
    llvm::LLVMContext& llvmContext;
    std::unordered_map<std::string, thlang::Type> type_map;
public:
    TypeSystem(llvm::LLVMContext& llvmContext) : llvmContext(llvmContext) {}
    void add_type(const std::string& type_name, const thlang::Type& type) ;
    thlang::Type& get_type(const std::string& type_name) ;
    llvm::Type* get_llvm_type(const thlang::Type& type) ;
    llvm::Type* get_llvm_type(const std::string& type_name) ;
};

} // namespace thlang

#endif // THLANG_TYPESYSTEM_H