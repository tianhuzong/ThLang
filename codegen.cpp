#include "nn.h"
#include "codegen.h"

std::unordered_map<std::string, llvm::Value*> symTable;
bool is_in_debug = true; //TODO:remove

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
        std::cout.precision(14);
        std::cout << "\033[31m打印浮点数" << something << "\033[0m\n";
    }
}

void CodeGenContext::codeGen(std::vector<Node*> nodes){
    for (auto node : nodes){
        node->codeGen(*this);
    }
}


llvm::Value* IntAst::codeGen(CodeGenContext& context){
	print_value(value);
	llvm::Value * res = llvm::ConstantInt::get(Type::getInt64Ty(MyContext), value, true);
    return res;
}

llvm::Value* FloatAst::codeGen(CodeGenContext& context){
	print_value(value);
    return llvm::ConstantFP::get(Type::getDoubleTy(MyContext), value);
}

llvm::Value* StringAst::codeGen(CodeGenContext& context){
	print_value(value);
    llvm::Constant *strConst1 = llvm::ConstantDataArray::getString(MyContext,
			value);
	llvm::Value *globalVar1 = new llvm::GlobalVariable(*context.module,
			strConst1->getType(), true, llvm::GlobalValue::PrivateLinkage,
			strConst1, Twine(".str"+std::to_string(value.size())));
	symTable[value] = globalVar1;
	return globalVar1;
}


llvm::Value* NameAst::codeGen(CodeGenContext& context){
    print_value(name);
    //TODO:修改字段
    //return new LoadInst(context.locals()[name]->getType(),context.locals()[name], name, false, context.currentBlock());
    return  llvm::ConstantInt::get(Type::getInt64Ty(MyContext), 0, true);
}
