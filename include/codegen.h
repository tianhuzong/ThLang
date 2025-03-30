#ifndef THLANG_CODEGEN_H
#define THLANG_CODEGEN_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h> // 新增：TargetRegistry支持
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h> // 新增：getDefaultTargetTriple支持
#include <optional>
#include <unordered_map>
#include <vector>

#include "TypeSystem.h"
#include "node.h"
#include "sema.h"

namespace thlang {

using _Symbol = std::pair<thlang::Type, llvm::Value *>;

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
  thlang::Sema sema; // 新增：语义分析模块
  std::unique_ptr<llvm::Module> theModule;
  std::unordered_map<std::string, thlang::_Symbol> globals;
  std::vector<thlang::Type> types;
  std::string ObjCode;
  std::string moduleName;

  CodeGenContext(std::string moduleName = "main")
      : builder(llvmContext), typeSystem(llvmContext),
        sema(typeSystem) { // 初始化 Sema
    this->moduleName = llvm::sys::path::filename(moduleName).str();
    theModule = std::make_unique<llvm::Module>("main", this->llvmContext);
  }

  void codegen(NModule &root);

  std::unordered_map<std::string, thlang::_Symbol> getlocals() {
    return blocks.back()->locals;
  }

  llvm::Value *getvalue(std::string name) {
    for (auto it : blocks) {
      if (it->locals.find(name) != it->locals.end()) {
        return it->locals[name].second;
      }
    }
    return nullptr;
  }

  thlang::Type getvalueType(std::string name) {
    for (auto it : blocks) {
      if (it->locals.find(name) != it->locals.end()) {
        return it->locals[name].first;
      }
    }
    return thlang::Type();
  }

  void setvalue(std::string name, thlang::Type type, llvm::Value *value) {
    blocks.back()->locals[name] =
        std::pair<thlang::Type, llvm::Value *>(type, value);
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
  }

  llvm::LLVMContext &getContext() { return llvmContext; }

  void objgen() {
    // 验证模块
    bool haserror = llvm::verifyModule(*theModule, &llvm::errs());
    if (haserror) {
      return;
    }

    // 获取目标三元组
    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    this->theModule->setTargetTriple(targetTriple);

    // 查找目标
    std::string error;
    auto Target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    if (!Target) {
      llvm::errs() << error;
      return;
    }

    // 配置目标机器
    auto CPU = "generic";
    auto features = "";
    llvm::TargetOptions opt;
    llvm::Reloc::Model RM = llvm::Reloc::Static;
    auto theTargetMachine =
        Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    // 设置模块数据布局
    this->theModule->setDataLayout(theTargetMachine->createDataLayout());

    // 创建输出文件
    std::error_code EC;
    llvm::raw_fd_ostream dest(moduleName + ".o", EC);

    // 配置PassManager
    llvm::legacy::PassManager pass;
    auto fileType = llvm::CodeGenFileType::ObjectFile;

    // 添加文件生成Pass
    if (theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
      llvm::errs() << "theTargetMachine can't emit a file of this type";
      return;
    }

    // 运行Pass并生成目标文件
    pass.run(*this->theModule.get());
    dest.flush();
  }
};
} // namespace thlang

llvm::Value *LogError(const char *str);
llvm::Value *LogError(std::string str);

#endif