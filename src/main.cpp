#include <iostream>
#include "node.h"
#include "codegen.h"
using namespace std;
thlang::NModule root_module;
extern int yyparse(thlang::NModule &root_program);


int main(int argc, char **argv){
    yyparse(root_module);
    auto block_node = root_module.block.get();
    std::cout << block_node << "\n";
    thlang::CodeGenContext context;
    root_module.codegen(context);
    context.theModule->print(llvm::outs(), nullptr);
    return 0;
    
}

