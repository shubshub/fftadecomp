#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 selected;
    u8 unknown_04[10];
    u8 type;
    u8 palette;
    u16 id;
    u16 unknown_12;
} TextEntry08042D4C;

typedef struct {
    u8 unknown_00[0x18];
    TextEntry08042D4C *entries;
} TextList08042D4C;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u8 unknown_14[0x1c];
    u16 id;
    u8 unknown_32[0x46];
    u8 list[0x48];
    u8 unknown_c0[8];
    TextList08042D4C *text;
} Record08042D4C;

typedef struct {
    u8 unknown_000[0x954];
    Record08042D4C records[1];
} State08042D4C;

typedef struct {
    u8 unknown_00[0x4a];
    s8 width;
    u8 unknown_4b;
} Unit08042D4C;

extern State08042D4C *g_state_03002810;
extern Unit08042D4C data_030009E0[];
extern u16 func_08017B68(void *, u32);
extern u16 func_08037F40(void *, s8, u16);
extern void func_08141868(const void *, void *, u32);
extern void func_08042B70(u16, u16, u8 *, TextList08042D4C *, void *, u8, u32);
extern void func_08042C10(u16, void *, u16, u32);

/* Complete [0x08042D4C, 0x08042E48): 252 bytes. */
void func_08042D4C(s32 slot, s16 row, void *map)
{
    TextList08042D4C *text = g_state_03002810->records[slot].text;
    u16 selected = func_08017B68(g_state_03002810->records[slot].list, (s8)row);
    u16 unit = g_state_03002810->records[slot].id;
    u16 width = data_030009E0[unit].width;
    u16 offset = func_08037F40(g_state_03002810->records[slot].list, (s8)row, width);
    u8 *tiles = g_state_03002810->records[slot].tiles + (offset << 5);
    u32 fill = 0;
    u16 palette;
    u16 id;

    func_08141868(&fill, tiles, (width << 4) | 0x01000000);
    id = text->entries[selected].id;
    palette = (text->entries[selected].palette & 15) << 12;
    func_08042B70(id, selected, tiles, text, map,
                 text->entries[selected].type, text->entries[selected].selected);
    func_08042C10(selected, map, palette, 0);
}
