#include "ffta.h"

// Complete target: [0x080835A4, 0x080837AA), 518 bytes, 259 instructions.

typedef struct {
    u8 unknown_00[0x0c];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16;
    u8 rows;
    u16 count;
    u16 offset;
    u16 tile_base;
    u8 unknown_1e;
    u8 palette;
} List080835A4;

typedef struct {
    u8 unknown_00[8];
    u16 text_id;
    u8 unknown_0a[4];
    u8 flags;
    u8 limit;
    u8 unknown_10[4];
} Entry080835A4;

typedef struct {
    u8 unknown_00[4];
    const u8 **texts;
    u8 unknown_08[0x10];
    Entry080835A4 *entries;
} Table080835A4;

typedef struct {
    u8 unknown_00[0x10];
    u8 *vram;
    u8 unknown_14[0x1c];
    u16 object_id;
    u8 unknown_32[0x46];
    List080835A4 list;
    u8 unknown_98[0x30];
    Table080835A4 *table;
} Slot080835A4;

typedef struct {
    u8 unknown_0000[0x68c];
    u8 text[0x2c88 - 0x68c];
    Slot080835A4 slots[1];
} State080835A4;

typedef struct {
    u8 unknown_00[0x28];
    u8 stride;
    u8 unknown_29[0x21];
    s8 width;
    u8 unknown_4b;
} RenderObject080835A4;

extern State080835A4 *data_03002818;
extern RenderObject080835A4 data_030009E0[];
extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u16 func_08017B68(List080835A4 *list, u32 row);
extern void func_08015110(void *context, void *destination, const u8 *text,
                         u32 mode, u32 reset);
extern void func_08089834(u16 *output, u16 style, u16 number, u16 digits,
                          u16 leading_zeroes, u16 tile_base);
extern void func_080897C4(u16 *destination, u16 value, u16 stride,
                          u16 width, u16 height, u16 attributes, s32 step);
extern void func_08089748(u16 *destination, u16 limit, u16 value, u16 attributes);

static inline u16 clamp_row(List080835A4 *list, u32 row)
{
    s16 value = (s8)row + list->offset;

    if (value < 0)
        return 0;
    else if (value > (s16)list->count - 1)
        return list->count - 1;
    else
        return value;
}

void func_080835A4(s32 index, u16 row, List080835A4 *list)
{
    u16 object_id;
    u8 limit;
    Table080835A4 *table;
    u16 width;
    u32 flags;
    List080835A4 *menu;
    u16 line;
    u16 tile;
    u8 *vram;
    u32 zero;
    u16 entry_index;
    const u8 *text;
    u16 value;
    u16 *dst;

    table = data_03002818->slots[index].table;
    object_id = data_03002818->slots[index].object_id;
    width = data_030009E0[object_id].width;
    menu = (List080835A4 *)((u8 *)data_03002818 + index * sizeof(Slot080835A4) + 0x2d00);
    line = clamp_row(menu, row);
    /* Called by name: written as %, agbcc keeps &data_03002818 in a callee-saved
       register across the call, where the ROM reloads it afterwards. */
    tile = (u16)func_08142950(line, menu->rows) * (width << 1) + menu->tile_base;
    vram = data_03002818->slots[index].vram + (tile << 5);
    zero = 0;
    func_08141868(&zero, vram, (width << 4) | 0x01000000);

    entry_index = func_08017B68(&data_03002818->slots[index].list, (s8)row);
    text = table->texts[table->entries[entry_index].text_id];
    flags = table->entries[entry_index].flags;
    limit = table->entries[entry_index].limit;
    value = table->entries[entry_index].flags & 0x7f;
    func_08015110(data_03002818->text, vram, text, ((flags >> 7) ^ 1) & 1, 1);

    dst = &list->tiles[list->stride * 2 * (entry_index % 6) + 11];
    if (flags != 0xff) {
        if (value >= limit) {
            dst[5] = 0;
            dst[6] = 0;
            func_080897C4(dst, 0xc1, data_030009E0[object_id].stride, 5, 2, 0xd000, 1);
            (dst + list->stride)[5] = 0;
            (dst + list->stride)[6] = 0;
        } else {
            dst[0] = 0;
            dst[1] = 0;
            dst[5] = 0;
            func_08089834(dst + 2, 0, value * 10, 3, 0, 0xc000);
            func_08089748(dst + list->stride, limit, value, 0xd000);
        }
    } else {
        for (value = 0; value <= 6; value++) {
            dst[value] = 0;
            (dst + list->stride)[value] = 0;
        }
    }
}
