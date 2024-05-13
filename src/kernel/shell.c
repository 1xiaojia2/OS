#include <kernel/shell.h>
#include <stdint.h>
#include <stddef.h>

#define cmd_len 128	   // 最大支持键入128个字符的命令行输入
#define MAX_ARG_NR 16	   // 加上命令名外,最多支持15个参数
