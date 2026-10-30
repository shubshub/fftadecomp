#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 value;
    u8 unknown_03;
} Entry08060E0C;

extern u8 *data_0200F44C;

/* 08060E0C..08060E24: 00 06 04 49 80 0D 94 22 52 00 80 18 09 68 09 18 88 78 70 47 4C F4 00 02. */
u8 func_08060E0C(u8 index)
{
    u32 offset = 0x128 + index * sizeof(Entry08060E0C);
    Entry08060E0C *entry = (Entry08060E0C *)(data_0200F44C + offset);

    return entry->value;
}
