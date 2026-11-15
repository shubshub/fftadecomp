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
} __attribute__((packed)) PathCell081493AC;

static inline PathCell081493AC *get_cell(PathCell081493AC *grid, s16 x, s16 y)
{
    return &grid[y * 16 + x];
}

/* Complete [0x081493AC, 0x081493C0): 20 bytes, 10 instructions.
 * Target bytes: 09061206120d090e5218d100891a401800797047 */
u8 func_081493AC(PathCell081493AC *grid, u8 x, u8 y)
{
    return get_cell(grid, x, y)->unknown_4;
}
