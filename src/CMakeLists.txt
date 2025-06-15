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

# 编译 libthlang.so
add_library(thlang SHARED ${LIB_SOURCES})
target_include_directories(thlang PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/third_party/reflex/include
    ${LLVM_INCLUDE_DIRS}
)
target_link_directories(thlang PUBLIC ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(thlang ${REFLEX_STATIC_LIB} LLVM)

# 编译main
add_executable(compiler ${MAIN_SOURCE})
target_include_directories(compiler PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)
target_link_libraries(compiler thlang LLVM)  # 链接 libthlang.so 和 LLVM