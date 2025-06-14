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
        EXE_NAME='reflex_exe'
        ;;
    Darwin)
        #echo "当前操作系统为 macOS（基于 Darwin 内核）"
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        EXE_NAME='reflex_exe'
        ;;
    MINGW* | MSYS*)
        cp third_party/reflex/src/reflex.exe src/reflex_exe.exe
        cp third_party/reflex/lib/reflex.lib lib/
        cp third_party/reflex/lib/reflexmin.lib lib/
        EXE_NAME='reflex_exe.exe'
        ;;
    *)
        #echo "当前操作系统为类 Unix 系统，按照类 Unix 方式处理"
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
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

