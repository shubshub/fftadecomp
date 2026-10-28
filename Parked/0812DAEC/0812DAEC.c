#include "ffta.h"

struct Object0812DAEC {
    u8 unknown_00[0xF8];
    u8 position;
};

extern u8 func_0812C960(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_0812D07C(const void *object, u16 entry, u32 context);

/* Complete [0x0812DAEC, 0x0812DB5A): 110 bytes, 52 instructions. */
u32 func_0812DAEC(const struct Object0812DAEC *first,
                  const struct Object0812DAEC *second, u32 context)
{
    s32 difference = first->position - second->position;
    s32 slot;
    s32 entry;

    if (difference < 0)
        difference = -difference;
    if (func_0812C960(second) != 0 || difference != 2)
        return 0;
    for (slot = 0; slot < 5; slot++) {
        entry = func_080C7EA4(second, (u8)(slot + 0x1D));

        if (entry != 0) {
            u16 identifier = entry;
            u8 allowed = func_0812D07C(second, identifier, context);

            if (allowed == 0)
                return 0;
        }
    }
    return 100;
}
