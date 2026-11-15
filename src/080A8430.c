#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} AnglePoint;

extern u16 func_08141860(s16 horizontal, s16 vertical);

/* Complete [0x080A8430, 0x080A8498): 104 bytes, 51 instructions.
 * 30b5041c0a1c0020215e0023d05e0b1a002b00da5b420425615f0425505f081a002800
 * da40420225515f0225625f181800040014891a0904091499f0f9f90004010e4039ff20
 * 8843011c0f39002900da00217e2900dd7f21081c002800da0f30001130bc02bc0847
 */
s32 func_080A8430(const AnglePoint *first, const AnglePoint *second)
{
    s32 dx = first->x - second->x;
    s32 dz;
    s32 first_y;
    s32 second_y;
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
    angle = func_08141860(dx + dz, second_y - first_y) >> 8;
    angle -= 0x40;
    angle = (0xFF & ~angle) - 0x0F;
    if (angle < 0) {
        angle = 0;
    }
    if (angle >= 0x7F) {
        angle = 0x7F;
    }
    return angle / 16;
}
