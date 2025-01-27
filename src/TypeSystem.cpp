#include "TypeSystem.h"
#include <iostream>

namespace thlang {

std::string& Type::get_type_name() {
    return type_name;
}

std::string& FunctionType::get_type_name() {
    return type_name;
}

std::string& ClassType::get_type_name() {
    return type_name;
}

void ClassType::add_method(const std::string& method_name) {
    this->methods.push_back(method_name);
}

void ClassType::add_member(const thlang::Type& type, const std::string& member_name) {
    this->members.emplace_back(type, member_name);
}

std::string& StructType::get_type_name() {
    return type_name;
}

void StructType::add_member(const thlang::Type& type, const std::string& member_name) {
    this->members.emplace_back(type, member_name);
}

void TypeSystem::add_type(const std::string& type_name, const thlang::Type& type) {
    this->type_map[type_name] = type;
}

thlang::Type& TypeSystem::get_type(const std::string& type_name) {
    auto it = this->type_map.find(type_name);
    if (it == this->type_map.end()) {
        throw std::runtime_error("Type not found: " + type_name);
    }
    return it->second;
}

llvm::Type* TypeSystem::get_llvm_type(const thlang::Type& type) {
    // Implement LLVM type conversion logic here
    return nullptr;
}

llvm::Type* TypeSystem::get_llvm_type(const std::string& type_name) {
    try {
        auto type = this->get_type(type_name);
        return this->get_llvm_type(type);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr;
    }
}

} // namespace thlang