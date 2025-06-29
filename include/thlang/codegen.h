#pragma once
#ifndef THLANG_CODEGEN_H
#define THLANG_CODEGEN_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/IRReader/IRReader.h" 
#include "llvm/AsmParser/Parser.h"
#include "llvm/Support/MemoryBuffer.h"
#include <cstdio>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/SourceMgr.h>
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

extern thlang::TypeSystem type_System;

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
    llvm::LLVMContext& llvmContext = type_System.getContext();
    llvm::IRBuilder<> builder;
    thlang::TypeSystem& typeSystem ;
    std::unique_ptr<llvm::Module> theModule;
    std::unordered_map<std::string, thlang::_Symbol> globals;
    std::vector<thlang::Type> types;
    std::string ObjCode;
    std::string moduleName;
    CodeGenContext(std::string moduleName = "main")
            : builder(llvmContext), typeSystem(type_System) {
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

    void asmgen(FILE* output_file) {
        if (!theModule) {
            llvm::errs() << "Error: Module is null\n";
            return;
        }

        // 初始化LLVM目标架构
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();

        // 获取当前主机的目标三元组
        auto targetTriple = llvm::sys::getDefaultTargetTriple();
        theModule->setTargetTriple(targetTriple);

        std::string error;
        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

        if (!target) {
            llvm::errs() << "Error: " << error << "\n";
            return;
        }

        // 配置目标机器
        auto cpu = "generic";
        auto features = "";
        llvm::TargetOptions opt;
        auto RM = std::optional<llvm::Reloc::Model>();
        auto targetMachine = target->createTargetMachine(
            targetTriple, cpu, features, opt, RM);

        theModule->setDataLayout(targetMachine->createDataLayout());

        // 打开文件描述符
        int fd = fileno(output_file);
        if (fd == -1) {
            llvm::errs() << "Error getting file descriptor\n";
            return;
        }

        // 创建输出流
        llvm::raw_fd_ostream dest(fd, /*shouldClose=*/false);
        
        // 配置输出文件类型为汇编文件
        llvm::legacy::PassManager pass;
        auto fileType = llvm::CodeGenFileType::AssemblyFile;

        // 生成汇编代码
        if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
            llvm::errs() << "TargetMachine can't emit a file of this type\n";
            return;
        }

        pass.run(*theModule);
        dest.flush();
    }

    void objgen(FILE* output_file) {
        if (!theModule) {
            llvm::errs() << "Error: Module is null\n";
            return;
        }

        // 初始化LLVM目标架构
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();

        // 获取当前主机的目标三元组
        auto targetTriple = llvm::sys::getDefaultTargetTriple();
        theModule->setTargetTriple(targetTriple);

        std::string error;
        auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

        if (!target) {
            llvm::errs() << "Error: " << error << "\n";
            return;
        }

        // 配置目标机器
        auto cpu = "generic";
        auto features = "";
        llvm::TargetOptions opt;
        auto RM = std::optional<llvm::Reloc::Model>();
        auto targetMachine = target->createTargetMachine(
            targetTriple, cpu, features, opt, RM);

        theModule->setDataLayout(targetMachine->createDataLayout());

        // 打开文件描述符
        int fd = fileno(output_file);
        if (fd == -1) {
            llvm::errs() << "Error getting file descriptor\n";
            return;
        }

        // 创建输出流
        llvm::raw_fd_ostream dest(fd, /*shouldClose=*/false);
        
        // 配置输出文件类型
        llvm::legacy::PassManager pass;
        auto fileType = llvm::CodeGenFileType::ObjectFile;

        // 生成目标代码
        if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
            llvm::errs() << "TargetMachine can't emit a file of this type\n";
            return;
        }

        pass.run(*theModule);
        dest.flush();
    }
};
} // namespace thlang

std::unique_ptr<llvm::Module> parseIRFromString(llvm::LLVMContext& context, 
                                              const std::string& irText);

llvm::Value *LogError(const char *str);
llvm::Value *LogError(std::string str);

#endif
