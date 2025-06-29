#include <thlang/TypeSystem.h>
#include <iostream>


namespace thlang {

// --- Type 基类实现 ---
std::string& Type::get_type_name() { 
    return type_name; 
}

Type* Type::create(const std::string& name, bool implicit_copy, size_t size) {
        return new Type(name, implicit_copy, size);
}

llvm::Type* Type::get_llvm_type(llvm::LLVMContext& context) {
    if (type_name == "整数型") {
        return llvm::Type::getInt32Ty(context);
    } else if (type_name == "长整数型") {
        return llvm::Type::getInt64Ty(context);
    } else if (type_name == "短整数型") {
        return llvm::Type::getInt16Ty(context);
    } else if (type_name == "小数型") {
        return llvm::Type::getFloatTy(context);
    } else if (type_name == "双精度小数型") {
        return llvm::Type::getDoubleTy(context);
    } else if (type_name == "布尔型") {
        return llvm::Type::getInt1Ty(context);
    } else if (type_name == "文本型") {
        return llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0);
    }
    return nullptr;
}

bool Type::should_implicit_copy() const {
    return implicit_copy  || size <= MAX_IMPLICIT_COPY_SIZE;
}

// --- FunctionType 实现 ---
llvm::Type* FunctionType::get_llvm_type(llvm::LLVMContext& context) {
    // 函数类型不参与隐式复制
    std::vector<llvm::Type *> argTypes;
    if (!this->arg_types.empty()) {
        for (const auto &arg : this->arg_types) {
            argTypes.push_back(type_System.get_llvm_type(arg));
            //argTypes.push_back();
        }
    }
    llvm::Type* retType = type_System.get_llvm_type(this->return_type);

    llvm::FunctionType *functionType =
            llvm::FunctionType::get(retType, argTypes, false);
    return functionType;
}

// --- ClassType 实现 ---
llvm::Type* ClassType::get_llvm_type(llvm::LLVMContext& context) {
    std::vector<llvm::Type*> member_types;
    for (const auto& member : members) {
        llvm::Type* ty = member.first->get_llvm_type(context);
        if (!ty) return nullptr;
        member_types.push_back(ty);
    }
    return llvm::StructType::create(context, member_types, type_name);
}

void ClassType::add_member(Type* type,const std::string& member_name) {
    members.emplace_back(type, member_name);
    size += type->size; // 更新类大小（需考虑对齐）
}


// --- TypeSystem 实现 ---

Type* TypeSystem::empty_type_ptr = Type::create("空类型", true, 0);

TypeSystem::TypeSystem() {
    // 注册基本类型（隐式复制）
    add_type("整数型", Type::create("整数型", true, 4));
    add_type("长整数型", Type::create("长整数型", true,  8));
    add_type("短整数型", Type::create("短整数型", true,  2));
    add_type("小数型", Type::create("小数型", true,  4));
    add_type("双精度小数型", Type::create("双精度小数型", true,  8));
    add_type("布尔型", Type::create("布尔型", true,  1));
    add_type("文本型", Type::create("文本型", true, DYNAMIC_SIZE));
    add_type("空类型",empty_type_ptr);
}

void TypeSystem::add_type(const std::string& type_name, thlang::Type* type) {
    type_map[type_name] = type;
}

llvm::LLVMContext& TypeSystem::getContext() { 
    return this->llvmContext; 
}

thlang::Type* TypeSystem::get_type(const std::string& type_name) {
    auto it = type_map.find(type_name);
    if(it != type_map.end() ){
        return it->second;
    }
    else{
        return empty_type_ptr;
    }
}

llvm::Type* TypeSystem::get_llvm_type(thlang::Type* type) {
    return type->get_llvm_type(llvmContext);
}

llvm::Type* TypeSystem::get_llvm_type(const std::string& type_name) {
    return get_llvm_type(get_type(type_name));
}

} // namespace thlang

thlang::TypeSystem type_System;