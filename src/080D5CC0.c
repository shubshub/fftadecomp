#include "ffta.h"

/* Complete [0x080D5CC0, 0x080D5DD2): 274 bytes.
 * f0b557464e464546e0b48db0159c169d179e189fb8460904090c8a4607911204170c0897
 * 1b041b0c9c46624609922404240c0a942d062d0ea94649460b913606360e0c9642461206
 * 130e011d88468278c17809021143461800250178407802020a430421101c0840002801d0
 * 8025ad0108200240002a03d08022d201101c0543002b12d1380400140090674638040014
 * 019002932004001403904846049005954046311c5246002323e06c461a3406a8211c48f7
 * bdfc06a9089a1004001409884018000400140090099f3804001424880019000400140190
 * 002002900a990804001403900b9a049205954046311c079a01233bf7c9fa041c201c0c99
 * 3bf7bcf9201c0db038bc9846a146aa46f0bc02bc0847
 */

struct Resource080D5CC0 {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

extern u32 func_08011348(const void *entries, const void *data, u16 index,
                        u8 layer, s16 x, s16 y, s16 width, s16 height,
                        u8 mode, u16 attributes);
extern void func_08011138(void *, u8);
extern void func_0801E6F0(s16 *x, s16 *y);

u32 func_080D5CC0(const struct Resource080D5CC0 *header,
                 u16 index, s16 x, s16 y, s16 height,
                 u8 mode, u8 palette, u8 relative)
{
    const void *entries = header->data;
    const void *data = (const u8 *)header + header->offset;
    u16 attributes = 0;
    u32 object;
    s16 offset_x, offset_y;

    if (header->flags & 4)
        attributes |= 0x2000;
    if (header->flags & 8)
        attributes |= 0x4000;
    if (relative == 0) {
        object = func_08011348(entries, data, index, 0,
                               x, y, 0, height, mode, attributes);
    } else {
        func_0801E6F0(&offset_x, &offset_y);
        object = func_08011348(entries, data, index, 1,
                               x + offset_x, y + offset_y, 0, height,
                               mode, attributes);
    }
    func_08011138((void *)object, palette);
    return object;
}
