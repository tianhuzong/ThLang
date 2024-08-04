#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include <memory>
#include <iostream>
#include <unordered_map>
using namespace llvm;
void print_value(long double something);
void print_value(long long something);
void print_value(std::string something);



class CodeGenContext ;
class Node {
public:
	virtual ~Node() {};
	virtual Value* codeGen(CodeGenContext& context) { return NULL; }
};

class ExprAst : public Node{};
class StmtAst : public Node{};
class ConstantAst : public Node{};


class IntAst : public ConstantAst {
    public:
        virtual ~IntAst() {};
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



