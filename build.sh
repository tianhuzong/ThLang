#!/usr/bin/bash

cd third_party/reflex
./build.sh

echo -e '\033[31m reflex built \033[0m'

cd ../..
OS=$(uname)

case "$OS" in
    Linux)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.so lib/  # 复制动态库
        EXE_NAME='reflex_exe'
        ;;
    Darwin)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.dylib lib/  # 复制动态库
        EXE_NAME='reflex_exe'
        ;;
    MINGW* | MSYS* | CYGWIN*)
        cp third_party/reflex/src/reflex.exe src/reflex_exe.exe
        cp third_party/reflex/lib/reflex.lib lib/
        cp third_party/reflex/lib/reflexmin.lib lib/
        cp third_party/reflex/lib/reflex.dll lib/  # 复制动态库
        EXE_NAME='reflex_exe.exe'
        ;;
    *)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.so lib/  # 复制动态库
        EXE_NAME='reflex_exe'
        ;;
esac
#cd src;bison -d parser.y -o parser.cpp;reflex -yy lex.l;cd ..
#clang++ main.cpp parser.cpp lex.yy.cpp codegen.cpp -o lex -lreflex  `llvm-config --cxxflags --ldflags --system-libs --libs`

cd src
bison -d parser.y -o parser.cpp
./${EXE_NAME} -yy lex.l
cd ..
cmake -B build .
cd build
make
cd ..

