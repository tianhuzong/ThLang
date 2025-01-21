#include "node.h"
#include "codegen.h"




const static bool is_in_debug = true; //TODO:remove
void print_value(std::string something){
    if (is_in_debug == true){
        std::cout << "\033[31m打印字符串" << something << "\033[0m\n";
    }
}

void print_value(long long something){
    if (is_in_debug == true){
        std::cout << "\033[31m打印整数" << something << "\033[0m\n";
    }
}

void print_value(long double something){
    if (is_in_debug == true){
        std::cout.precision(17);
        std::cout << "\033[31m打印浮点数" << something << "\033[0m\n";
    }
}

namespace thlang{

void CodeGenContext::codegen(thlang::NModule& node){
    node.codegen(*this);
}

llvm::Value* NModule::codegen(thlang::CodeGenContext& context){
    return this->block->codegen(context);
}

llvm::Value* NBlock::codegen(thlang::CodeGenContext& context){
    llvm::Value* last = nullptr;
    for(auto& it : *this->stmts){
        last = it->codegen(context);
    }
    return last; //可能为nullptr
}

llvm::Value* IntAst::codegen(thlang::CodeGenContext& context){
	llvm::Value * res = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.getContext()), value, true);
    return res;
}

llvm::Value* FloatAst::codegen(thlang::CodeGenContext& context){
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.getContext()), value);
}

llvm::Value* StringAst::codegen(thlang::CodeGenContext& context){
    /*auto it = symTable.find(value);
    if(it != symTable.end()){
        return it->second;
    }*/
    return context.builder.CreateGlobalString(value);
}


llvm::Value* NameAst::codegen(thlang::CodeGenContext& context){
    //TODO:修改字段
    //return new LoadInst(context.locals()[name]->getType(),context.locals()[name], name, false, context.currentBlock());
    return  llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.getContext()), 0, true);
}

llvm::Value* BoolAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* UnOpAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* BinOpAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* AssignAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* ExprStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* VarStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* IfStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* ForStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* WhileStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* ReturnStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

llvm::Value* FunctionStmtAst::codegen(CodeGenContext& context) {
    return nullptr;
}

} // namespace thlang