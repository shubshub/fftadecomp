#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 limit;
    s16 position;
    u8 unknown_0A[2];
    u16 state;
} Animation08090214;

extern void func_080901A8(Animation08090214 *animation);

/* 0x08090214..0x08090264: 80 bytes, 38 instructions. */
s32 func_08090214(Animation08090214 *animation)
{
    switch (animation->state) {
    case 1:
        animation->position++;
        func_080901A8(animation);
        if (animation->position >= animation->limit) {
            animation->state = 0;
        }
        break;
    case 2:
        animation->position--;
        if (animation->position <= 0) {
            animation->state = 0;
            animation->position = 0;
        }
        func_080901A8(animation);
        break;
    default:
        return 0;
    }
    return 1;
}
