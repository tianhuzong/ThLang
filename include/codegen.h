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

struct Symbol {
  std::unique_ptr<thlang::Type> type;
  llvm::Value *value;

  Symbol(std::unique_ptr<thlang::Type> t, llvm::Value *v)
      : type(std::move(t)), value(v) {}

  // 移动构造函数
  Symbol(Symbol &&other) noexcept
      : type(std::move(other.type)), value(other.value) {}

  // 禁用拷贝
  Symbol(const Symbol &) = delete;
  Symbol &operator=(const Symbol &) = delete;
};

class CodeGenBlock {
public:
  llvm::BasicBlock *block = nullptr;
  llvm::Value *returnValue = nullptr;
  std::unordered_map<std::string, Symbol> locals;
  std::unordered_map<std::string, bool> isFuncArg;

  CodeGenBlock() = default;

  // 移动构造函数
  CodeGenBlock(CodeGenBlock &&other) noexcept
      : block(other.block), returnValue(other.returnValue),
        locals(std::move(other.locals)), isFuncArg(std::move(other.isFuncArg)) {
    other.block = nullptr;
    other.returnValue = nullptr;
  }

  // 禁用拷贝
  CodeGenBlock(const CodeGenBlock &) = delete;
  CodeGenBlock &operator=(const CodeGenBlock &) = delete;
};

class CodeGenContext {
  std::vector<std::unique_ptr<CodeGenBlock>> blocks;

public:
  llvm::LLVMContext llvmContext;
  llvm::IRBuilder<> builder;
  thlang::TypeSystem typeSystem;
  thlang::Sema sema;
  std::unique_ptr<llvm::Module> theModule;
  std::unordered_map<std::string, Symbol> globals;
  std::vector<std::unique_ptr<thlang::Type>> types;
  std::string ObjCode;
  std::string moduleName;

  CodeGenContext(std::string moduleName = "main")
      : builder(llvmContext), typeSystem(llvmContext), sema(typeSystem) {
    this->moduleName = llvm::sys::path::filename(moduleName).str();
    theModule = std::make_unique<llvm::Module>("main", this->llvmContext);
  }

  void codegen(NModule &root);

  const std::unordered_map<std::string, Symbol> &getlocals() const {
    return blocks.back()->locals;
  }

  llvm::Value *getvalue(const std::string &name) {
    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
      auto found = (*it)->locals.find(name);
      if (found != (*it)->locals.end()) {
        return found->second.value;
      }
    }
    return nullptr;
  }

  std::unique_ptr<thlang::Type> getvalueType(const std::string &name) {
    for (auto it = blocks.rbegin(); it != blocks.rend(); ++it) {
      auto found = (*it)->locals.find(name);
      if (found != (*it)->locals.end()) {
        return std::make_unique<thlang::Type>(*found->second.type);
      }
    }
    return nullptr;
  }

  void setvalue(std::string name, std::unique_ptr<thlang::Type> type,
                llvm::Value *value) {
    blocks.back()->locals.emplace(
        std::piecewise_construct, std::forward_as_tuple(std::move(name)),
        std::forward_as_tuple(std::move(type), value));
  }

  llvm::BasicBlock *currentBlock() {
    return blocks.empty() ? nullptr : blocks.back()->block;
  }

  void pushBlock(llvm::BasicBlock *block) {
    auto newBlock = std::make_unique<CodeGenBlock>();
    newBlock->block = block;
    blocks.push_back(std::move(newBlock));
    builder.SetInsertPoint(block);
  }

  void popBlock() {
    if (!blocks.empty()) {
      blocks.pop_back();
    }
  }

  llvm::LLVMContext &getContext() { return llvmContext; }

  void objgen() {
    bool haserror = llvm::verifyModule(*theModule, &llvm::errs());
    if (haserror) {
      return;
    }

    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    theModule->setTargetTriple(targetTriple);

    std::string error;
    auto Target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
    if (!Target) {
      llvm::errs() << error;
      return;
    }

    auto CPU = "generic";
    auto features = "";
    llvm::TargetOptions opt;
    llvm::Reloc::Model RM = llvm::Reloc::Static;
    auto theTargetMachine =
        Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    theModule->setDataLayout(theTargetMachine->createDataLayout());

    std::error_code EC;
    llvm::raw_fd_ostream dest(moduleName + ".o", EC);

    llvm::legacy::PassManager pass;
    auto fileType = llvm::CodeGenFileType::ObjectFile;

    if (theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
      llvm::errs() << "theTargetMachine can't emit a file of this type";
      return;
    }

    pass.run(*theModule);
    dest.flush();
  }
};
} // namespace thlang

llvm::Value *LogError(const char *str);
llvm::Value *LogError(std::string str);

#endif