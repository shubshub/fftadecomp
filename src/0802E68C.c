#include "control_flags.h"

typedef struct {
    u16 x;
    u16 y;
    u8 unknown_04[4];
    u8 height;
    u8 unknown_09[2];
    u8 step;
    u8 unknown_0C[0x49C - 0x0C];
    u16 rows[8][52];
} BorderState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} BorderMap;

struct ExtendedRequestNode;

extern BorderState *data_0200F444;
extern const u16 data_083C4AA8[];
extern BorderMap data_03000990;
extern BorderMap data_030008B0;
extern void func_0802F1D0(void);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern void *func_0802DFCC(void);
extern void func_08000BAC(struct ExtendedRequestNode *entry, u32 source,
                          u32 destination, u16 width, u16 height,
                          u16 source_stride, u16 destination_stride);

static inline void copy_four_tiles(u16 *destination, const u16 *source)
{
    destination[0] = source[0];
    destination[1] = source[1];
    destination[2] = source[2];
    destination[3] = source[3];
}

/* 0802E68C..0802E890: 516 bytes, 231 instructions. */
u8 func_0802E68C(void)
{
    u16 column;
    const u16 *source;
    u16 *destination;
    s32 i;
    u16 index;

    if (data_0200F444->step == 6) {
        func_0802F1D0();
        func_0802A2C0(0, 0, 0, 0);
        g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
    }
    column = 24 - data_0200F444->step * 2;
    source = data_083C4AA8 + column;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + column, data_0200F444->y, 32);
    copy_four_tiles(destination, source);

    source += 26;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + column, data_0200F444->y + 1, 32);
    if (data_0200F444->step == 6)
        destination[-1] = source[-1];
    copy_four_tiles(destination, source);

    source += 26;
    destination = data_03000990.map +
        func_080161A0(data_0200F444->x + column,
                      data_0200F444->height * 2 + data_0200F444->y + 2, 32);
    copy_four_tiles(destination, source);

    source += 26;
    for (i = 0; i < data_0200F444->height; i++) {
        index = func_080161A0(data_0200F444->x + column,
                             data_0200F444->y + (i * 2 + 2), 32);
        destination = data_03000990.map + index;
        copy_four_tiles(destination, source);
        destination[32] = source[26];
        destination[33] = source[27];
        destination[34] = source[28];
        destination[35] = source[29];
    }

    data_0200F444->step--;
    if (data_0200F444->step == 0) {
        for (i = 0; i < data_0200F444->height; i++) {
            source = data_0200F444->rows[i];
            destination = data_030008B0.map +
                func_080161A0(data_0200F444->x + 1, i * 2 + data_0200F444->y + 2, 32);
            func_08000BAC(func_0802DFCC(), (u32)source, (u32)destination, 26, 2, 52, 64);
        }
    }
    return data_0200F444->step == 0;
}
