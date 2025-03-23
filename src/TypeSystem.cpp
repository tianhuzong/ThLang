#include "TypeSystem.h"
#include <iostream>

namespace thlang{
std::string& Type::get_type_name(){
    return type_name;
}

llvm::Type* Type::get_llvm_type(llvm::LLVMContext& context){
    // 整数
    if(type_name == "整数型"){
        return llvm::Type::getInt32Ty(context);
    }
    else if(type_name == "长整数型"){
        return llvm::Type::getInt64Ty(context);
    }
    else if(type_name == "短整数型"){
        return llvm::Type::getInt16Ty(context);
    }
    // 小数
    else if(type_name == "小数型"){
        return llvm::Type::getFloatTy(context);
    }
    else if(type_name == "双精度小数型"){
        return llvm::Type::getDoubleTy(context);
    }
    else if(type_name == "半精度小数型"){
        return llvm::Type::getHalfTy(context);
    }

}

llvm::Type* FunctionType::get_llvm_type(llvm::LLVMContext& context){
    return nullptr;
}

llvm::Type* ClassType::get_llvm_type(llvm::LLVMContext& context){
    return nullptr;
}

llvm::Type* StructType::get_llvm_type(llvm::LLVMContext& context){
    return nullptr;
}

std::string& FunctionType::get_type_name(){
    return type_name;
}

std::string& ClassType::get_type_name(){
    return type_name;
}

void ClassType::add_method(std::string method_name){
    this->methods.push_back(method_name);
}

void ClassType::add_member(thlang::Type type, std::string member_name){
    this->members.emplace_back(type, member_name);
}

std::string& StructType::get_type_name(){
    return type_name;
}

void StructType::add_member(thlang::Type type, std::string member_name){
    this->members.emplace_back(type, member_name);
}

void TypeSystem::add_type(std::string type_name, thlang::Type type){
    this->type_map[type_name] = type;
}

thlang::Type TypeSystem::get_type(std::string type_name){
    return this->type_map[type_name];
}

llvm::Type* TypeSystem::get_llvm_type(thlang::Type type){
    return type.get_llvm_type(this->llvmContext);
}

llvm::Type* TypeSystem::get_llvm_type(std::string type_name){
    auto type = this->get_type(type_name);
    return this->get_llvm_type(type);
}

}//namespace thlang