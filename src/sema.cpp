#include <thlang/sema.h>
#include <iostream>

namespace thlang {
/*
// 类型检查：确保两个类型兼容
bool Sema::checkTypeCompatibility(Type type1, Type type2) {
    return type1.get_type_name() == type2.get_type_name();
}

// 检查变量声明
bool Sema::checkVariableDeclaration(const std::string &name, Type type) {
    if (lookupSymbol(name)) {
        std::cerr << "错误：变量 '" << name << "' 已定义" << std::endl;
        return false; // 变量已存在
    }
    return addSymbol(Symbol(name, type));
}

// 检查函数调用
bool Sema::checkFunctionCall(const std::string &name,
                                                         const std::vector<Type> &argTypes) {
    Symbol *symbol = lookupSymbol(name);
    if (!symbol) {
        std::cerr << "错误：函数 '" << name << "' 未定义" << std::endl;
        return false; // 函数未定义
    }
    if (symbol->type.get_type_name() != "函数") {
        std::cerr << "错误：'" << name << "' 不是函数" << std::endl;
        return false; // 不是函数类型
    }
    // TODO: 检查参数类型是否匹配
    return true;
}

// 检查赋值操作
bool Sema::checkAssignment(Type lhsType, Type rhsType) {
    if (!checkTypeCompatibility(lhsType, rhsType)) {
        std::cerr << "错误：赋值操作类型不兼容" << std::endl;
        return false;
    }
    return true;
}

// 语义分析函数
bool Sema::analyze(thlang::Node *node) {
    if (!node) {
        return true; // 空节点，跳过
    }

    // 根据节点类型调用相应的语义检查逻辑
    switch (node->getKind()) {
    case thlang::VariableDecl: {
        auto *decl = static_cast<VariableDeclAst *>(node);
        if (!checkVariableDeclaration(decl->name, decl->type)) {
            return false;
        }
        break;
    }
    case thlang::Assignment: {
        auto *assign = static_cast<AssignmentAst *>(node);
        Type lhsType = assign->lhs->getType();
        Type rhsType = assign->rhs->getType();
        if (!checkAssignment(lhsType, rhsType)) {
            return false;
        }
        break;
    }
    case thlang::FunctionCall: {
        auto *call = static_cast<FunctionCallAst *>(node);
        std::vector<Type> argTypes;
        for (auto &arg : call->args) {
            argTypes.push_back(arg->getType());
        }
        if (!checkFunctionCall(call->name, argTypes)) {
            return false;
        }
        break;
    }
    case thlang::NBlock: {
        auto *block = static_cast<NBlock *>(node);
        enterScope(); // 进入新的作用域
        for (auto &stmt : block->stmts) {
            if (!analyze(stmt.get())) {
                return false;
            }
        }
        exitScope(); // 退出作用域
        break;
    }
    default:
        // 其他节点类型，递归分析子节点
        for (auto &child : node->getChildren()) {
            if (!analyze(child.get())) {
                return false;
            }
        }
        break;
    }

    return true;
}
*/
} // namespace thlang

