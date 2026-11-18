#include "ffta.h"

// Complete [0x0801A320, 0x0801A42C): 268 bytes, 134 instructions.

struct PackedRecord0801A320 {
    u8 unknown_00[0xC];
    u32 palette;
    u8 unknown_10[0x46];
    u8 palette_index;
    u8 unknown_57;
} __attribute__((packed));

struct CompressedHeader0801A320 {
    u8 type;
    u32 size : 24;
    u8 data[0];
} __attribute__((packed));

extern u16 data_02007F10;
extern u16 data_03003860[];
extern const struct PackedRecord0801A320 data_08569104[];
extern void (*const data_0836D4BC)(void *destination, const void *source, u32 length);
extern const u16 data_08427A04[];
extern const u16 data_0842CC80[];
extern void func_0801E6D4(u8 *first, u8 *second);
extern u32 func_0801AE9C(void);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141890(const void *source, void *destination);
extern void func_0800543C(void *destination, const void *source);

void func_0801A320(void)
{
    if (data_02007F10 == 0xFF) {
        u8 first;
        u8 count;
        u16 zero;

        func_0801E6D4(&first, &count);
        zero = 0;
        func_0814186C(&zero, data_03003860, 0x01000000 | (count << 4));
    } else {
        u16 saved = data_03003860[0];
        u8 first;
        u8 count;
        u8 *destination;
        u8 mode;

        func_0801E6D4(&first, &count);
        destination = (u8 *)data_03003860 + first * 32;
        mode = func_0801AE9C();
        if (mode == 0) {
            const struct CompressedHeader0801A320 *header =
                (const void *)((const u8 *)data_08569104
                               + data_08569104[data_02007F10].palette);
            const u8 *data = header->data;

            if (header->type == 0x10)
                func_08141890(header, destination);
            else
                data_0836D4BC(destination, data, header->size);
        } else {
            u8 index = data_08569104[data_02007F10].palette_index;

            if (mode == 1)
                func_0800543C(destination,
                              (const u8 *)data_08427A04 + data_08427A04[index]);
            else
                func_0800543C(destination,
                              (const u8 *)data_0842CC80 + data_0842CC80[index]);
        }
        data_03003860[0] = saved;
    }
}
