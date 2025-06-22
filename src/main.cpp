#include <bits/types/FILE.h>
#include <thlang/codegen.h>
#include <thlang/node.h>
#include <thlang/thlang.h>
#include <iostream>
#include <cstdio>

int main(int argc, char **argv) {
    std::string ir = thlang::compile_toir_from_file("f.txt");
    std::cout << ir << "\n";
    FILE* file = std::fopen("tmp.s","w");
    thlang::compile_fir_to_asm(ir,file);
    return 0;
}
