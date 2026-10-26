#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;

extern void func_08003508(s16 offset, u8 value);
extern void func_08003558(s16 offset, u8 value);

void func_080D7468(const Position *position, u8 value, u16 x, u16 y)
{
    u16 dx = position->x - x;
    u16 dy = position->y - y;

    func_08003508((s16)dx, value);
    func_08003558((s16)dy, value);
}
