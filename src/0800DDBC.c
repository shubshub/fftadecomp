#include "ffta.h"

struct Effect0800DDBC {
    u8 unknown_00[0x1C];
};

extern void func_0800C720(struct Effect0800DDBC *effect,
                        u16 *destination, u8 stride);

void func_0800DDBC(struct Effect0800DDBC effects[2], u16 *destination)
{
    func_0800C720(&effects[0], destination, 4);
    func_0800C720(&effects[1], destination + 1, 4);
}
