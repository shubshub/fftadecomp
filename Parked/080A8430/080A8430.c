#include "ffta.h"

/* 0x080A8430..0x080A8498: 104 bytes, 51 instructions. */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
} AnglePoint;

extern u16 func_08141860(s16 horizontal, s16 vertical);

s32 func_080A8430(const AnglePoint *first, const AnglePoint *second)
{
    s32 dx = first->x - second->x;
    s32 dz;
    s32 first_y;
    s32 second_y;
    u16 direction;
    s32 angle;

    if (dx < 0) {
        dx = -dx;
    }
    dz = first->z - second->z;
    if (dz < 0) {
        dz = -dz;
    }
    second_y = second->y;
    first_y = first->y;
    direction = func_08141860((s16)(dx + dz), (s16)(second_y - first_y)) >> 8;
    direction = ~(direction - 0x40) & 0xFF;
    angle = direction;
    angle -= 0x0F;
    if (angle < 0) {
        angle = 0;
    }
    if (angle > 0x7E) {
        angle = 0x7F;
    }
    return angle / 16;
}
