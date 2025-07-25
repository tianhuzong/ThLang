#include <thlang/codegen.h>

const static bool is_in_debug = true; // TODO:remove
void print_value(std::string something) {
    if (is_in_debug == true) {
        std::cout << "\033[31m打印字符串" << something << "\033[0m\n";
    }
}

void print_value(long long something) {
    if (is_in_debug == true) {
        std::cout << "\033[31m打印整数" << something << "\033[0m\n";
    }
}

void print_value(long double something) {
    if (is_in_debug == true) {
        std::cout.precision(17);
        std::cout << "\033[31m打印浮点数" << something << "\033[0m\n";
    }
}

namespace thlang {

void CodeGenContext::codegen(thlang::NModule &node) { node.codegen(*this); }

llvm::Value *NModule::codegen(thlang::CodeGenContext &context) {
    return this->block->codegen(context);
}

llvm::Value *NBlock::codegen(thlang::CodeGenContext &context) {
    llvm::Value *last;
    for (auto &it : *this->stmts) {
        assert(it);
        if (!it) {
            LogError("it为空");
            exit(1);
        }
        // auto var = static_cast<thlang::VarStmtAst*>(it.get());
        // std::cout << "it正常......\n" << typeid(*(it.get())).name() << "\n" ;
        last = it->codegen(context);
    }
    return last; // 可能为nullptr
}

llvm::Value *IntAst::codegen(thlang::CodeGenContext &context) {
    llvm::Value *res = llvm::ConstantInt::get(
            llvm::Type::getInt32Ty(context.getContext()), value, true);
    return res;
}

llvm::Value *FloatAst::codegen(thlang::CodeGenContext &context) {
    return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.getContext()),
                                                             llvm::APFloat(value));
}

llvm::Value *StringAst::codegen(thlang::CodeGenContext &context) {
    /*auto it = symTable.find(value);
    if(it != symTable.end()){
            return it->second;
    }*/
    value.erase(0,1);
    value.pop_back();
    return context.builder.CreateGlobalString(value);
}

llvm::Value *NameAst::codegen(thlang::CodeGenContext &context) {
    // TODO:修改字段
    // return new
    // LoadInst(context.locals()[name]->getType(),context.locals()[name], name,
    // false, context.currentBlock());
    llvm::Value *value = context.getvalue(this->name).second;
    if (!value) {
        LogError("Name " + this->name + " is not defined");
    }
    // TODO: 修改类型
    if(context.getvalue(this->name).first->type_name == "函数"){
        return value;
    }
    return context.builder.CreateLoad(context.typeSystem.get_llvm_type(context.getvalue(this->name).first), value, false);
}

llvm::Value *BoolAst::codegen(thlang::CodeGenContext &context) {
    // TODO:
    return nullptr;
}

llvm::Value *UnOpAst::codegen(thlang::CodeGenContext &context) {
    llvm::Value *un_expr = this->expr->codegen(context); // 避免发生命名冲突问题
    if (!un_expr) {
        return nullptr;
    }

    if (this->op == "-") {
        return context.builder.CreateSub(
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.getContext()), 0),
                un_expr, "subtemp");
    } else if (this->op == "+") {
        return un_expr;
    } else if (this->op == "!") {
    }
}

llvm::Value *BinOpAst::codegen(thlang::CodeGenContext &context) {
    llvm::Value *lhs = this->left->codegen(context);
    llvm::Value *rhs = this->right->codegen(context);

    if (!lhs || !rhs) {
        return nullptr;
    }
    if (this->op == "+") {
        // TODO: 对于其他类型例如文本的要进行更多判断
        if (lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy()){
            return context.builder.CreateFAdd(lhs, rhs, "addtmp");
        }
        else{
            return context.builder.CreateAdd(lhs, rhs, "addtmp");
        }
    } else if (this->op == "-") {
        // TODO: 对于其他类型例如文本的要进行更多判断
        if (lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy()){
            return context.builder.CreateFSub(lhs, rhs, "subtmp");
        }
        else{
            return context.builder.CreateSub(lhs, rhs, "subtmp");
        }
        
    } else if (this->op == "*") {
        // TODO: 对于其他类型例如文本的要进行更多判断
        if (lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy()){
            return context.builder.CreateFMul(lhs, rhs, "multmp");
        }
        else{
            return context.builder.CreateMul(lhs, rhs, "multmp");
        }

    } else if (this->op == "/") {
        // TODO: 对于其他类型例如文本的要进行更多判断
        if (lhs->getType()->isFloatingPointTy() || rhs->getType()->isFloatingPointTy()){
            return context.builder.CreateFDiv(lhs, rhs, "divtmp");
        }
        else{
            return context.builder.CreateSDiv(lhs, rhs, "divtmp");
        }
        
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

llvm::Value *AssignAst::codegen(thlang::CodeGenContext &context) {
    // 获取变量名对应的 NameAst 节点
    auto nameast = static_cast<thlang::NameAst *>((this->name).get());

    // 从上下文中获取变量名对应的 LLVM 值
    llvm::Value *dst = context.getvalue(nameast->name).second;
    if (!dst) {
        // 如果变量未定义，记录错误信息并返回
        return LogError("未定义的标识符: " + nameast->name);
    }

    // 生成表达式的 LLVM 值
    llvm::Value *exp = this->expr->codegen(context);
    if (!exp) {
        // 如果表达式生成失败，记录错误信息并返回
        return LogError("表达式生成失败");
    }

    // 存储赋值
    context.builder.CreateStore(exp, dst);

    // 返回变量地址
    return dst;
}

/*
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
*/

llvm::Value* CallExprAst::codegen(thlang::CodeGenContext& context) {
    auto* function_name = static_cast<thlang::NameAst*>(this->call_name.get());
    
    // 1. 尝试直接获取函数
    llvm::Function* function = context.theModule->getFunction(function_name->name);
    
    // 2. 如果未找到，从符号表获取（可能是函数指针）
    if (!function) {
        auto type = context.getvalue(function_name->name).first;
        auto value = context.getvalue(function_name->name).second;
        std::cout << "\033[31mtype: "<< type->type_name << "value: " << value << "\033[0m\n";
        if (!value) {
            return LogError("函数 " + function_name->name + " 未定义");
        }
        
        // 如果是函数指针类型，加载其值
        if (type->type_name == "函数") {
            function = llvm::dyn_cast<llvm::Function>(value);
            if (!function) {
                return LogError("符号 " + function_name->name + " 不是函数");
            }
        }
        // 普通变量则报错
        else {
            std::cerr << "\033[31m 调用名: " << function_name->name << " 符号类型: " << type->type_name << "\033[0m\n";
            for (auto x : context.getlocals()){
                if (x.first == "f"){
                    std::cout<< x.first << " , " << x.second.first->type_name << " " << x.second.second << "\n";
                    x.second.second->dump();
                }
            }
            return LogError("无法调用非函数类型的符号");
        }
    }
    
    // 参数检查和调用生成
    if (function->arg_size() != this->args->size()) {
        return LogError("参数数量不匹配");
    }
    
    std::vector<llvm::Value*> args;
    for (auto& arg : *this->args) {
        args.push_back(arg->codegen(context));
        if (!args.back()) return nullptr;
    }
    
    return context.builder.CreateCall(function, args, "calltmp");
}

llvm::Value *ExprStmtAst::codegen(thlang::CodeGenContext &context) {
    assert(this->expr);
    return this->expr->codegen(context);
}

llvm::Value* VarStmtAst::codegen(thlang::CodeGenContext& context) {
    auto* nameast = static_cast<thlang::NameAst*>(this->name.get());
    
    // 如果是函数指针类型，直接存储函数地址（不创建alloca）
    if (auto* funcType = dynamic_cast<thlang::FunctionType*>(this->type)) {
        if (!init) {
            return LogError("函数指针必须初始化");
        }
        
        llvm::Value* funcValue = init->codegen(context);
        if (!funcValue) return nullptr;
        
        // 直接保存函数指针到符号表
        context.setvalue(nameast->name, this->type, funcValue);
        return funcValue;
    }
    // 普通变量：使用alloca + store
    else {
        llvm::Value* inst = context.builder.CreateAlloca(
            context.typeSystem.get_llvm_type(this->type)
        );
        context.setvalue(nameast->name, this->type, inst);
        
        if (init) {
            llvm::Value* initVal = init->codegen(context);
            if (!initVal) return nullptr;
            context.builder.CreateStore(initVal, inst);
        }
        return inst;
    }
}

llvm::Value *IfStmtAst::codegen(CodeGenContext &context) {
    // 生成条件表达式的值
    llvm::Value *condValue = condition->codegen(context);
    if (!condValue) {
        return nullptr; // 生成条件表达式失败
    }

    // 确保条件为i1类型，如果不是则转换为i1
    if (condValue->getType() != context.builder.getInt1Ty()) {
        condValue = context.builder.CreateICmpNE(
                condValue,
                llvm::ConstantInt::get(condValue->getType(), 0, /*isSigned=*/true),
                "ifcond");
    }

    llvm::Function *currentFunction =
            context.builder.GetInsertBlock()->getParent();

    // 创建基本块：then, else, merge
    llvm::BasicBlock *thenBB =
            llvm::BasicBlock::Create(context.llvmContext, "then", currentFunction);
    llvm::BasicBlock *elseBB =
            llvm::BasicBlock::Create(context.llvmContext, "else");
    llvm::BasicBlock *mergeBB =
            llvm::BasicBlock::Create(context.llvmContext, "ifcont");

    // 生成条件分支指令
    context.builder.CreateCondBr(condValue, thenBB, elseBB);

    // 生成then块的代码
    context.builder.SetInsertPoint(thenBB);
    if (!thenStmt->codegen(context)) {
        return nullptr; // 生成then语句失败
    }
    // 如果当前块没有终止指令，跳转到merge块
    if (!context.builder.GetInsertBlock()->getTerminator()) {
        context.builder.CreateBr(mergeBB);
    }

    // 生成else块的代码
    elseBB->insertInto(currentFunction);
    context.builder.SetInsertPoint(elseBB);
    if (elseStmt) {
        if (!elseStmt->codegen(context)) {
            return nullptr; // 生成else语句失败
        }
    }
    // 如果当前块没有终止指令，跳转到merge块
    if (!context.builder.GetInsertBlock()->getTerminator()) {
        context.builder.CreateBr(mergeBB);
    }

    // 将merge块添加到函数并设置插入点
    mergeBB->insertInto(currentFunction);
    context.builder.SetInsertPoint(mergeBB);

    return nullptr; // if语句没有返回值
}

llvm::Value *ForStmtAst::codegen(thlang::CodeGenContext &context) {
    llvm::Function *theFunction = context.builder.GetInsertBlock()->getParent();

    // 创建基本块
    llvm::BasicBlock *initBlock =
            llvm::BasicBlock::Create(context.llvmContext, "forinit", theFunction);
    llvm::BasicBlock *condBlock =
            llvm::BasicBlock::Create(context.llvmContext, "forcond", theFunction);
    llvm::BasicBlock *bodyBlock =
            llvm::BasicBlock::Create(context.llvmContext, "forbody", theFunction);
    llvm::BasicBlock *iterBlock =
            llvm::BasicBlock::Create(context.llvmContext, "foriter", theFunction);
    llvm::BasicBlock *afterBlock =
            llvm::BasicBlock::Create(context.llvmContext, "forcont", theFunction);

    // 获取当前的 entry 块
    llvm::BasicBlock *entryBlock = context.builder.GetInsertBlock();

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
    llvm::Value *condValue = this->condition->codegen(context);
    if (!condValue) {
        return nullptr;
    }

    condValue = context.builder.CreateIntCast(
            condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(
            condValue, llvm::ConstantInt::get(
                                         llvm::Type::getInt1Ty(context.llvmContext), 0, true));
    context.builder.CreateCondBr(condValue, bodyBlock, afterBlock);

    // 循环体块
    context.builder.SetInsertPoint(bodyBlock);
    context.pushBlock(bodyBlock);
    this->body->codegen(context);
    if (!bodyBlock->getTerminator())
        context.builder.CreateBr(iterBlock); // 确保从 bodyBlock 跳转到 iterBlock
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

llvm::Value *WhileStmtAst::codegen(thlang::CodeGenContext &context) {
    llvm::Function *theFunction = context.builder.GetInsertBlock()->getParent();

    llvm::BasicBlock *block =
            llvm::BasicBlock::Create(context.llvmContext, "whileloop", theFunction);
    llvm::BasicBlock *after =
            llvm::BasicBlock::Create(context.llvmContext, "whilecont");

    // 判断循环条件
    llvm::Value *condValue = this->condition->codegen(context);
    if (!condValue)
        return nullptr;

    condValue = context.builder.CreateIntCast(
            condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(
            condValue, llvm::ConstantInt::get(
                                         llvm::Type::getInt1Ty(context.llvmContext), 0, true));

    context.builder.CreateCondBr(condValue, block, after);
    context.builder.SetInsertPoint(block);
    context.pushBlock(block);

    // 循环体
    this->body->codegen(context);

    context.popBlock();

    // 重新判断循环条件
    condValue = this->condition->codegen(context);
    condValue = context.builder.CreateIntCast(
            condValue, llvm::Type::getInt1Ty(context.llvmContext), true);
    condValue = context.builder.CreateICmpNE(
            condValue, llvm::ConstantInt::get(
                                         llvm::Type::getInt1Ty(context.llvmContext), 0, true));
    context.builder.CreateCondBr(condValue, block, after);

    // 插入循环后续的基本块
    after->insertInto(theFunction);
    context.builder.SetInsertPoint(after);
    if (!after->getTerminator()) {
        context.builder.CreateRetVoid();
    }
    return nullptr;
}

llvm::Value *ReturnStmtAst::codegen(thlang::CodeGenContext &context) {
    if (!this->expr){
        context.builder.CreateRetVoid();
        return nullptr;
    }
    llvm::Value *returnValue = this->expr->codegen(context);
    context.builder.CreateRet(returnValue);
    return returnValue;
}

llvm::Value *FunctionStmtAst::codegen(thlang::CodeGenContext &context) {
    std::vector<llvm::Type *> argTypes;
    if (!this->args->empty()) {
        for (const auto &arg : *this->args) {
            argTypes.push_back(context.typeSystem.get_llvm_type(arg->type));
            //argTypes.push_back();
        }
    }
    llvm::Type* retType = context.typeSystem.get_llvm_type(this->type);

    llvm::FunctionType *functionType =
            llvm::FunctionType::get(retType, argTypes, false);
    thlang::NameAst *function_name =
            static_cast<thlang::NameAst *>(this->name.get());
    std::string fname = (function_name->name == "入口") ? "main" : function_name->name;
    llvm::Function *function = llvm::Function::Create(
            functionType, llvm::GlobalValue::ExternalLinkage,
            fname, context.theModule.get());

    if (!this->is_extern) {
        llvm::BasicBlock *entryBlock = llvm::BasicBlock::Create(
                context.llvmContext, "entry", function, nullptr);
        context.pushBlock(entryBlock);
        // 声明函数参数
        auto origin_arg = this->args->begin();
        unsigned argNo = 0;
        for (auto &ir_arg_it : function->args()) {
            thlang::NameAst *arg_name =
                    static_cast<thlang::NameAst *>((*origin_arg)->name.get());
            thlang::Type *arg_type = (*origin_arg)->type;
            llvm::Type *arg_type_llvm = context.typeSystem.get_llvm_type(arg_type);
            ir_arg_it.setName(arg_name->name);
            llvm::Value* argAlloc = context.builder.CreateAlloca(arg_type_llvm,
            nullptr, ir_arg_it.getName().str() + ".addr");
            context.builder.CreateStore(&ir_arg_it, argAlloc);
            context.setvalue(arg_name->name, arg_type, argAlloc);
            origin_arg++;
            argNo++;
        }

        // 生成函数体代码
        this->block->codegen(context);
    }
    std::vector<thlang::Type*> args_thlangtype;
    for (const auto &arg : *this->args) {
        args_thlangtype.push_back(arg->type);
    }
    if(function_name->name != "入口" && function_name->name != "main" ){
        llvm::Value* function_value = function;
        context.setglobal(function_name->name, thlang::FunctionType::get(this->type, std::move(args_thlangtype)), function_value);
        std::cout << "function_name: " << (function_name->name) << "\tptr: " << context.getvalue((function_name->name)).second << "\n";
    }
    return function;
}

} // namespace thlang


std::unique_ptr<llvm::Module> parseIRFromString(llvm::LLVMContext& context, 
                                              const std::string& irText) {
    // 创建内存缓冲区
    auto buffer = llvm::MemoryBuffer::getMemBuffer(irText);
    
    // 创建诊断信息
    llvm::SMDiagnostic err;
    
    // 直接使用MemoryBufferRef解析
    auto module = llvm::parseAssembly(
        buffer->getMemBufferRef(),  // 这才是正确的参数类型
        err,
        context
    );
    
    if (!module) {
        err.print("IRParser", llvm::errs());
        return nullptr;
    }
    
    return std::move(module);
}

llvm::Value *LogError(std::string str) {
    std::cerr << str << "\n";
    return nullptr;
}
