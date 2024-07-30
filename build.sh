#! /usr/bin/bash
bison -d parser.y -o parser.cpp
reflex --yy lex.l
clang++ main.cpp parser.cpp lex.yy.cpp codegen.cpp -o lex -lreflex  `llvm-config --cxxflags --ldflags --system-libs --libs`
