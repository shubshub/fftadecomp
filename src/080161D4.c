#include "ffta.h"

/* 0x080161D4..0x08016210: 60 bytes / 26 instructions. */
extern u8 data_030008B0[];
extern void func_080154D8(void *source, void *destination, void *buffer,
                          u8 rows, u8 width, u8 height, u8 mode,
                          void *graphics, u32 size);

void func_080161D4(void *source, void *destination, void *buffer,
                   u8 rows, u8 width, u8 height, u8 mode)
{
    func_080154D8(source, destination, buffer, rows, width, height, mode,
                  data_030008B0, 0x800);
}
