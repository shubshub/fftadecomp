#include "ffta.h"

extern u16 func_08014778(const u8 *field);
extern u16 func_08013BC0(u16 value, u8 bits);

/* Complete [0x0801446C, 0x080144F2): 134 bytes, 63 instructions. */
u16 func_0801446C(const u8 *data, u16 *total)
{
    u8 kind = data[2] & 0xF0;
    const u8 *cursor = data + 3;
    u16 first = func_08014778(cursor);
    u16 second;

    while (*cursor++ != 0)
        ;
    second = func_08014778(cursor);
    while (*cursor++ != 0)
        ;

    if (kind == 0x10) {
        first = func_08013BC0(first, 8);
        second = func_08013BC0(second, 8);
        if (total != 0)
            *total += first + second + 0x30;
    }
    return (u16)(cursor - data);
}
