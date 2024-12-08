#include <iostream>
#include "nn.h"
#include "codegen.h"
#include "parser.hpp"
using namespace std;
extern std::vector<Node*> program;


int main(int argc, char **argv){

    yyparse();
    CodeGenContext myC("main");
    myC.codeGen(program);
    myC.module->print(llvm::outs(), nullptr);
}

