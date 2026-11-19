#include "ffta.h"

/* Complete [0x0800BB60, 0x0800BB74): 20 bytes: 5 instructions, a padding
 * halfword and two literal words.
 * Target: 024a10800248017070470000389100023a910002.
 * Sets the tile values the layout drawers skip: src/0800A71C.c compares
 * data_02009138 with u16 map entries and src/0800AA54.c compares
 * data_0200913A with u8 ones; src/0800C2C0.c sets them to 0x3FF and 0xFF.
 */
extern u16 data_02009138;
extern u8 data_0200913A;

void func_0800BB60(u16 transparentTile16, u8 transparentTile8)
{
    data_02009138 = transparentTile16;
    data_0200913A = transparentTile8;
}
