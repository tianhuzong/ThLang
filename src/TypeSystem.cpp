#include "TypeSystem.h"
#include <iostream>

namespace thlang{
std::string& Type::get_type_name(){
    return type_name;
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

void ClassType::add_member(std::shared_ptr<thlang::Type> type, std::string member_name){
    this->members.emplace_back(type, member_name);
}

std::string& StructType::get_type_name(){
    return type_name;
}

void StructType::add_member(std::shared_ptr<thlang::Type> type, std::string member_name){
    this->members.emplace_back(type, member_name);
}

}//namespace thlang