#include <thlang/codegen.h>
#include <thlang/node.h>
#include <thlang/thlang.h>
#include <iostream>

int main(int argc, char **argv) {
    std::cout << thlang::compile_from_file("f.txt") << "\n";
    return 0;
}
