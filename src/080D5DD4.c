#include "ffta.h"

// Complete [0x080D5DD4, 0x080D5E80): 172 bytes, 84 instructions.

struct Resource080D5DD4 {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

extern u32 func_08011348(const void *entries, const void *data, u16 index,
                        u8 layer, s16 x, s16 y, s16 width, s16 height,
                        u8 mode, u16 attributes);
extern void func_08011138(void *, u8);

u32 func_080D5DD4(const struct Resource080D5DD4 *header,
                 u16 index, u16 x, u16 y,
                 u16 height, u8 mode, u8 palette)
{
    const void *entries = header->data;
    const void *data = (const u8 *)header + header->offset;
    u16 attributes = 0;
    u32 object;

    if (header->flags & 4)
        attributes |= 0x2000;
    if (header->flags & 8)
        attributes |= 0x4000;
    object = func_08011348(entries, data, index, 1,
                           (s16)x, (s16)y, 0, (s16)height,
                           mode, attributes);
    func_08011138((void *)object, palette);
    return object;
}
