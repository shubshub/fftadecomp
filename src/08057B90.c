#include "ffta.h"

extern void func_08000D48(u8 channel, const void *source, void *destination, u32 control);

/* Complete target: [0x08057B90, 0x08057BEC), 92 bytes. */
void func_08057B90(u8 channel, u16 *buffer, u8 split, u16 first, u16 second)
{
    u8 row;

    for (row = 0; row < split; row++)
        buffer[row] = first;
    for (row = split; row < 160; row++)
        buffer[row] = second;
    func_08000D48(channel, buffer, (void *)0x04000050, 0x20400001);
}
