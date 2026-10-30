#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} DisplayState08061350;

extern DisplayState08061350 data_030008B0;

/* Complete [0x08061350, 0x08061390): 64 bytes, 26 instructions. */
void func_08061350(void)
{
    u16 *destination = data_030008B0.tilemap + 0x58;
    destination[0] = 0xD063;
    destination[1] = 0xD064;
    destination[2] = 0xD065;
    destination += 32;
    *destination++ = 0xD066;
    *destination++ = 0xD067;
    *destination = 0xD068;
}
