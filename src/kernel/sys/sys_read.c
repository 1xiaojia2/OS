#include <stdint.h>
#include <stddef.h>
#include <drivers/keryboard.h>
#include <asm/cpu.h>

// int32_t read(void* buf, uint32_t count) {
//     cli();
//     int32_t ret = -1;
//     char* buffer = buf;
//     uint32_t bytes_read = 0;
//     while (bytes_read < count) {
// 	    *buffer = ioq_getchar(&kbd_buf);
// 	    bytes_read++;
// 	    buffer++;
//     }
//     ret = (bytes_read == 0 ? -1 : (int32_t)bytes_read);
//     sti();
//    return ret;
// }