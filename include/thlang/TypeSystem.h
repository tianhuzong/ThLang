#pragma once
#ifndef THLANG_TYPESYSTEM_H
#define THLANG_TYPESYSTEM_H

// TODO:设计类型系统时,对于文本型等类型做一个标记,目前无实际意义
#define DYNAMIC_SIZE -1


#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include <iostream>
#include <unordered_map>
#include <vector>

namespace thlang {

class CodeGenContext;

class Type {
public:
    Type() : implicit_copy(false),  size(0) {};  // 新增默认属性
    Type(const std::string& type_name, bool implicit_copy = false,  size_t size = 0) 
        : type_name(type_name), implicit_copy(implicit_copy),  size(size) {};

    static Type* create(const std::string& name, bool implicit_copy, size_t size) ;

    std::string type_name;
    bool implicit_copy;
    size_t size;           // 类型大小

    virtual std::string& get_type_name() ;
    virtual llvm::Type* get_llvm_type(llvm::LLVMContext& context);

    // 判断是否需要生成隐式复制逻辑
    virtual bool should_implicit_copy() const ;

    static constexpr size_t MAX_IMPLICIT_COPY_SIZE = 16; 
};

class FunctionType : public Type {
public:
    Type* return_type;
    std::vector<Type*> arg_types;
    FunctionType(Type* return_type,const  std::vector<Type*>& arg_types) : Type("函数", false, 0), return_type(return_type), arg_types(std::move(arg_types)){} ; // 函数类型不参与隐式复制
    virtual llvm::Type* get_llvm_type(llvm::LLVMContext& context) override;
};

class ClassType : public Type {
private:
    std::vector<std::string> methods;
    std::vector<std::pair<Type*, std::string>> members; 
public:
    ClassType(std::string type_name, bool implicit_copy = false) 
        : Type(type_name, implicit_copy,  0) {}; // 类默认不隐式复制

    void add_method(const std::string& method_name) ;
    void add_member(Type* type, const std::string& member_name) ;
    virtual llvm::Type* get_llvm_type(llvm::LLVMContext& context) override;
};


class TypeSystem {
private:
    
    std::unordered_map<std::string, Type*> type_map; // 改为指针存储
    llvm::LLVMContext llvmContext;
    static Type* empty_type_ptr;
public:
    TypeSystem() ;
    
    void add_type(const std::string& type_name, Type* type) ;
    llvm::LLVMContext& getContext();
    Type* get_type(const std::string& type_name) ;

    llvm::Type* get_llvm_type(Type* type) ;

    llvm::Type* get_llvm_type(const std::string& type_name) ;
};

} // namespace thlang

extern thlang::TypeSystem type_System;

#endif // THLANG_TYPESYSTEM_H