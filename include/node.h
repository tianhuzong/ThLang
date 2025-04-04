#ifndef THLANG_NODE_H
#define THLANG_NODE_H
#include "TypeSystem.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <memory>
#include <unordered_map>

namespace thlang {

class CodeGenContext;
class VarStmtAst;
class ExprAst;
using VarList = std::vector<std::unique_ptr<VarStmtAst>>;
using ExprList = std::vector<std::unique_ptr<ExprAst>>;

class Node {
public:
  virtual ~Node() = default;
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) = 0;
  virtual void unparse() = 0;
};

class ExprAst : public Node {
public:
  std::unique_ptr<thlang::Type> type;
  virtual std::unique_ptr<thlang::Type> get_type() { return std::move(type); }
};

class StmtAst : public Node {};

class NBlock : public Node {
public:
  std::unique_ptr<std::vector<std::unique_ptr<thlang::Node>>> stmts =
      std::make_unique<std::vector<std::unique_ptr<thlang::Node>>>();
  NBlock() {}
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class NModule : public Node {
public:
  std::unique_ptr<thlang::Node> block;
  NModule() {}
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class IntAst : public ExprAst {
public:
  long long value;
  IntAst(long long value) : value(value) {
    type = std::make_unique<thlang::Type>("整数型");
  };
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class FloatAst : public ExprAst {
public:
  long double value;
  FloatAst(long double value) : value(value) {
    type = std::make_unique<thlang::Type>("小数型");
  };
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class StringAst : public ExprAst {
public:
  std::string value;
  StringAst(std::string value) : value(value) {
    type = std::make_unique<thlang::Type>("字符串");
  };
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class BoolAst : public ExprAst {
public:
  bool value;
  BoolAst(bool value) : value(value) {
    type = std::make_unique<thlang::Type>("布尔型");
  };
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse() override;
};

class NameAst : public ExprAst {
public:
  std::string name;
  NameAst(std::string name) : name(name){};
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class UnOpAst : public ExprAst {
public:
  std::string op;
  std::unique_ptr<thlang::Node> expr;
  UnOpAst(std::string op, std::unique_ptr<thlang::Node> expr)
      : op(op), expr(std::move(expr)) {}
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse() override;
};

class BinOpAst : public ExprAst {
public:
  std::string op;
  std::unique_ptr<thlang::Node> left;
  std::unique_ptr<thlang::Node> right;
  BinOpAst(std::string op, std::unique_ptr<thlang::Node> left,
           std::unique_ptr<thlang::Node> right)
      : op(op), left(std::move(left)), right(std::move(right)) {}
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class AssignAst : public ExprAst {
public:
  std::unique_ptr<thlang::Node> name;
  std::unique_ptr<thlang::Node> expr;
  AssignAst(std::unique_ptr<thlang::Node> name,
            std::unique_ptr<thlang::Node> expr)
      : name(std::move(name)), expr(std::move(expr)) {}
  virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
  virtual void unparse();
};

class ExprStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Node> expr;
  ExprStmtAst(std::unique_ptr<thlang::Node> expr) : expr(std::move(expr)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class VarStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Type> type;
  std::unique_ptr<thlang::Node> name;
  std::unique_ptr<thlang::Node> init;
  VarStmtAst(std::unique_ptr<thlang::Type> type,
             std::unique_ptr<thlang::Node> name,
             std::unique_ptr<thlang::Node> init = nullptr)
      : type(std::move(type)), name(std::move(name)), init(std::move(init)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class IfStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Node> condition;
  std::unique_ptr<thlang::Node> thenStmt;
  std::unique_ptr<thlang::Node> elseStmt;
  IfStmtAst(std::unique_ptr<thlang::Node> condition,
            std::unique_ptr<thlang::Node> thenStmt,
            std::unique_ptr<thlang::Node> elseStmt = nullptr)
      : condition(std::move(condition)), thenStmt(std::move(thenStmt)),
        elseStmt(std::move(elseStmt)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class ForStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Node> init;
  std::unique_ptr<thlang::Node> condition;
  std::unique_ptr<thlang::Node> increment;
  std::unique_ptr<thlang::Node> body;
  ForStmtAst(std::unique_ptr<thlang::Node> init,
             std::unique_ptr<thlang::Node> condition,
             std::unique_ptr<thlang::Node> increment,
             std::unique_ptr<thlang::Node> body)
      : init(std::move(init)), condition(std::move(condition)),
        increment(std::move(increment)), body(std::move(body)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class WhileStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Node> condition;
  std::unique_ptr<thlang::Node> body;
  WhileStmtAst(std::unique_ptr<thlang::Node> condition,
               std::unique_ptr<thlang::Node> body)
      : condition(std::move(condition)), body(std::move(body)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class ReturnStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Node> expr;
  ReturnStmtAst(std::unique_ptr<thlang::Node> expr) : expr(std::move(expr)){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class FunctionStmtAst : public StmtAst {
public:
  std::unique_ptr<thlang::Type> type;
  std::unique_ptr<thlang::Node> name;
  std::unique_ptr<VarList> args = std::make_unique<VarList>();
  std::unique_ptr<thlang::Node> block;
  bool is_extern;
  FunctionStmtAst(std::unique_ptr<thlang::Type> type,
                  std::unique_ptr<thlang::Node> name,
                  std::unique_ptr<VarList> args,
                  std::unique_ptr<thlang::Node> block, bool is_extern = false)
      : type(std::move(type)), name(std::move(name)), args(std::move(args)),
        block(std::move(block)), is_extern(is_extern){};
  virtual llvm::Value *codegen(CodeGenContext &context) override;
  virtual void unparse() override;
};

class ClassStmtAst : public StmtAst {};

} // namespace thlang

#endif // THLANG_NODE_H