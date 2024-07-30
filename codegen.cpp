#include "nn.h"
llvm::LLVMContext MyContext;
Module *module = new Module("module",MyContext);


llvm::Value* IntAst::codeGen(CodeGenContext& context){
    return llvm::ConstantInt::get(Type::getInt64Ty(MyContext), value, true);
}

llvm::Value* FloatAst::codeGen(CodeGenContext& context){
    return llvm::ConstantFP::get(Type::getDoubleTy(MyContext), value);
}

llvm::Value* StringAst::codeGen(CodeGenContext& context){
    llvm::Constant *strConst1 = llvm::ConstantDataArray::getString(MyContext,
			value);
	llvm::Value *globalVar1 = new llvm::GlobalVariable(*module,
			strConst1->getType(), true, llvm::GlobalValue::PrivateLinkage,
			strConst1, Twine(""));
	return globalVar1;
}
