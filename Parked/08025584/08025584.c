#include "ffta.h"

// 08025584..080255FC: 120 bytes, 60 instructions.

typedef struct {
    u8 unknown_00[0x10];
    u16 selected;
    u8 unknown_12[0x0A];
    const void *object;
} State08025584;

extern State08025584 *data_0200F438;
u8 func_080CE410(const void *object);
void func_080C9208(u16 index, u8 *flags);
s32 func_080C9134(u8 selector);

u8 func_08025584(void)
{
    u8 flags[4];
    u8 i;
    u8 count;
    u8 result;

    func_080C9208(func_080CE410(data_0200F438->object) + 0xCA, flags);
    result = 0;
    count = 0;
    for (i = 0; i < 3; i++) {
        if (flags[i] != 0) {
            if (count == data_0200F438->selected) {
                result = i;
                break;
            }
            count++;
        }
    }
    return func_080C9134(flags[result]);
}
