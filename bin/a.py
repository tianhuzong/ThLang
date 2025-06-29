from ctypes import *

# 加载库
libthlang = CDLL("../lib/libthlang.so")

# 定义编译函数（直接返回c_void_p）
cctiff = libthlang.compile_code_to_ir_from_file
cctiff.argtypes = [c_char_p]
cctiff.restype = c_void_p  # 修改为返回void指针

# 定义释放函数
free_mem = libthlang.free_memory
free_mem.argtypes = [c_void_p]
free_mem.restype = None

# 定义将void*转为char*的函数（如果需要）
get_string = CFUNCTYPE(c_char_p, c_void_p)(lambda p: cast(p, c_char_p))

# 调用并处理结果
try:
    # 获取void指针
    res_ptr = cctiff(b"./main.th")  
    
    if res_ptr:
        # 转换为char*并解码
        res_str = cast(res_ptr, c_char_p).value.decode('utf-8')
        print(res_str)
finally:
    # 释放内存
    if res_ptr:
        free_mem(res_ptr)  # 直接使用void*释放