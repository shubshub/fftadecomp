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
} __attribute__((packed)) PathCell08149384;

static inline PathCell08149384 *get_cell(PathCell08149384 *grid, s16 x, s16 y)
{
    return &grid[y * 16 + x];
}

/* Complete [0x08149384, 0x081493AA): 38 bytes, 19 instructions.
 * Target bytes: 00b509061206120d090e5218d100891a4018817880200840002801d10020
 *               00e0012002bc0847 */
u32 func_08149384(PathCell08149384 *grid, u8 x, u8 y)
{
    if (get_cell(grid, x, y)->valid)
        return 1;
    return 0;
}
