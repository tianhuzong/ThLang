#ifndef THLANG_SEMA_H
#define THLANG_SEMA_H

#include "TypeSystem.h"
#include "node.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace thlang {

// 符号类
class Symbol {
public:
    std::string name;     // 符号名称
    thlang::Type type;                    // 符号类型
    bool isFunctionArg; // 是否为函数参数
    bool isClassMember; // 是否为类成员
    llvm::Value *value; // 对应的 LLVM Value（用于代码生成）

    // 默认构造函数
    Symbol()
            : name(""), type(Type()), isFunctionArg(false), isClassMember(false),
                value(nullptr) {}

    // 带参数的构造函数
    Symbol(std::string name, Type type, bool isFunctionArg = false,
                 bool isClassMember = false)
            : name(name), type(type), isFunctionArg(isFunctionArg),
                isClassMember(isClassMember), value(nullptr) {}
};

// 作用域类
class Scope {
private:
    std::unordered_map<std::string, Symbol> symbols; // 当前作用域的符号表

public:
    // 添加符号
    bool addSymbol(const Symbol &symbol) {
        if (symbols.find(symbol.name) != symbols.end()) {
            return false; // 符号已存在
        }
        symbols[symbol.name] = symbol;
        return true;
    }

    // 查找符号
    Symbol *lookupSymbol(const std::string &name) {
        auto it = symbols.find(name);
        if (it != symbols.end()) {
            return &it->second;
        }
        return nullptr; // 符号未找到
    }
};

// 作用域栈
class ScopeStack {
private:
    std::vector<Scope> scopes; // 作用域栈

public:
    // 进入新的作用域
    void pushScope() { scopes.push_back(Scope()); }

    // 退出当前作用域
    void popScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
        }
    }

    // 添加符号到当前作用域
    bool addSymbol(const Symbol &symbol) {
        if (scopes.empty()) {
            return false;
        }
        return scopes.back().addSymbol(symbol);
    }

    // 查找符号（从当前作用域向外查找）
    Symbol *lookupSymbol(const std::string &name) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            Symbol *symbol = it->lookupSymbol(name);
            if (symbol) {
                return symbol;
            }
        }
        return nullptr; // 符号未找到
    }
};

// 语义分析类
class Sema {
private:
    ScopeStack scopeStack;    // 作用域栈
    TypeSystem &typeSystem; // 类型系统

public:
    Sema(TypeSystem &typeSystem) : typeSystem(typeSystem) {
        scopeStack.pushScope(); // 初始化全局作用域
    }

    // 进入新的作用域
    void enterScope() { scopeStack.pushScope(); }

    // 退出当前作用域
    void exitScope() { scopeStack.popScope(); }

    // 添加符号到当前作用域
    bool addSymbol(const Symbol &symbol) { return scopeStack.addSymbol(symbol); }

    // 查找符号
    Symbol *lookupSymbol(const std::string &name) {
        return scopeStack.lookupSymbol(name);
    }

    // 类型检查：确保两个类型兼容
    bool checkTypeCompatibility(Type type1, Type type2);

    // 检查变量声明
    bool checkVariableDeclaration(const std::string &name, Type type);

    // 检查函数调用
    bool checkFunctionCall(const std::string &name,
                                                 const std::vector<Type> &argTypes);

    // 检查赋值操作
    bool checkAssignment(Type lhsType, Type rhsType);

    // 语义分析函数
    bool analyze(thlang::Node *node);
};

} // namespace thlang

#endif // THLANG_SEMA_H