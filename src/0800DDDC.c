#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Effect0800DDDC;

extern void func_0800C720(Effect0800DDDC *effect,
                         u16 *destination, u8 stride);

/* Complete [0x0800DDDC, 0x0800DE14): 56 bytes, 24 instructions. */
void func_0800DDDC(Effect0800DDDC effects[4], u16 *destination)
{
    func_0800C720(&effects[0], destination, 8);
    func_0800C720(&effects[1], destination + 1, 8);
    func_0800C720(&effects[2], destination + 2, 8);
    func_0800C720(&effects[3], destination + 3, 8);
}
