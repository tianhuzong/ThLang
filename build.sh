#!/usr/bin/env bash

cd third_party/reflex
./build.sh

echo -e '\033[31m reflex built \033[0m'

cd ../

cmake ./lld -B build
# 修正拼写错误：将 --buils 改为 --build
cmake --build build

echo -e "\033[31mlld built\033[0m"

OS=$(uname -s)

# 判断是否为 Linux
if [ "$OS" = "Linux" ]; then
    cd musl
    ./configure
    make
    cd ..

    echo -e "\033[31mmusl libc built\033[0m"
fi

cd ../

# 查找 LLVM 库目录
LLVM_LIB_DIR=$(llvm-config --libdir)

OS=$(uname)
libls=$(ls third_party/reflex/lib)
out="\033[31m"+${libls}+"   "+${OS}+"\033[0m"

echo -e ${out}

case "$OS" in
    Linux)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.so lib/  # 复制动态库
        # 复制 LLVM 动态库
        cp $LLVM_LIB_DIR/libLLVM-18*.so lib/
        EXE_NAME='reflex_exe'
        ;;
    Darwin)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.dylib lib/  # 复制动态库
        # 复制 LLVM 动态库
        cp $LLVM_LIB_DIR/libLLVM*.dylib lib/
        EXE_NAME='reflex_exe'
        ;;
    MINGW* | MSYS* | CYGWIN*)
        cp third_party/reflex/src/reflex.exe src/reflex_exe.exe
        cp third_party/reflex/lib/reflex.lib lib/
        cp third_party/reflex/lib/reflexmin.lib lib/
        cp third_party/reflex/lib/reflex.dll lib/  # 复制动态库
        # 复制 LLVM 动态库
        cp $LLVM_LIB_DIR/libLLVM*.dll lib/
        EXE_NAME='reflex_exe.exe'
        ;;
    *)
        cp third_party/reflex/src/reflex src/reflex_exe
        cp third_party/reflex/lib/libreflex.a lib/
        cp third_party/reflex/lib/libreflexmin.a lib/
        cp third_party/reflex/lib/libreflex.so lib/  # 复制动态库
        # 复制 LLVM 动态库
        cp $LLVM_LIB_DIR/libLLVM*.so* lib/
        EXE_NAME='reflex_exe'
        ;;
esac

cd src
bison -d parser.y -o parser.cpp
./${EXE_NAME} -yy lex.l
cd ..
cmake -B build . 
cmake --build build