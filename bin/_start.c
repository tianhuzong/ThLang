// start.h

// 平台检测宏
#if defined(__linux__)
    #define PLATFORM_LINUX 1
    #if defined(__MUSL__) || !defined(__GLIBC__)
        #define USE_MUSL 1
    #endif
#elif defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
#else
    #define PLATFORM_UNKNOWN 1
#endif

// 声明 main 函数
extern int main(int argc, char **argv, char **envp);

//-------------------------------
// Linux (musl) 专用部分
//-------------------------------
#if defined(PLATFORM_LINUX) && defined(USE_MUSL)

/* 声明 musl 内部符号 */
void _start_c(long *);
extern int __libc_start_main(int (*)(int,char**,char**), int, char**, 
                           void (*)(), void(*)(), void(*));

/* 汇编入口（直接跳转到 musl 的初始化） */
__asm__(
    ".global _start\n"
    "_start:\n"
    "   xor %ebp, %ebp\n"
    "   mov (%rsp), %rdi\n"      // argc
    "   lea 8(%rsp), %rsi\n"     // argv
    "   jmp _start_c\n"          // 跳转到 musl 的初始化代码
);

//-------------------------------
// macOS (libSystem) 专用部分
//-------------------------------
#elif defined(PLATFORM_MACOS)

/* 声明 libSystem 符号 */
extern void _main(int, char**, char**, char**);

void _start() {
    _main(0, NULL, NULL, NULL);  // macOS dyld 会处理实际初始化
}

//-------------------------------
// Windows (MSVCRT) 专用部分
//-------------------------------
#elif defined(PLATFORM_WINDOWS)

/* 声明 MSVCRT 符号 */
extern int __argc;
extern char **__argv;
extern char **_environ;
extern void __cdecl exit(int);

void _start() {
    exit(main(__argc, __argv, _environ));
}

//-------------------------------
// 其他平台（裸机/未知系统）
//-------------------------------
#else

void _exit(int code) { while(1); }

void _start() {
    _exit(main(0, NULL, NULL));
}

#endif