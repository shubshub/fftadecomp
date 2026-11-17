// 0x0801D624 .. 0x0801D818: 500 bytes, 250 instructions.
#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Offset0801D624;

typedef struct {
    Offset0801D624 entries[4];
} OffsetTable0801D624;

extern const OffsetTable0801D624 data_08149904;
extern const OffsetTable0801D624 data_081498F4;

extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                          s16 *firstOutput, s16 *secondOutput, s16 *thirdOutput);
extern void func_0801C918(s16 first, s16 second, s16 third, s16 *first_output,
                          s16 *second_output, s16 *third_output);
extern u8 func_0801EC28(s16 first, s16 second, s16 third,
                        u8 fourth, u8 fifth, u8 sixth);
extern u8 func_0801E63C(void);
extern u8 *func_0801AD38(u8 second);
extern void func_0801D130(u8 column, u8 row, u8 x, u8 y, u8 *flags, u8 mode);

void func_0801D624(u8 column, u8 row, u8 mode)
{
    u8 flags[4];
    OffsetTable0801D624 near = data_08149904;
    u8 height;
    s16 worldX, worldY, worldZ;
    s16 screenX, screenY, depth;
    u8 base;
    u8 found;
    u8 i;

    height = func_0801CC18(column, row);
    func_0801CA78(column, height, row, &worldX, &worldY, &worldZ);
    func_0801C918(worldX, worldY, worldZ, &screenX, &screenY, &depth);
    screenX -= 16;
    screenY -= 8;

    base = column + row;
    for (i = 0; i < 4; i++) {
        depth = base;
        if (i == 2) {
            if (row < 15 && height == func_0801CC18(column, row + 1))
                depth++;
        } else if (i == 3) {
            if (column < 15 && height == func_0801CC18(column + 1, row))
                depth++;
        }
        flags[i] = 0;
        found = func_0801EC28(screenX + near.entries[i].x,
                              screenY + near.entries[i].y, depth, height, 1, 0);
        if (found == func_0801E63C())
            flags[i] = 1;
    }

    screenX >>= 3;
    screenY >>= 3;
    {
        OffsetTable0801D624 far = data_081498F4;

        for (i = 0; i < 4; i++) {
            if (!flags[i]) {
                u8 *row_base = func_0801AD38(0)
                               + (screenY + far.entries[i].y) * 64;
                u16 *cell = (u16 *)row_base
                            + ((screenX + far.entries[i].x) >> 1);

                if (*cell == 0)
                    flags[i] = 1;
            }
        }
    }

    func_0801D130(column, row, screenX, screenY, flags, mode);
}
