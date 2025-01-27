#ifndef THLANG_NODE_H
#define THLANG_NODE_H
#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <iostream>
#include <unordered_map>
#include "TypeSystem.h"


//TODO: 使用命名空间

namespace thlang {

class CodeGenContext;
class VarStmtAst;
class ExprAst;
using VarList = std::vector<std::shared_ptr<VarStmtAst>>;
using ExprList = std::vector<std::shared_ptr<ExprAst>> ;

class Node{
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codegen(thlang::CodeGenContext& context)  = 0;
        virtual void unparse() = 0; //TODO: 设置为纯虚函数，子类必须实现
};

class ExprAst : public Node {

}; //表达式节点的基类
class StmtAst : public  Node {

}; //常量节点的基类

// 块级节点: NBlock
class NBlock : public Node {
    public:
        std::shared_ptr<std::vector<std::shared_ptr<thlang::Node>>> stmts = std::make_shared<std::vector<std::shared_ptr<thlang::Node>>>();
        NBlock() {}
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};



// 模块节点: NModule
class NModule : public Node {
    public:
        std::shared_ptr<thlang::Node> block ;
        NModule(){}
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};


// 常量节点: 整数Int 小数Float  字符串String 布尔值Bool
class IntAst : public  ExprAst {
    public:
        int value;
        thlang::Type type;
        IntAst(int value, thlang::Type type) : value(value), type(type){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

class FloatAst : public  ExprAst {
    public:
        long double value;
        FloatAst(long double value) : value(value){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

class StringAst : public  ExprAst {
    public:
        std::string value;
        StringAst(std::string value) : value(value){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

class BoolAst : public  ExprAst {
    public:
        bool value;
        BoolAst(bool value) : value(value){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse() override;
};

// 表达式节点: 标识符Name 一元表达式UnOp  二元表达式BinOp 赋值表达式 Assign 函数调用表达式Call
class NameAst : public  ExprAst {
    public:
        std::string name;
        NameAst(std::string name) : name(name){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

class UnOpAst : public ExprAst {
    public:
        std::string op;
        std::shared_ptr<thlang::Node> expr;
        UnOpAst(std::string op, std::shared_ptr<thlang::Node> expr) : op(op), expr((expr)) {}
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse() override;
};

class BinOpAst : public ExprAst {
    public:
        std::string op;
        std::shared_ptr<thlang::Node> left;
        std::shared_ptr<thlang::Node> right;
        BinOpAst(std::string op, std::shared_ptr<thlang::Node> left, std::shared_ptr<thlang::Node> right) : op(op), left((left)), right((right)) {}
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

class AssignAst : public ExprAst {
    public:
        std::shared_ptr<thlang::Node> name; //左值
        std::shared_ptr<thlang::Node> expr; //右值
        AssignAst(std::shared_ptr<thlang::Node> name, std::shared_ptr<thlang::Node> expr) : name((name)), expr((expr)) {}
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
        virtual void unparse();
};

// 语句节点 : 表达式语句 赋值语句 if语句 for语句 while语句 函数定义语句 返回值语句 类定义语句

class ExprStmtAst : public StmtAst{
public:
    std::shared_ptr<thlang::Node> expr;
    ExprStmtAst(std::shared_ptr<thlang::Node> expr) : expr((expr)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class VarStmtAst : public StmtAst {
public:
    thlang::Type type;
    std::shared_ptr<thlang::Node> name;
    std::shared_ptr<thlang::Node> init;
    VarStmtAst(thlang::Type type, std::shared_ptr<thlang::Node> name, std::shared_ptr<thlang::Node> init = nullptr) : type(type), name((name)), init((init)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class IfStmtAst : public StmtAst {
public:
    std::shared_ptr<thlang::Node> condition;
    std::shared_ptr<thlang::Node> thenStmt;
    std::shared_ptr<thlang::Node> elseStmt;
    IfStmtAst(std::shared_ptr<thlang::Node> condition, std::shared_ptr<thlang::Node> thenStmt, std::shared_ptr<thlang::Node> elseStmt = nullptr) : condition((condition)), thenStmt((thenStmt)), elseStmt((elseStmt)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class ForStmtAst : public StmtAst {
public:
    std::shared_ptr<thlang::Node> init;
    std::shared_ptr<thlang::Node> condition;
    std::shared_ptr<thlang::Node> increment;
    std::shared_ptr<thlang::Node> body;
    ForStmtAst(std::shared_ptr<thlang::Node> init, std::shared_ptr<thlang::Node> condition, std::shared_ptr<thlang::Node> increment, std::shared_ptr<thlang::Node> body) : init((init)), condition((condition)), increment((increment)), body((body)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class WhileStmtAst : public StmtAst {
public:
    std::shared_ptr<thlang::Node> condition;
    std::shared_ptr<thlang::Node> body;
    WhileStmtAst(std::shared_ptr<thlang::Node> condition, std::shared_ptr<thlang::Node> body) : condition((condition)), body((body)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class ReturnStmtAst : public StmtAst {
public:
    std::shared_ptr<thlang::Node> expr;
    ReturnStmtAst(std::shared_ptr<thlang::Node> expr) : expr((expr)) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};   

class FunctionStmtAst : public StmtAst {
public:
    thlang::Type type;
    std::shared_ptr<thlang::Node> name;
    std::shared_ptr<VarList> args = std::make_shared<VarList>();
    std::shared_ptr<thlang::Node> block;
    bool is_extern;
    FunctionStmtAst(thlang::Type type, std::shared_ptr<thlang::Node> name, std::shared_ptr<VarList> args, std::shared_ptr<thlang::Node> block, bool is_extern = false) : type(type), name((name)), args((args)), block((block)), is_extern(is_extern) {};
    virtual llvm::Value* codegen(CodeGenContext& context) override; 
    virtual void unparse() override;
};

class ClassStmtAst : public StmtAst {};

}

/*
class Node {
public:
    //Node() = default;
	virtual ~Node() = default;
	virtual Value* codegen(thlang::CodeGenContext& context) = 0;
};

class ExprAst : public Node{};
class StmtAst : public Node{};
class ConstantAst : public Node{};


class IntAst : public ConstantAst {
    public:
        long long value;
        IntAst(long long value) : value(value){};
        virtual Value* codegen(thlang::CodeGenContext& context) ;
};

class FloatAst : public ConstantAst {
    public:
        long double value;
        FloatAst(long double value) : value(value){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
};

class StringAst : public ConstantAst {
    public:
        std::string value;
        StringAst(std::string value) : value(value){};
        virtual llvm::Value* codegen(thlang::CodeGenContext& context) override ;
};


class NameAst : public ExprAst{
    public:
        std::string name;
        NameAst(std::string name) : name(name){};
        virtual Value* codegen(thlang::CodeGenContext& context) ;
};

class BlockAst_temp{
    public:

};



class Type_{
    Type_();
};
class Value {
public:
    Value() = default;
    Value(const char* a) : str_(a) {std::cout << "Value(const char* a) is " << a << std::endl; }
    static Value fromString(const char* a) { return Value(a); }
private:
    std::string str_;
};
*/

#endif   // THLANG_NODE_H

