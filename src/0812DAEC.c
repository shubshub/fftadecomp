#include "ffta.h"

/* Complete [0x0812DAEC, 0x0812DB5A): 110 bytes, 52 instructions. */
typedef struct {
    u8 unknown_00[0xF8];
    u8 direction;
} Object0812DAEC;

extern u8 func_0812C960(void *object);
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u8 func_0812D07C(void *unit, u16 entry, u32 selector);

s32 func_0812DAEC(Object0812DAEC *source, Object0812DAEC *target, s32 selector)
{
    s32 value; /* the direction difference, then each entry */
    s32 index;

    value = source->direction - target->direction;
    if (value < 0)
        value = -value;
    if (func_0812C960(target) || value != 2)
        return 0;
    for (index = 0; index < 5; index++) {
        value = func_080C7EA4(target, (u8)(index + 0x1D));
        if (value != 0 && !func_0812D07C(target, value, selector))
            return 0;
    }
    return 100;
}
