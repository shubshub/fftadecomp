#include "ffta.h"

typedef struct {
    u32 value : 7;
    u32 enabled : 1;
    u32 mode : 4;
    u32 flag4 : 1;
    u32 flag5 : 1;
    u32 flag6 : 1;
    u32 unknown_flag : 1;
    u8 direction : 7;
    u8 valid : 1;
    u8 unknown_3;
    u8 unknown_4;
    u8 unknown_5;
    u8 unknown_6;
} __attribute__((packed)) PathCell08149194;

static inline PathCell08149194 *get_cell(PathCell08149194 *grid, s16 x, s16 y)
{
    return &grid[y * 16 + x];
}

/* Complete [0x08149194, 0x081491C0): 44 bytes, 22 instructions.
 * Target bytes: 00b509061206120d090e5218d100891a4218002b03d050784021084303e0
 *               5178412040420840507001bc0047 */
void func_08149194(PathCell08149194 *grid, u8 x, u8 y, s32 flag6)
{
    PathCell08149194 *cell = get_cell(grid, x, y);

    if (flag6)
        cell->flag6 = 1;
    else
        cell->flag6 = 0;
}
