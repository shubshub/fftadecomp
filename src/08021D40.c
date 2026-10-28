#include "ffta.h"

/* 0x08021D40..0x08021D46: 6 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 x;
    s16 y;
} Position08021D40;

void func_08021D40(Position08021D40 *position, s16 x, s16 y)
{
    position->x = x;
    position->y = y;
}
