#include "ffta.h"

typedef struct {
    u8 unknown_00[0xB];
    u8 flags_0B;
    u16 flags_0C;
    u8 unknown_0E[0x1D];
    u8 flags_2B;
    u32 selection;
    u32 value;
    u8 unknown_34[6];
    u16 flags_3A;
    u8 unknown_3C[0x718];
    void *resource;
} State080131A4;

extern State080131A4 *data_0200918C;
extern void *func_080CB968(u8 key);

/* Target bytes [080131A4, 08013210):
 * 70 B5 00 06 00 0E 09 06 09 0E 90 26 F6 01 13 4D
 * 2B 68 5C 8F 12 4A 22 40 5A 87 02 02 0A 43 DA 62
 * 1E 63 B8 F0 CF FB 2A 68 0E 4B D1 18 08 60 2B 32
 * 11 78 FD 23 18 1C 08 40 10 70 29 68 2B 31 0A 78
 * 01 20 10 43 08 70 29 68 8A 89 07 48 10 40 88 81
 * C8 7A 03 40 CB 72 70 BC 01 BC 00 47 8C 91 00 02
 * 7F FF 00 00 54 07 00 00 EF FF 00 00.
 */
void func_080131A4(u8 key, u8 selection)
{
    u32 value = 0x4800;

    data_0200918C->flags_3A &= 0xFF7F;
    data_0200918C->selection = (key << 8) | selection;
    data_0200918C->value = value;
    data_0200918C->resource = func_080CB968(key);
    data_0200918C->flags_2B &= 0xFD;
    data_0200918C->flags_2B |= 1;
    data_0200918C->flags_0C &= 0xFFEF;
    data_0200918C->flags_0B &= 0xFD;
}
