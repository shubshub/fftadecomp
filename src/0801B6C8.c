#include "ffta.h"

// 0x0801B6C8..0x0801B73C: 116 bytes, 104 bytes of Thumb code and three
// literal words (g_state_02007F40, 0x01001000, 0x01000800).
// Fills both 0x2000-byte tile maps with the state's fill tile and clears
// both 0x1000-byte maps, each through a BIOS CpuSet fixed-source fill.

typedef struct {
    u8 unknown_00[0x1e];
    u16 fill_tile;
} State0801B6C8;

extern State0801B6C8 g_state_02007F40;

extern u16 *func_0801AD1C(u8 layer);
extern u16 *func_0801AD38(u8 layer);
extern void func_0814186C(const void *source, void *destination, u32 control);

static inline void Fill16(const u16 *source, void *destination, u32 size)
{
    func_0814186C(source, destination, 0x01000000 | (size / 2));
}

void func_0801B6C8(void)
{
    u16 fill[4];
    /* One pointer per fill value: the ROM keeps each slot address live across its CpuSet call. */
    u16 *first;
    u16 *second;
    u16 *third;
    u16 *fourth;

    first = &fill[0];
    *first = g_state_02007F40.fill_tile;
    Fill16(first, func_0801AD1C(0), 0x2000);
    second = &fill[1];
    *second = g_state_02007F40.fill_tile;
    Fill16(second, func_0801AD1C(1), 0x2000);
    third = &fill[2];
    *third = 0;
    Fill16(third, func_0801AD38(0), 0x1000);
    fourth = &fill[3];
    *fourth = 0;
    Fill16(fourth, func_0801AD38(1), 0x1000);
}
