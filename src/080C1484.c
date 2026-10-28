#include "ffta.h"

/* 0x080C1484..0x080C14B0: 44 bytes, including the literal pool. */
typedef struct {
    u8 unknown_00[0x54E4];
    u8 entries[4];
    u8 count;
} State;

extern State data_020101F8;

s32 func_080C1484(s32 index)
{
    if (index >= data_020101F8.count)
        return -1;
    return data_020101F8.entries[index];
}
