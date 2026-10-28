#include "ffta.h"

/* 0x08018CEC..0x08018D10: 36 bytes / 14 instructions. */
typedef u32 (*TextFormatter)(u8 *destination, u8 code);

extern TextFormatter const data_0836D768[];

u8 func_08018CEC(u8 *destination, u8 code)
{
    *destination = 0;
    return data_0836D768[code](destination, code);
}
