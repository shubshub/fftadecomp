#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
} Entry08121C98;

typedef struct {
    u8 unknown_000[0x8D8];
    Entry08121C98 entries[256];
} State08121C98;

extern State08121C98 *data_020159CC;

/* 0x08121C98..0x08121CB4:
 * 00 06 04 49 40 0D 04 4A 80 18 09 68 09 18 08 1C
 * 70 47 00 00 CC 59 01 02 D8 08 00 00. */
Entry08121C98 *func_08121C98(u8 index)
{
    return &data_020159CC->entries[index];
}
