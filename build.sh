#! /usr/bin/bash
cd src;bison -d parser.y -o parser.cpp;reflex -yy lex.l;cd ..
#clang++ main.cpp parser.cpp lex.yy.cpp codegen.cpp -o lex -lreflex  `llvm-config --cxxflags --ldflags --system-libs --libs`
cmake -B build .
cd build
make
cd ..

