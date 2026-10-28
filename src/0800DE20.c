#include "ffta.h"

struct Effect0800DE20 {
    u8 unknown_00[0x1C];
};

extern void func_0800C804(struct Effect0800DE20 *effect,
                        u16 *destination, u8 stride);

void func_0800DE20(struct Effect0800DE20 effects[2], u16 *destination)
{
    func_0800C804(&effects[0], destination, 4);
    func_0800C804(&effects[1], destination + 1, 4);
}
