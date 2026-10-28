#include "ffta.h"

typedef struct {
    u8 unknown_00[0xf6];
    u8 column;
    u8 row;
    u8 unknown_f8[5];
    u8 movement;
} Unit08097504;

typedef struct Grid08097504 Grid08097504;
typedef struct {
    Unit08097504 *unit;
    u8 unknown_04[0x38];
    Grid08097504 *grid;
} Context08097504;

extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u32 func_08149384(Grid08097504 *grid, u8 column, u8 row);
extern u8 func_081493AC(Grid08097504 *grid, u8 column, u8 row);

/* Complete [0x08097504, 0x080975DA): 214 bytes, 103 instructions. */
u8 func_08097504(Context08097504 *context, s8 column, s8 row, u8 range)
{
    u8 flags;

    if (range == 0) {
        if (context->unit->column != column || context->unit->row != row)
            return 0;
        return 1;
    }

    if (column < 0 || row < 0 || column > 15 || row > 15)
        return 0;
    if (!func_0801CC7C(column, row))
        return 0;

    flags = func_0801CD08(column, row);
    if (flags & 1)
        return 0;
    if (flags & 8)
        return 0;
    if (flags & 2) {
        s32 movement = context->unit->movement;

        if (movement > 4)
            return 0;
        if (movement < 2)
            return 0;
    }

    if (!func_08149384(context->grid, column, row))
        return 0;
    if (func_081493AC(context->grid, column, row) > range)
        return 0;
    return 1;
}
