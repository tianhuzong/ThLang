cmake_minimum_required(VERSION 3.10)

find_package(LLVM REQUIRED CONFIG)

# 设置源文件
set(REFLEX_STATIC_LIB reflex)
set(LIB_SOURCES 
    libthlang.cpp
    codegen.cpp 
    lex.yy.cpp 
    parser.cpp 
    unparse.cpp 
    TypeSystem.cpp 
    sema.cpp
)
set(MAIN_SOURCE main.cpp)

# 指定库文件所在的目录
link_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/third_party/build/lib
    # 如果 libLLVM 动态库被复制到了其他目录，添加该目录
    ${PROJECT_SOURCE_DIR}/lib  # 假设 libLLVM 库也在这个目录
)

# 编译 libthlang.so
add_library(thlang SHARED ${LIB_SOURCES})
target_include_directories(thlang PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/third_party/reflex/include
    ${PROJECT_SOURCE_DIR}/third_party/lld/include
    ${PROJECT_SOURCE_DIR}/third_party/lld/include/
    ${PROJECT_SOURCE_DIR}/third_party/lld/ELF/
    ${PROJECT_SOURCE_DIR}/third_party/lld/MachO/
    ${PROJECT_SOURCE_DIR}/third_party/lld/MinGW/
    ${PROJECT_SOURCE_DIR}/third_party/lld/Wasm/
    ${PROJECT_SOURCE_DIR}/third_party/build/ELF/
    ${PROJECT_SOURCE_DIR}/third_party/build/MachO/
    ${PROJECT_SOURCE_DIR}/third_party/build/MinGW/
    ${PROJECT_SOURCE_DIR}/third_party/build/Wasm/
    ${LLVM_INCLUDE_DIRS}
)

file(GLOB LLVM_LIBS "${PROJECT_SOURCE_DIR}/lib/libLLVM*.so*" "${PROJECT_SOURCE_DIR}/lib/libLLVM*.dylib" "${PROJECT_SOURCE_DIR}/lib/libLLVM*.dll")

# 链接库文件
target_link_libraries(thlang 
    ${REFLEX_STATIC_LIB} 
    lldELF
    lldCOFF
    lldMachO
    lldWasm
    lldMinGW
    lldCommon
    ${LLVM_LIBS}  # 链接 LLVM 库
    zstd
    z
    pthread
)

# 编译 main
add_executable(compiler ${MAIN_SOURCE})
target_include_directories(compiler PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)
target_link_libraries(compiler thlang LLVM)  # 链接 libthlang.so 和 LLVM