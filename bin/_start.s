.section .text
.global _start
_start:
    xor %rbp, %rbp                # 清除帧指针
    
    # 获取 argc, argv, envp
    mov (%rsp), %rdi              # argc
    lea 8(%rsp), %rsi             # argv
    lea 16(%rsp,%rdi,8), %rdx     # envp = argv + argc + 1

    # 调用 musl 的初始化函数
    call __libc_start_main@PLT    # 必须动态链接或提供实现
    
    # 如果返回则崩溃
    ud2