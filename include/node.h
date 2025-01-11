#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include <memory>
#include <iostream>
#include <unordered_map>
using namespace llvm;




//TODO: 使用命名空间
/*
namespace thlang {
class Node{
    public:
        virtual ~Node() = default;
        virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
        virtual void unparse() { return ""; }; //TODO: 设置为纯虚函数，子类必须实现
}

// 模块节点: NModule
class NModule : public Node {
    public:
        std::vector<std::unique_ptr<Node>> nodes;
        NModule(std::vector<std::unique_ptr<Node>> nodes) : nodes(std::move(nodes)) {}
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
}

// 块级节点: NBlock
class NBlock : public Node {
    public:
        std::vector<std::unique_ptr<Node>> nodes;
        NBlock(std::vector<std::unique_ptr<Node>> nodes) : nodes(std::move(nodes)) {}
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
}

class ExprAst : Node {}; //表达式节点的基类
class StmtAst : Node {}; //常量节点的基类

// 常量节点: 整数Int 长整数LongLongInt 小数Float 双精度小数Double 字符串String 布尔值Bool
class IntAst : ExprAst {
    public:
        int value;
        IntAst(int value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class LongLongIntAst : ExprAst {
    public:
        long long value;
        LongLongIntAst(long long value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class FloatAst : ExprAst {
    public:
        float value;
        FloatAst(float value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class DoubleAst : ExprAst {
    public:
        double value;
        DoubleAst(double value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class StringAst : ExprAst {
    public:
        std::string value;
        StringAst(std::string value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class BoolAst : ExprAst {
    public:
        bool value;
        BoolAst(bool value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

// 表达式节点: 标识符Name 一元表达式UnOp  二元表达式BinOp 赋值表达式 Assign 函数调用表达式Call
class NameAst : ExprAst {
    public:
        std::string name;
        NameAst(std::string name) : name(name){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class UnOpAst : ExprAst {
    public:
        char* op;
        std::unique_ptr<ExprAst> expr;
        UnOpAst(char op, std::unique_ptr<ExprAst> expr) : op(op), expr(std::move(expr)) {}
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class BinOpAst : ExprAst {
    public:
        char* op;
        std::unique_ptr<ExprAst> left;
        std::unique_ptr<ExprAst> right;
        BinOpAst(char op, std::unique_ptr<ExprAst> left, std::unique_ptr<ExprAst> right) : op(op), left(std::move(left)), right(std::move(right)) {}
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

class AssignAst : StmtAst {
    public:
        std::unique_ptr<NameAst> name; //左值
        std::unique_ptr<ExprAst> expr; //右值
        AssignAst(std::unique_ptr<NameAst> name, std::unique_ptr<ExprAst> expr) : name(std::move(name)), expr(std::move(expr)) {}
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
        virtual void unparse();
};

}
*/

class Node {
public:
    //Node() = default;
	virtual ~Node() = default;
	virtual Value* codeGen(CodeGenContext& context) { return NULL; }
};

class ExprAst : public Node{};
class StmtAst : public Node{};
class ConstantAst : public Node{};


class IntAst : public ConstantAst {
    public:
        long long value;
        IntAst(long long value) : value(value){};
        virtual Value* codeGen(CodeGenContext& context) ;
};

class FloatAst : public ConstantAst {
    public:
        long double value;
        FloatAst(long double value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
};

class StringAst : public ConstantAst {
    public:
        std::string value;
        StringAst(std::string value) : value(value){};
        virtual llvm::Value* codeGen(CodeGenContext& context) ;
};


class NameAst : public ExprAst{
    public:
        std::string name;
        NameAst(std::string name) : name(name){};
        virtual Value* codeGen(CodeGenContext& context) ;
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



