#include "ffta.h"

/* Target: complete [0x0812DB5C, 0x0812DBA6), 74 bytes. */
typedef struct {
    u8 unknown_00[0xf6];
    s8 x;
    s8 y;
    s8 z;
} Position0812DB5C;

extern u32 func_0812D1DC(Position0812DB5C *, Position0812DB5C *,
                        s32, s32, s32, s32, s32, u32);

u32 func_0812DB5C(Position0812DB5C *source, Position0812DB5C *destination,
                   u32 mode)
{
    return func_0812D1DC(source, destination, source->x, source->y,
                          destination->x, destination->y, destination->z, mode);
}
