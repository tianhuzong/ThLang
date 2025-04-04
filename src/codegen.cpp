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
    last = it->codegen(context);
  }
  return last;
}

llvm::Value *IntAst::codegen(thlang::CodeGenContext &context) {
  this->type = std::make_unique<thlang::Type>("整数型");
  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.getContext()),
                                value, true);
}

llvm::Value *FloatAst::codegen(thlang::CodeGenContext &context) {
  this->type = std::make_unique<thlang::Type>("小数型");
  return llvm::ConstantFP::get(llvm::Type::getDoubleTy(context.getContext()),
                               value);
}

llvm::Value *StringAst::codegen(thlang::CodeGenContext &context) {
  this->type = std::make_unique<thlang::Type>("字符串");
  return context.builder.CreateGlobalString(value);
}

llvm::Value *BoolAst::codegen(thlang::CodeGenContext &context) {
  this->type = std::make_unique<thlang::Type>("布尔型");
  return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.getContext()),
                                value);
}

llvm::Value *NameAst::codegen(thlang::CodeGenContext &context) {
  llvm::Value *value = context.getvalue(this->name);
  if (!value) {
    LogError("Name " + this->name + " is not defined");
  }
  this->type =
      std::make_unique<thlang::Type>(*context.getvalueType(this->name));
  return context.builder.CreateLoad(
      context.typeSystem.get_llvm_type(*this->type), value, false);
}

llvm::Value *UnOpAst::codegen(thlang::CodeGenContext &context) {
  llvm::Value *un_expr = this->expr->codegen(context);
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
    return nullptr;
  }
}

llvm::Value *BinOpAst::codegen(thlang::CodeGenContext &context) {
  llvm::Value *lhs = this->left->codegen(context);
  llvm::Value *rhs = this->right->codegen(context);

  auto left = static_cast<thlang::ExprAst *>(this->left.get());
  auto right = static_cast<thlang::ExprAst *>(this->right.get());

  if (!lhs || !rhs) {
    return nullptr;
  }

  lhs = context.builder.CreateLoad(
      context.typeSystem.get_llvm_type(*left->get_type()), lhs, "load_lhs");
  rhs = context.builder.CreateLoad(
      context.typeSystem.get_llvm_type(*right->get_type()), rhs, "load_rhs");

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
}

llvm::Value *AssignAst::codegen(thlang::CodeGenContext &context) {
  auto nameast = static_cast<thlang::NameAst *>((this->name).get());
  llvm::Value *dst = context.getvalue(nameast->name);
  if (!dst) {
    return LogError("未定义的标识符: " + nameast->name);
  }

  llvm::Value *exp = this->expr->codegen(context);
  if (!exp) {
    return LogError("表达式生成失败");
  }

  context.builder.CreateStore(exp, dst);
  return dst;
}

llvm::Value *ExprStmtAst::codegen(thlang::CodeGenContext &context) {
  return this->expr->codegen(context);
}

llvm::Value *VarStmtAst::codegen(thlang::CodeGenContext &context) {
  auto nameast = static_cast<thlang::NameAst *>(this->name.get());
  llvm::Type *llvmType = context.typeSystem.get_llvm_type(*this->type);
  llvm::Value *inst =
      context.builder.CreateAlloca(llvmType, nullptr, nameast->name.c_str());

  context.setvalue(nameast->name, std::move(this->type), inst);

  if (this->init != nullptr) {
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

// ... [保留 IfStmtAst、ForStmtAst、WhileStmtAst 的实现，它们不需要修改] ...

llvm::Value *FunctionStmtAst::codegen(thlang::CodeGenContext &context) {
  std::vector<llvm::Type *> argTypes;
  for (const auto &arg : *this->args) {
    argTypes.push_back(context.typeSystem.get_llvm_type(*arg->type));
  }

  llvm::Type *retType = context.typeSystem.get_llvm_type(*this->type);
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

    auto origin_arg = this->args->begin();
    for (auto &ir_arg_it : function->args()) {
      thlang::NameAst *arg_name =
          static_cast<thlang::NameAst *>((*origin_arg)->name.get());
      llvm::Type *arg_type_llvm =
          context.typeSystem.get_llvm_type(*(*origin_arg)->type);
      ir_arg_it.setName(arg_name->name);
      llvm::Value *argAlloc = context.builder.CreateAlloca(
          arg_type_llvm, nullptr, ir_arg_it.getName().str() + ".addr");
      context.builder.CreateStore(&ir_arg_it, argAlloc);
      context.setvalue(arg_name->name, std::move((*origin_arg)->type),
                       argAlloc);
      origin_arg++;
    }

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