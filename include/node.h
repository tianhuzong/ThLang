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

// TODO: 使用命名空间

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
    virtual void unparse() = 0; // TODO: 设置为纯虚函数，子类必须实现
};

class ExprAst : public Node {}; // 表达式节点的基类
class StmtAst : public Node {}; // 常量节点的基类

// 块级节点: NBlock
class NBlock : public Node {
public:
    std::unique_ptr<std::vector<std::unique_ptr<thlang::Node>>> stmts =
            std::make_unique<std::vector<std::unique_ptr<thlang::Node>>>();
    NBlock() {}
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

// 模块节点: NModule
class NModule : public Node {
public:
    std::unique_ptr<thlang::Node> block;
    NModule() {}
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

// 常量节点: 整数Int 小数Float    字符串String 布尔值Bool
class IntAst : public ExprAst {
public:
    long long value;
    thlang::Type type = thlang::Type("整数型");
    IntAst(long long value) : value(value){};
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

class FloatAst : public ExprAst {
public:
    long double value;
    FloatAst(long double value) : value(value){};
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

class StringAst : public ExprAst {
public:
    std::string value;
    StringAst(std::string value) : value(value){};
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

class BoolAst : public ExprAst {
public:
    bool value;
    BoolAst(bool value) : value(value){};
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse() override;
};

// 表达式节点: 标识符Name 一元表达式UnOp    二元表达式BinOp 赋值表达式 Assign
// 函数调用表达式Call
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
    std::unique_ptr<thlang::Node> name; // 左值
    std::unique_ptr<thlang::Node> expr; // 右值
    AssignAst(std::unique_ptr<thlang::Node> name,
                        std::unique_ptr<thlang::Node> expr)
            : name(std::move(name)), expr(std::move(expr)) {}
    virtual llvm::Value *codegen(thlang::CodeGenContext &context) override;
    virtual void unparse();
};

// 语句节点 : 表达式语句 赋值语句 if语句 for语句 while语句 函数定义语句
// 返回值语句 类定义语句

class ExprStmtAst : public StmtAst {
public:
    std::unique_ptr<thlang::Node> expr;
    ExprStmtAst(std::unique_ptr<thlang::Node> expr) : expr(std::move(expr)){};
    virtual llvm::Value *codegen(CodeGenContext &context) override;
    virtual void unparse() override;
};

class VarStmtAst : public StmtAst {
public:
    thlang::Type *type;
    std::unique_ptr<thlang::Node> name;
    std::unique_ptr<thlang::Node> init;
    VarStmtAst(thlang::Type *type, std::unique_ptr<thlang::Node> name,
                         std::unique_ptr<thlang::Node> init = nullptr)
            : type(type), name(std::move(name)), init(std::move(init)){};
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
    thlang::Type *type;
    std::unique_ptr<thlang::Node> name;
    std::unique_ptr<VarList> args = std::make_unique<VarList>();
    std::unique_ptr<thlang::Node> block;
    bool is_extern;
    FunctionStmtAst(thlang::Type *type, std::unique_ptr<thlang::Node> name,
                                    std::unique_ptr<VarList> args,
                                    std::unique_ptr<thlang::Node> block, bool is_extern = false)
            : type(type), name(std::move(name)), args(std::move(args)),
                block(std::move(block)), is_extern(is_extern){};
    virtual llvm::Value *codegen(CodeGenContext &context) override;
    virtual void unparse() override;
};

class ClassStmtAst : public StmtAst {
public:
};

} // namespace thlang


#endif // THLANG_NODE_H