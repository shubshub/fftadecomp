#include "ffta.h"

/* Complete 0x08039DF4..0x0803A07C: 648 bytes, 258 instructions.
 * Draws the item/ability name window: window 5 is opened, its icon and
 * name are copied into VRAM and the text is centred above them. */

typedef struct {
    u8 unknown_00[0x90];
    u16 *second_resource;
    u16 *first_resource;
    u8 unknown_98[0xBB4];
    u8 text_state[1];
} Resources08039DF4;

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 rows;
    u8 unknown_2A[0x22];
} Window08039DF4;

typedef struct {
    u16 text;
    u8 unknown_02[0x1E];
} Item08039DF4;

typedef struct {
    u8 unknown_00[2];
    u8 icon;
    u8 unknown_03[0xD];
} Ability08039DF4;

extern Resources08039DF4 *g_state_03002810;
extern u8 *data_03002740[];
extern Window08039DF4 data_030009E0[];
extern u8 data_02003CB0[];

extern const u8 *const data_085668B0[];
extern const Item08039DF4 g_table_0851D180[];
extern const Ability08039DF4 data_0851FAA4[];
extern u8 *const g_table_08526680[];

extern void *func_0808A268(s32 index, u8 mode,
    u16 *first_resource, u16 *second_resource,
    u8 *first_tiles, u8 *second_tiles, u8 *first_text, u8 *second_text,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(u16 *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_0814186C(const void *, void *, u32);
extern u16 func_080161BC(const u8 *text);
extern void func_08015110(void *context, void *destination, const u8 *text,
    u8 mode, u8 reset);
extern void func_080CB980(void *buffer, u32 id);
extern u8 func_080CB99C(u32 id);
extern void func_08038CF0(u8 *destination, const u8 *first, const u8 *second);
extern void func_0808B7C0(s32 index, u16 *, u16 tile, u16 count, u16 flags);
extern void func_08089400(s32 index, u16 tile, u8 x, u8 y, u8 width,
    u8 height);
extern u32 func_0808A604(s32 index, u16 mode);

void func_08039DF4(u16 id)
{
    u8 *buffer = data_02003CB0;
    u16 clear;
    const u8 *text;
    u16 width;
    u16 palette;
    u16 icon;
    const Ability08039DF4 *ability;
    u8 *p;
    s32 left;

    func_0808A268(5, 12, g_state_03002810->first_resource,
        g_state_03002810->second_resource,
        data_03002740[5], data_03002740[5] + 0xDC, 0, 0,
        3, 9, 22, 5, 3, 9, 22, 5, 22, 5);
    func_08016344(data_030009E0[5].second_plane,
        data_030009E0[5].stride, data_030009E0[5].rows,
        0xC0, data_030009E0[5].stride, 5, 12);
    func_08016560(data_030009E0[5].first_plane, 22, 5, 0xC0, 22, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(5, 1, 1, 1),
        func_08018524(buffer, 0x3E, 0x12), 1);
    /* VRAM addresses are plain numbers, as in src/08038ECC.c: each arm
     * reloads the pool word 0x0600AFE0 (0x08039F00, 0x08039F94) instead of
     * reusing r4 from 0x08039EBA. */
    clear = 0;
    func_0814186C(&clear, (u8 *)0x0600AFE0, 0x01000280);
    text = data_085668B0[0x51];
    width = func_080161BC(text);
    func_08015110(g_state_03002810->text_state, (u8 *)0x0600AFE0, text, 0, 1);

    if (id < 0x178) {
        u16 text_index = g_table_0851D180[id].text;

        /* p is the icon's VRAM destination and then the name: the ROM keeps
         * both in r6 in each arm (0x08039F02 and 0x08039F1C, 0x08039F96 and
         * 0x08039FBE), and copies the else-arm destination out of r6 at
         * 0x08039F9A. */
        p = (u8 *)0x0600AFE0 + width * 64;
        func_080CB980(buffer, id);
        func_0814186C(buffer, p, 0x40);
        p = g_table_08526680[text_index];
        palette = (func_080CB99C(id) + 13) << 12;
    } else {
        ability = &data_0851FAA4[id];
        icon = ability->icon ? ability->icon + 0x18A : 0;
        func_080CB980(buffer, icon);
        p = (u8 *)0x0600AFE0 + width * 64;
        func_0814186C(buffer, p, 0x40);
        palette = (func_080CB99C(icon) + 13) << 12;
        p = g_table_08526680[id + 0x7B];
    }

    text = data_085668B0[0x52];
    func_08038CF0(buffer, p, text);
    /* The name goes two columns (the icon) after the label. */
    func_08015110(g_state_03002810->text_state,
        (u8 *)0x0600AFE0 + (width + 2) * 64, buffer, 0, 1);
    left = (20 - (width + 2 + func_080161BC(buffer))) / 2;
    func_0808B7C0(5, func_0808B8E4(5, 1, left + 1, 2), 0x17F,
        20 - left * 2, 0xC000);
    func_08089400(5, palette, left + width + 1, 2, 2, 2);
    func_0808A604(5, 2);
}
