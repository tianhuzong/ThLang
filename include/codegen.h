#ifndef THLANG_CODEGEN_H
#define THLANG_CODEGEN_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "TypeSystem.h"
#include "node.h"
#include "sema.h"

namespace thlang {

using _Symbol = std::pair<thlang::Type*, llvm::Value *>;

class CodeGenBlock {
public:
    llvm::BasicBlock *block;
    llvm::Value *returnValue;
    std::unordered_map<std::string, thlang::_Symbol> locals;
    std::unordered_map<std::string, bool> isFuncArg;
};

class CodeGenContext {
    std::vector<CodeGenBlock *> blocks;

public:
    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> builder;
    thlang::TypeSystem typeSystem;
    std::unique_ptr<llvm::Module> theModule;
    std::unordered_map<std::string, thlang::_Symbol> globals;
    std::vector<thlang::Type> types;
    std::string ObjCode;
    std::string moduleName;
    CodeGenContext(std::string moduleName = "main")
            : builder(llvmContext), typeSystem(llvmContext) {
        this->moduleName = llvm::sys::path::filename(moduleName);
        theModule = std::make_unique<llvm::Module>("main", this->llvmContext);
    }
    void codegen(NModule &root);
    std::unordered_map<std::string, thlang::_Symbol> getlocals() {
        return blocks.back()->locals;
    }
    thlang::_Symbol getvalue(std::string name) {
        for (auto it : blocks) {
            if (it->locals.find(name) != it->locals.end()) {
                return it->locals[name];
            }
        }
        return std::make_pair<thlang::Type*, llvm::Value *>(nullptr, nullptr);
    }

    void setvalue(std::string name, thlang::Type* type, llvm::Value *value) {
        blocks.back()->locals[name] =
                std::pair<thlang::Type*, llvm::Value *>(type, value);
    }

    llvm::BasicBlock *currentBlock() { return blocks.back()->block; }
    void pushBlock(llvm::BasicBlock *block) {
        blocks.push_back(new CodeGenBlock());
        blocks.back()->block = block;
        this->builder.SetInsertPoint(block);
    }
    void popBlock() {
        CodeGenBlock *top = blocks.back();
        blocks.pop_back();
        delete top;
    } /*
    void setCurrentReturnValue(llvm::Value *value) {
        blocks.back()->returnValue = value;
        builder.CreateStore(value, returnAlloca);
    }
     void setReturnValueAlloca(llvm::AllocaInst* value) {
             returnAlloca = value;
     }
     llvm::Value* getCurrentReturnValue() {
        return blocks.back()->returnValue;
     */
    llvm::LLVMContext &getContext() { return llvmContext; }
    void objgen() { /*
         bool haserror = llvm::verifyModule(*theModule, &llvm::errs());
         if (haserror) {
             return;
         }
         auto targetTriple = llvm::sys::getDefaultTargetTriple();
         this->theModule->setTargetTriple(targetTriple);

         std::string error;
         auto Target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

         if (!Target) {
             llvm::errs() << error;
             return;
         }

         auto CPU = "generic";
         auto features = "";

         llvm::TargetOptions opt;
         auto RM = llvm::Optional<llvm::Reloc::Model>();
         auto theTargetMachine =
                 Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

         this->theModule->setDataLayout(theTargetMachine->createDataLayout());
         this->theModule->setTargetTriple(targetTriple);
         std::error_code EC;
         llvm::raw_fd_ostream dest(moduleName + ".o", EC, llvm::sys::fs::OF_Text);

         llvm::legacy::PassManager pass;
         auto fileType = llvm::TargetMachine::CGFT_ObjectFile;

         if (theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
             llvm::errs() << "theTargetMachine can't emit a file of this type";
             return;
         }

         pass.run(*this->theModule.get());
         dest.flush();

         return;
     */
    }
};
} // namespace thlang

llvm::Value *LogError(const char *str);
llvm::Value *LogError(std::string str);

#endif
