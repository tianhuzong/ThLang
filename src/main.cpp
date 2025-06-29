#include <bits/types/FILE.h>
#include <thlang/codegen.h>
#include <thlang/node.h>
#include <thlang/thlang.h>
#include <iostream>
#include <cstdio>

int main(int argc, char **argv) {
    /*
    std::string ir = thlang::compile_toir_from_file("f.txt");
    std::cout << ir << "\n";
    FILE* file = std::fopen("tmp.s","w");
    FILE* file2 = std::fopen("tmp.o","w");
    thlang::compile_fir_to_asm(ir,file);
    thlang::compile_fir_to_obj(ir,file2);
    fclose(file);
    fclose(file2);
    */
    //thlang::link({"tmp.o","_start.o","-o","start_try","-L../lib","-lthlang"});
    //thlang::compile_fobj_to_exe({"tmp.o","_start.o"},"st_tmp");
    thlang::compile_from_files_to_exe({"main.th","_start.o"}, "st_temp");
    return 0;
}
