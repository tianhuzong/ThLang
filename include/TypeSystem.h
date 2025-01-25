// 实现一个类型系统
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

namespace thlang{

class Type{
public:
    Type(){};
    Type(std::string type_name) : type_name(type_name) {};
    std::string type_name; //类型名
    virtual std::string& get_type_name();
};

class FunctionType : public Type{
// TODO:考虑将参数和返回值的类型加入函数类型
public:
    FunctionType();
    std::string type_name = "函数"; 
    virtual std::string& get_type_name() override;
};

class ClassType : public Type{
private:
    std::vector<std::string> methods; //类的方法
    std::vector<std::pair<std::shared_ptr<thlang::Type>, std::string>> members; //类的成员变量pair<类型, 字段名>
public:
    ClassType(std::string type_name) : type_name(type_name){};
    std::string type_name; //类的名字
    virtual std::string& get_type_name() override;
    void add_method(std::string method_name);
    void add_member(std::shared_ptr<thlang::Type> type, std::string member_name);
};

class StructType : public Type{
private:
    std::vector<std::pair<std::shared_ptr<thlang::Type>, std::string>> members; //结构体的成员变量pair<类型, 字段名>
public:
    StructType(std::string type_name) : type_name(type_name){};
    std::string type_name; //结构体的名字
    virtual std::string& get_type_name();
    void add_member(std::shared_ptr<thlang::Type> type, std::string member_name);
};

class TypeSystem{
private:
    llvm::LLVMContext& llvmContext;
    std::unordered_map<std::string, std::shared_ptr<thlang::Type>> type_map;
public:
    TypeSystem(llvm::LLVMContext& llvmContext) : llvmContext(llvmContext){};
    void add_type(std::string type_name, std::shared_ptr<Type> type);
    std::shared_ptr<thlang::Type> get_type(std::string type_name);
    llvm::Type* get_llvm_type(std::shared_ptr<thlang::Type> type);
    llvm::Type* get_llvm_type(std::string type_name);
};

} //namespace thlang

#endif //THLANG_TYPESYSTEM_H