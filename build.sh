#! /usr/bin/bash
bison -d parser.y -o parser.cpp
reflex --yy lex.l
clang++ parser.cpp lex.yy.cpp -o lex -lreflex
