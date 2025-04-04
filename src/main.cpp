#include "codegen.h"
#include "node.h"
#include <iostream>
using namespace std;
thlang::NModule root_module;
extern int yyparse(thlang::NModule &root_program,
                   thlang::CodeGenContext &context);

int main(int argc, char **argv) {
  freopen("f.txt", "r", stdin);
  thlang::CodeGenContext context;
  context.typeSystem.add_type("整数型", thlang::Type("整数型"));
  yyparse(root_module, context);
  auto block_node = root_module.block.get();
  std::cout << block_node << "\n";
  /*
  if (context.sema.analyze(block_node)) {
    std::cerr << "语义分析失败!\n";
    return 1;
  }
  */
  root_module.codegen(context);
  context.theModule->print(llvm::outs(), nullptr);
  return 0;
}
