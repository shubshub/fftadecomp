#include "ffta.h"

typedef struct {
    u8 frame;
    u8 flags;
    u8 index;
    u8 requested_index;
    s16 x;
    s16 y;
    u8 unknown_08[0x40];
    u16 state;
    u8 unknown_4A[0x46];
} Animation080C586C;

typedef void (*BufferInitializer080C586C)(void *destination, u32 size);
extern BufferInitializer080C586C g_callbacks_0836D4B8[];
extern void func_080C55D8(Animation080C586C *animation);
extern void func_080C566C(Animation080C586C *animation);
extern void func_080C56E8(Animation080C586C *animation);
extern void func_080C5774(Animation080C586C *animation);

/* Complete [0x080C586C, 0x080C5906): 154 bytes, 69 instructions. */
void func_080C586C(Animation080C586C *animation)
{
    if (animation->flags & 4) {
        u8 busy = animation->flags & 8;

        if (!busy) {
            u8 index = animation->requested_index;

            g_callbacks_0836D4B8[0](animation, sizeof(Animation080C586C));
            animation->index = 0;
            animation->x = 0xD8;
            animation->y = 0x98;
            g_callbacks_0836D4B8[0](animation, sizeof(Animation080C586C));
            animation->index = index;
            animation->x = 0xD8;
            animation->y = 0x98;
            if (index != 0)
                animation->state = 1;
        }
    }

    switch (animation->index) {
    case 2:
        func_080C55D8(animation);
        break;
    case 3:
        func_080C566C(animation);
        break;
    case 1:
        func_080C56E8(animation);
        break;
    default:
        func_080C5774(animation);
        break;
    }
}
