#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
} Position0806F46C;

struct Tilemap0806F46C;
extern struct Tilemap0806F46C data_030008B0;
extern struct Tilemap0806F46C data_03000990;
extern void func_0802B2E8(struct Tilemap0806F46C *, u8 x, u8 y,
                          u8 width, u8 height);
extern void func_0806F33C(Position0806F46C *, s32 x, s32 y);

/* Complete target: [0x0806F46C, 0x0806F568), 252 bytes, 111 instructions. */
u32 func_0806F46C(Position0806F46C *position, s8 target)
{
    s8 difference;
    s8 previous;
    s8 end;
    s8 width;

    if (position->x == target)
        return 1;
    difference = target - position->x;
    previous = position->x;
    if (difference > 0) {
        position->x += 4;
        if (position->x >= target)
            position->x = target;
        end = position->x > 30 ? 30 : position->x;
        width = end - previous;
        if (width > 0) {
            func_0802B2E8(&data_030008B0, previous, position->y, width, 3);
            func_0802B2E8(&data_03000990, previous, position->y, width, 3);
        }
    } else {
        s32 left;
        position->x -= 4;
        if (position->x < target)
            position->x = target;
        if (position->x + 14 < 30) {
            end = previous + 14 > 30 ? 30 : previous + 14;
            left = end - 14;
            width = left - position->x;
            func_0802B2E8(&data_030008B0, position->x + 14, position->y,
                          width, 3);
            func_0802B2E8(&data_03000990, position->x + 14, position->y,
                          width, 3);
        }
    }
    func_0806F33C(position, position->x, position->y);
    return 0;
}
