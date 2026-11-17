#include "ffta.h"

// Target: 080153FC, complete 218-byte Thumb function
// [0x080153FC, 0x080154D6), literal pool word 0x08149868 at 0x08015484.

extern const u8 data_08149868[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_08013728(void *cursor, s16 amount);
extern u16 func_08015110(void *drawing, const void *source,
    const u8 *text, u8 palette, u8 reset);

u16 func_080153FC(void *drawing, u32 unused, const u8 *text, u8 palette)
{
    u8 mark[3];
    const u8 *cursor;
    u8 single = 1;
    u8 kind;

    func_081443FC(mark, data_08149868, sizeof(mark));
    kind = text[2] & 0xF0;
    if (kind != 0)
        single = kind != 0x10;
    cursor = text + 3;

    func_08013728(drawing, 2);
    func_08015110(drawing, 0, mark, palette, 0);
    func_08013728(drawing, -2);
    cursor += func_08015110(drawing, 0, cursor, palette, 0);

    if (single) {
        func_08013728(drawing, 0x10);
    } else {
        func_08013728(drawing, 2);
        func_08015110(drawing, 0, mark, palette, 0);
        func_08013728(drawing, -2);
    }
    cursor += func_08015110(drawing, 0, cursor, palette, 0);
    return cursor - text;
}
