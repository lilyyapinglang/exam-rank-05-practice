Valgrind 错误信息： Conditional jump or move depends on uninitialised value(s) 

字符串缺少结束符 '\0'

解决方案：
1. 在 malloc 分配每行内存时，长度一定要 + 1（给 '\0' 留出空间）。
2. 在读取完一行的字符（如 . 和 o）后，必须在末尾明确手动赋值 '\0'：