#include "ffta.h"

struct Resource080D5CC0 {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

extern u32 func_08011348(u32 first, u32 second, u16 third, u8 fourth,
                        s16 fifth, s16 sixth, s16 seventh, s16 eighth,
                        s16 ninth, u16 tenth);
extern void func_0801E6F0(u16 *first, u16 *second);
extern void func_08011138(u8 *object, u8 value);

/* Complete [0x080D5CC0, 0x080D5DD2): 274 bytes, 134 instructions.
 * Target begins f0b557464e464546e0b48db0159c169d and ends
 * 201c0db038bc9846a146aa46f0bc02bc0847.
 */
u32 func_080D5CC0(const struct Resource080D5CC0 *header,
                 u16 index, u16 x, u16 y, u16 width,
                 u8 mode, u8 value, u8 relative)
{
    u16 first, second;
    const void *entries = header->data;
    const void *data = (const u8 *)header + header->offset;
    u16 attributes = 0;
    u32 result;

    if (header->flags & 4)
        attributes |= 0x2000;
    if (header->flags & 8)
        attributes |= 0x4000;

    if (relative == 0) {
        result = func_08011348((u32)entries, (u32)data, index, 0,
                              (s16)x, (s16)y, 0, (s16)width,
                              mode, attributes);
    } else {
        func_0801E6F0(&first, &second);
        result = func_08011348((u32)entries, (u32)data, index, 1,
                              (s16)((s16)x + first),
                              (s16)((s16)y + second), 0, (s16)width,
                              mode, attributes);
    }
    func_08011138((u8 *)result, value);
    return result;
}
