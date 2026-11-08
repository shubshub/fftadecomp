#include "ffta.h"

extern u16 func_080161A0(u8 x, u8 y, u8 stride);
extern u32 func_08142AB0(u32, u32);
extern u32 func_08142B28(u32, u32);

typedef struct {
    u8 unknown_00[0xc];
    u16 *tiles;
    u8 unknown_10[0xe];
    u8 stride;
} Window0804FFB8;

/* Complete [0x0804FFB8, 0x0805005C): 164 bytes; the fifth argument is the
 * first incoming stack word ([sp, #0x14] after the five-register push). */
void func_0804FFB8(Window0804FFB8 *window, u32 x, u32 y, u16 value, u8 alternate)
{
    u16 *destination;
    u16 digit = value;

    destination = window->tiles + func_080161A0(x, y, window->stride);

    digit = func_08142AB0(digit, 100);
    destination[0] = digit + (alternate ? 0x601E : 0xD01E);

    digit = func_08142B28((u16)func_08142AB0(value, 10), 10);
    destination[1] = digit + (alternate ? 0x601E : 0xD01E);

    digit = func_08142B28(value, 10);
    destination[2] = digit + (alternate ? 0x601E : 0xD01E);
}
