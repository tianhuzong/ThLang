find_package(LLVM REQUIRED CONFIG)
#find_library(ReflexLib REQUIRED)

set(REFLEX_STATIC_LIB reflex)
SET(SOURCES main.cpp codegen.cpp lex.yy.cpp parser.cpp unparse.cpp TypeSystem.cpp sema.cpp)


add_executable(compiler  ${SOURCES})
target_include_directories(compiler PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(compiler PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(compiler PUBLIC ${PROJECT_SOURCE_DIR}/third_party/reflex/include)
target_link_directories(compiler PUBLIC ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(compiler  ${REFLEX_STATIC_LIB})
target_include_directories(compiler PUBLIC ${LLVM_INCLUDE_DIRS})
target_link_libraries(compiler LLVM)
