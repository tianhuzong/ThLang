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
    llvm::Value* value = context.getvalue(this->name);
    if( !value ){
        LogError("Name " + this->name + " is not defined");
    }
    
    return context.builder.CreateLoad(value, false, "");
}


llvm::Value* BoolAst::codegen(thlang::CodeGenContext& context) {
    // TODO:
    return nullptr;
}

llvm::Value* UnOpAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* BinOpAst::codegen(thlang::CodeGenContext& context) {
    llvm::Value* lhs = this->left->codegen(context);
    llvm::Value* rhs = this->right->codegen(context);

    if (!lhs || !rhs){
        return nullptr;
    }
    if (this->op == "+") {
        return context.builder.CreateAdd(lhs, rhs, "addtmp");
    } else if (this->op == "-") {
        return context.builder.CreateSub(lhs, rhs, "subtmp");
    } else if (this->op == "*") {
        return context.builder.CreateMul(lhs, rhs, "multmp");
    } else if (this->op == "/") {
        return context.builder.CreateSDiv(lhs, rhs, "divtmp");
    } else if (this->op == "&" || this->op == "且") {
        return context.builder.CreateAnd(lhs, rhs, "andtmp");
    } else if (this->op == "||" || this->op == "或") {
        return context.builder.CreateOr(lhs, rhs, "ortmp");
    } else if (this->op == "^") {
        return context.builder.CreateXor(lhs, rhs, "xortmp");
    } else if (this->op == "<<") {
        return context.builder.CreateShl(lhs, rhs, "shltmp");
    } else if (this->op == ">>") {
        return context.builder.CreateAShr(lhs, rhs, "ashrtmp");
    } else if (this->op == "<") {
        return context.builder.CreateICmpULT(lhs, rhs, "cmptmp");
    } else if (this->op == "<=") {
        return context.builder.CreateICmpSLE(lhs, rhs, "cmptmp");
    } else if (this->op == ">=") {
        return context.builder.CreateICmpSGE(lhs, rhs, "cmptmp");
    } else if (this->op == ">") {
        return context.builder.CreateICmpSGT(lhs, rhs, "cmptmp");
    } else if (this->op == "==") {
        return context.builder.CreateICmpEQ(lhs, rhs, "cmptmp");
    } else if (this->op == "!=") {
        return context.builder.CreateICmpNE(lhs, rhs, "cmptmp");
    } else {
        return LogError("符号不存在");
    }


    return nullptr;
}

llvm::Value* AssignAst::codegen(thlang::CodeGenContext& context) {
    auto nameast = static_cast<thlang::NameAst*>((this->name).get());
    llvm::Value* dst = context.getvalue(nameast->name);
    if( !dst ){
        return LogError("未定义的标识符: " + nameast->name);
    }
    llvm::Value* exp = this->expr->codegen(context);
    context.builder.CreateStore(exp, dst);
    return dst;
}

llvm::Value* ExprStmtAst::codegen(thlang::CodeGenContext& context) {
    return this->expr->codegen(context);
}

llvm::Value* VarStmtAst::codegen(thlang::CodeGenContext& context) {
    auto nameast = static_cast<thlang::NameAst*>(this->name.get());
    llvm::Value* inst = context.builder.CreateAlloca(context.typeSystem.get_llvm_type(this->type), nullptr, nameast->name.c_str());
    context.setvalue(nameast->name, this->type, inst);
    if( this->init != nullptr ){
        //thlang::ExprAst exprast = *static_cast<thlang::ExprAst*>(this->init.get());
        thlang::AssignAst assignment(std::move(std::make_unique<thlang::NameAst>(nameast->name)), this->init);
        assignment.codegen(context);
    }
    return inst;
}

llvm::Value* IfStmtAst::codegen(thlang::CodeGenContext& context) {
    llvm::Value* cond = this->condition->codegen(context);//条件
    if( !cond ){
        return nullptr;
    }
    cond = context.builder.CreateIntCast(cond, llvm::Type::getInt1Ty(context.llvmContext), true);
    cond = context.builder.CreateICmpNE(cond, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.llvmContext), 0, true));
    llvm::Function* theFunction = context.builder.GetInsertBlock()->getParent();      // the function where if statement is in

    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(context.llvmContext, "then", theFunction);
    llvm::BasicBlock *falseBB = llvm::BasicBlock::Create(context.llvmContext, "else");
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(context.llvmContext, "ifcont");

    if( this->elseStmt ){ // 判断是否存在else语句
        context.builder.CreateCondBr(cond, thenBB, falseBB);
    } else{
        context.builder.CreateCondBr(cond, thenBB, mergeBB);
    }

    context.builder.SetInsertPoint(thenBB);

    context.pushBlock(thenBB);

    this->thenStmt->codegen(context);

    context.popBlock();

    thenBB = context.builder.GetInsertBlock();

    if( thenBB->getTerminator() == nullptr ){        // 如果块没有终结指令 就添加一个跳转
        context.builder.CreateBr(mergeBB);
    }

    if( this->elseStmt ){
        theFunction->getBasicBlockList().push_back(falseBB);    
        context.builder.SetInsertPoint(falseBB);            
        context.pushBlock(thenBB);
        this->elseStmt->codegen(context);
        if( mergeBB->getTerminator() == nullptr ){        // 如果块没有终结指令 就添加一个跳转
            context.builder.CreateBr(mergeBB);
        }
        context.popBlock();

    }

    theFunction->getBasicBlockList().push_back(mergeBB);
    context.builder.SetInsertPoint(mergeBB);        // 设置插入点
    if( mergeBB->getTerminator() == nullptr ){        // 如果块没有终结指令 就添加一个跳转
        context.builder.CreateRetVoid();
    }

    return nullptr;
}

llvm::Value* ForStmtAst::codegen(thlang::CodeGenContext& context) {
    llvm::Function* theFunction = context.builder.GetInsertBlock()->getParent();

    // 创建基本块
    llvm::BasicBlock* initBlock = llvm::BasicBlock::Create(context.llvmContext, "forinit", theFunction);
    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(context.llvmContext, "forcond", theFunction);
    llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(context.llvmContext, "forbody", theFunction);
    llvm::BasicBlock* iterBlock = llvm::BasicBlock::Create(context.llvmContext, "foriter", theFunction);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(context.llvmContext, "forcont", theFunction);

    // 获取当前的 entry 块
    llvm::BasicBlock* entryBlock = context.builder.GetInsertBlock();

    // 在 entry 块中添加跳转到 initBlock 的指令
    context.builder.SetInsertPoint(entryBlock);
    context.builder.CreateBr(initBlock);

    // 初始化块
    context.builder.SetInsertPoint(initBlock);
    if (this->init) {
        this->init->codegen(context);
    }
    context.builder.CreateBr(condBlock);

    // 条件块
    context.builder.SetInsertPoint(condBlock);
    llvm::Value* condValue = this->condition->codegen(context);
    if (!condValue) {
        return nullptr;
    }

    condValue = context.builder.CreateIntCast(condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.llvmContext), 0, true));
    context.builder.CreateCondBr(condValue, bodyBlock, afterBlock);

    // 循环体块
    context.builder.SetInsertPoint(bodyBlock);
    context.pushBlock(bodyBlock);
    this->body->codegen(context);
    if(!bodyBlock->getTerminator())
        context.builder.CreateBr(iterBlock);  // 确保从 bodyBlock 跳转到 iterBlock
    context.popBlock();
    // 迭代块
    context.builder.SetInsertPoint(iterBlock);
    if (this->increment) {
        this->increment->codegen(context);
    }
    context.builder.CreateBr(condBlock);

    // 退出块
    context.builder.SetInsertPoint(afterBlock);
    if (!afterBlock->getTerminator()) {
        context.builder.CreateRetVoid();
    }

    return nullptr;
}

llvm::Value* WhileStmtAst::codegen(thlang::CodeGenContext& context) {
    llvm::Function* theFunction = context.builder.GetInsertBlock()->getParent();

    llvm::BasicBlock *block = llvm::BasicBlock::Create(context.llvmContext, "whileloop", theFunction);
    llvm::BasicBlock *after = llvm::BasicBlock::Create(context.llvmContext, "whilecont");

    // 判断循环条件
    llvm::Value* condValue = this->condition->codegen(context);
    if (!condValue) 
        return nullptr;

    condValue = context.builder.CreateIntCast(condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.llvmContext), 0, true));

    context.builder.CreateCondBr(condValue, block, after);
    context.builder.SetInsertPoint(block);
    context.pushBlock(block);

    // 循环体
    this->body->codegen(context);

    context.popBlock();

    // 重新判断循环条件
    condValue = this->condition->codegen(context);
    condValue = context.builder.CreateIntCast(condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(condValue, llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.llvmContext), 0, true));
    context.builder.CreateCondBr(condValue, block, after);

    // 插入循环后续的基本块
    theFunction->getBasicBlockList().push_back(after);
    context.builder.SetInsertPoint(after);
    if(!after->getTerminator()){
        context.builder.CreateRetVoid();
    }
    return nullptr;
}

llvm::Value* ReturnStmtAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

llvm::Value* FunctionStmtAst::codegen(thlang::CodeGenContext& context) {
    return nullptr;
}

} // namespace thlang

llvm::Value* LogError(std::string str){
    std::cerr << str << "\n";
    return nullptr;
}

llvm::Value* LogError(const char* str){
    return LogError(str);
}