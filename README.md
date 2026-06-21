# ThLang
## 天河语言，一款适合新手入门的好语言。
## 开源·简易·可扩展
** 始皇编译器正在开发中**
- - -
## 简介
天河语言（Tianhe Language,Thlang）是一款面向儿童的中文编译型语言，解释器采用C++和LLVM开发。
这个语言结合了python、C/C++、Java等语言的语法。
设计这个语言的目的是为了避免大家在入门其他编程时要理解太多名词，
熟练掌握这个语言，学习其他语言也相对容易。
天狐语言有以下优势：
 - **开源**：这个语言是开源的，无需收费
 - **易上手**：这个语言采用全中文，不需要背诵英语单词，上手简易。
 - **可扩展**：如果你懂C++或者LLVM IR的语法的话可以扩展始皇编译器的标准库。

## 重构计划
重构代码，由AST重构，不需要一次加入太多，要写测试
### 架构调整
```
thlang/
├── CMakeLists.txt                      # 主构建文件（简洁版）
├── README.md                           # 项目介绍
├── LICENSE
├── .gitignore
├── .clang-format
├── .github/
│   └── workflows/
│       └── ci.yml                      # 持续集成
│
├── include/                            # 公共头文件
│   └── thlang/
│       ├── ast/
│       │   ├── AST.h                  # 所有AST节点定义（一个文件）
│       │   └── Visitor.h              # Visitor接口
│       ├── frontend/
│       │   ├── Lexer.h
│       │   ├── Parser.h
│       │   └── Token.h
│       ├── sema/
│       │   ├── Sema.h                 # 语义分析主入口
│       │   ├── SymbolTable.h
│       │   ├── TypeChecker.h
│       │   ├── TypeSystem.h
│       │   └── BorrowChecker.h        # 后期添加
│       ├── codegen/
│       │   ├── IRGenerator.h
│       │   ├── JITEngine.h
│       │   └── AOTCompiler.h
│       ├── driver/
│       │   └── Compiler.h             # 编译器主类
│       └── support/
│           ├── Arena.h                # 内存池
│           ├── Diagnostic.h           # 错误报告
│           └── SourceLocation.h
│
├── src/                                # 实现文件
│   ├── main.cpp                       # 主程序入口
│   ├── ast/
│   │   ├── AST.cpp
│   │   └── Visitor.cpp
│   ├── frontend/
│   │   ├── Lexer.cpp
│   │   ├── Parser.cpp
│   │   └── Token.cpp
│   ├── sema/
│   │   ├── Sema.cpp
│   │   ├── SymbolTable.cpp
│   │   ├── TypeSystem.cpp
│   │   └── TypeChecker.cpp
│   │   └── BorrowChecker.cpp          # 后期添加
│   ├── codegen/
│   │   ├── IRGenerator.cpp
│   │   ├── JITEngine.cpp
│   │   └── AOTCompiler.cpp
│   ├── driver/
│   │   └── Compiler.cpp
│   └── support/
│       ├── Arena.cpp                  # 为我们的AST内存管理，类似写一个std::unique_ptr，可直接用智能指针
│       ├── Diagnostic.cpp
│       └── SourceLocation.cpp
│
├── tests/                              # 测试
│   ├── CMakeLists.txt
│   ├── unit/                          # 单元测试
│   │   ├── TestLexer.cpp
│   │   ├── TestParser.cpp
│   │   ├── TestTypeChecker.cpp
│   │   └── TestIRGenerator.cpp
│   └── integration/                   # 集成测试
│       ├── arithmetic/
│       │   ├── add.myc
│       │   └── add.expected
│       ├── control_flow/
│       │   ├── if.thang
│       │   └── while.thlang
│       └── functions/
│           └── simple.thlang
│
├── examples/                           # 示例
│   ├── hello.thlang
│   └── fibonacci.thlang
│
├── runtime/                            # 运行时（可选）
│   ├── include/
│   │   └── runtime.h
│   └── src/
│       └── runtime.cpp
│
└── scripts/                            # 辅助脚本
    ├── build.sh
    ├── test.sh
    └── format.sh
```
**架构可参考**

### 模块化设计
如上文所示，项目高度模块化，减少模块干扰

### 开发路线
#### AST节点设计
**可以先创建少数节点，然后补充**
```cpp
class ASTNode {
public:
    // 核心：位置信息（必须）
    SourceLocation loc;
    
    // Visitor模式支持
    virtual void accept(ASTVisitor* visitor) = 0;
    virtual ~ASTNode() = default;
    
    // 调试辅助
    virtual void dump(int indent = 0) const = 0;
    virtual std::string getKindName() const = 0;
    
protected:
    ASTNode(SourceLocation loc) : loc(loc) {}
};

// 位置信息 - 包含足够上下文
class SourceLocation {
public:
    std::string filename;   // 文件路径
    int line;               // 行号（从1开始）
    int column;             // 列号（从1开始）
    int length;             // Token长度（用于高亮）
    
    // 用于错误报告
    std::string getLineContent(const std::string& source) const;
    std::string format() const {
        return filename + ":" + std::to_string(line) + ":" + std::to_string(column);
    }
};
```

### 内存管理设计
```
┌──────────────────────────────────── ──┐
│ C的灵活性 + Rust的安全性 - 学习曲线陡峭│
│ 类似Zig的显式 + 自动的借用检查         │
└───────────────────────────────────────┘
```
在AST节点加入指针、引用节点，设计移动语义、复制语义、值语义
### 异常处理设计
不要传统的异常，使用类似zig的异常方式
### 链接管理
初期采用clang，后面逐步取消依赖
### 模块管理
### REPL
