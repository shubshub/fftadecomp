#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x, y, z;
} Position080DBF90;

typedef struct {
    s16 x, y;
    s16 rectangle[4];
} ProjectedBounds080DBF90;

extern void func_0801C984(s16, s16, s16, s16 *, s16 *);
extern u8 func_080D8604(s16 *, const s16 *, u8, const s16 *);

// Complete [0x080DBF90, 0x080DBFFA): 106 bytes.
// Projects the position, builds a rectangle around it and tests it with
// the caller's area, mode and adjustment.
u8 func_080DBF90(const Position080DBF90 *position, const s16 *area, u8 mode,
                 const s16 *adjustment)
{
    ProjectedBounds080DBF90 projected;
    s16 *rectangle = projected.rectangle;
    s16 *y = &projected.y;

    func_0801C984(position->x, position->y, position->z,
                   &projected.x, y);
    rectangle[0] = projected.x - 16;
    rectangle[2] = projected.x + 16;
    rectangle[1] = *y - 32;
    rectangle[3] = *y + 8;
    return func_080D8604(rectangle, area, mode, adjustment);
}
