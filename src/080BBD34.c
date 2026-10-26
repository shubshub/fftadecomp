#include "ffta.h"

struct Countdown080BBD34 {
    s16 x;
    s16 y;
    s16 z;
    s8 count;
    u8 unknown07;
};

extern void func_080E2C00(void *context, s32 x, s32 y, s32 z,
                         u32 effect, u32 argument5);
extern u8 func_080D3878(void *context);

/* Complete [0x080BBD34, 0x080BBDFE): 202 bytes, 98 instructions. */
s32 func_080BBD34(struct Countdown080BBD34 *entries, s32 count, void *context)
{
    s32 active = 0;
    s32 i;

    if (context == 0)
        return 0;

    for (i = 0; i < count; i++, entries++) {
        if (entries->count != 0) {
            active = 1;
            switch (entries->count) {
            case 16:
                func_080E2C00(context, entries->x, entries->y, entries->z, 4, 4);
                break;
            case 12:
                func_080E2C00(context, entries->x, entries->y, entries->z, 5, 4);
                break;
            case 8:
                func_080E2C00(context, entries->x, entries->y, entries->z, 6, 4);
                break;
            case 4:
                func_080E2C00(context, entries->x, entries->y, entries->z, 7, 4);
                break;
            }
            entries->count--;
        }
    }

    if (!func_080D3878(context))
        active = 1;
    return active;
}
