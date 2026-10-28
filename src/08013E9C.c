/* 0x08013E9C - Decode a table entry into a caller-provided text buffer. */
#include "ffta.h"

extern void func_0800543C(void *destination, const void *source);
extern u16 func_08013F20(u8 *destination, const u8 *source);
extern u16 func_0801407C(u8 *destination, const u8 *source);

u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                  u16 index, u8 *status, u8 *mode)
{
    const u8 *entry = table + index * sizeof(u16);
    u16 format;
    u16 compressed;
    u16 length;

    entry = table + *(const u16 *)entry;
    if (mode)
        *mode = (*(const u16 *)entry & 0xF0) >> 4;
    if (status)
        *status = 0;

    format = *(const u16 *)entry & 1;
    compressed = (u16)(*(const u16 *)entry & 2) >> 1;
    entry += 2;
    if (compressed) {
        func_0800543C(workspace, entry);
        entry = workspace;
    }

    if (format)
        length = func_08013F20(destination, entry);
    else
        length = func_0801407C(destination, entry);

    if (!compressed && length > 0x1FF)
        length -= 0x200;
    return length;
}
