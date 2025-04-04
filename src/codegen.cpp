#include "codegen.h"

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
                               value);
}

llvm::Value *StringAst::codegen(thlang::CodeGenContext &context) {
  /*auto it = symTable.find(value);
  if(it != symTable.end()){
      return it->second;
  }*/
  return context.builder.CreateGlobalString(value);
}

llvm::Value *NameAst::codegen(thlang::CodeGenContext &context) {
  // TODO:修改字段
  // return new
  // LoadInst(context.locals()[name]->getType(),context.locals()[name], name,
  // false, context.currentBlock());
  llvm::Value *value = context.getvalue(this->name);
  if (!value) {
    LogError("Name " + this->name + " is not defined");
  }
  // TODO: 修改类型
  return context.builder.CreateLoad(context.builder.getInt32Ty(), value, false);
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

llvm::Value *AssignAst::codegen(thlang::CodeGenContext &context) {
  // 获取变量名对应的 NameAst 节点
  auto nameast = static_cast<thlang::NameAst *>((this->name).get());

  // 从上下文中获取变量名对应的 LLVM 值
  llvm::Value *dst = context.getvalue(nameast->name);
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
llvm::Value *ExprStmtAst::codegen(thlang::CodeGenContext &context) {
  return this->expr->codegen(context);
}

llvm::Value *VarStmtAst::codegen(thlang::CodeGenContext &context) {
  std::cout << "varstmtcodegn\n";
  auto nameast = static_cast<thlang::NameAst *>(this->name.get());
  // TODO:llvm::Value* inst =
  // context.builder.CreateAlloca(context.typeSystem.get_llvm_type(this->type),
  // nullptr, nameast->name.c_str());
  llvm::Value *inst =
      context.builder.CreateAlloca(llvm::Type::getInt32Ty(context.llvmContext));
  context.setvalue(nameast->name, this->type, inst);
  if (this->init != nullptr) {
    // thlang::ExprAst* exprast = new thlang::ExprAst(*(this->init.get()));
    auto initExpr = dynamic_cast<thlang::ExprAst *>(this->init.get());
    if (initExpr == nullptr) {
      return LogError("初始化表达式类型不匹配");
    }
    thlang::AssignAst assignment(
        std::make_unique<thlang::NameAst>(nameast->name),
        std::move(this->init));
    assignment.codegen(context);
  }
  return inst;
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
  llvm::Value *returnValue = this->expr->codegen(context);
  context.builder.CreateRet(returnValue);
  return returnValue;
}

llvm::Value *FunctionStmtAst::codegen(thlang::CodeGenContext &context) {
  std::vector<llvm::Type *> argTypes;
  if (!this->args->empty()) {
    for (const auto &arg : *this->args) {
      // TODO:argTypes.push_back(context.typeSystem.get_llvm_type(arg->type));
      argTypes.push_back(llvm::Type::getInt32Ty(context.getContext()));
    }
  }
  // TODO:
  // llvm::Type* retType = context.typeSystem.get_llvm_type(this->type);
  llvm::Type *retType = llvm::Type::getInt32Ty(context.getContext());

  llvm::FunctionType *functionType =
      llvm::FunctionType::get(retType, argTypes, false);
  thlang::NameAst *function_name =
      static_cast<thlang::NameAst *>(this->name.get());
  llvm::Function *function = llvm::Function::Create(
      functionType, llvm::GlobalValue::ExternalLinkage,
      function_name->name.c_str(), context.theModule.get());

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
      thlang::Type arg_type = (*origin_arg)->type;
      llvm::Type *arg_type_llvm = context.typeSystem.get_llvm_type(arg_type);
      ir_arg_it.setName(arg_name->name);
      // TODO:llvm::Value* argAlloc = context.builder.CreateAlloca(arg_type,
      // nullptr, ir_arg_it.getName().str() + ".addr");
      llvm::Value *argAlloc = context.builder.CreateAlloca(
          llvm::Type::getInt32Ty(context.getContext()), nullptr,
          ir_arg_it.getName().str() + ".addr");
      context.builder.CreateStore(&ir_arg_it, argAlloc);
      context.setvalue(arg_name->name, arg_type, argAlloc);
      origin_arg++;
      argNo++;
    }

    // 生成函数体代码
    this->block->codegen(context);
  }

  return function;
}

} // namespace thlang

llvm::Value *LogError(std::string str) {
  std::cerr << str << "\n";
  return nullptr;
}

llvm::Value *LogError(const char *str) { return LogError(str); }