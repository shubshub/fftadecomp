/* 0x0804AA20..0x0804AD44: complete 804-byte Thumb owner, 317 instructions
 * and the literal pools at 0x0804ABA0, 0x0804AC28, 0x0804AC44, 0x0804ACB8
 * and 0x0804AD30.
 * Opens window 5 with one row per entry of the list at +0x914 of the
 * shared state (src/08038734.c compacts its first four): an item icon and
 * name, another icon and name, or the empty-row text.
 */
#include "ffta.h"

/* The list entries of src/08038734.c and src/0803890C.c. */
typedef struct {
    u16 id;
    u16 kind;
    u8 unknown_04[4];
} ListEntry;

typedef struct {
    u8 unknown_00[0x90];
    u16 *second_resource;
    u16 *first_resource;
    u8 unknown_98[0x87C];
    ListEntry entries[1];
    u8 unknown_91C[0x330];
    u8 text_state[1];
} ListState;

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 unknown_29[0xB];
    u8 x;
    u8 y;
    u8 unknown_36[0x16];
} TileWindow;

/* The item table of src/0804B95C.c: an item number indexes it as
 * [item - 375]. */
typedef struct {
    u16 index;
    u8 category;
    u8 unknown_03[13];
} ItemCategory;

extern ListState *g_state_03002810;
extern u8 *data_03002740[];
extern TileWindow data_030009E0[];
extern u8 data_02003CB0[];
extern const ItemCategory g_table_08521214[];
extern const u8 *const g_table_08526680[];
extern const u8 *const data_085668B0[];

extern void *func_0808A268(s32 index, u8 mode,
    u16 *first_resource, u16 *second_resource,
    u8 *first_tiles, u8 *second_tiles, u8 *first_text, u8 *second_text,
    u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile, u16 count,
    u16 flags);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080CB980(void *buffer, u32 id);
extern u8 func_080CB99C(u32 id);
extern void func_08089400(s32 index, u16 tile, u8 x, u8 y, u8 width,
    u8 height);
extern void func_08015110(void *context, void *destination, const u8 *text,
    u8 mode, u8 reset);

/* The SDK's CpuFill16 (pret include/gba/macro.h, CPU_FILL with 16 bits):
 * vu16 written out, func_0814186C is CpuSet and 0x01000000 is
 * CPU_SET_16BIT | CPU_SET_SRC_FIXED.  Each fill forms its slot's address,
 * then stores the zero there (add r1, sp, #0x38 then movs r0, #0 at
 * 0x0804AB2C; the same at 0x0804ABE2, 0x0804AC5C and 0x0804ACD8).  The
 * slots are sp+0x38, sp+0x3A, sp+0x3C and sp+0x3C: the last two fills share
 * one.  agbcc gives a volatile temporary its slot as it expands the
 * declaration and lets a later block reuse it; a plain local whose address
 * is taken keeps its slot, which puts the empty row's fill at sp+0x3E.  The
 * kit admits the temporary as the SDK's BIOS fill (fftadecomp-kit#164). */
#define CpuFill16(value, dest, size)                                      \
{                                                                         \
    volatile u16 tmp = (volatile u16)(value);                             \
    func_0814186C((void *)&tmp, (dest),                                   \
        0x01000000 | ((size) / (16 / 8) & 0x1FFFFF));                     \
}

/* An entry icon: decompress it into the buffer, clear the row's tiles,
 * copy the icon to the row start and set its 2x2 map cell in window 5.
 * The ROM repeats the block for both entry kinds, 0x0804ABD6..0x0804AC1A
 * and 0x0804AC4E..0x0804AC92, apart from the clear size. */
#define DRAW_ICON(icon_id, clear_size)                                    \
{                                                                         \
    u16 icon = (icon_id);                                                 \
                                                                          \
    func_080CB980(buffer, icon);                                          \
    tiles = (u8 *)0x0600A560 + i * 0x340;                                 \
    CpuFill16(0, tiles, clear_size);                                      \
    func_0814186C(buffer, tiles, 0x40);                                   \
    palette = (func_080CB99C(icon) + 13) << 12;                           \
    func_08089400(5, palette, 0, i * 2 + 2, 2, 2);                        \
}

void func_0804AA20(s32 count)
{
    u8 *text = data_02003CB0;
    s32 i;
    u32 value;
    u32 index;
    const ItemCategory *category;
    const u8 *name;
    u16 palette;
    u8 *tiles;

    func_0808A268(5, 12, g_state_03002810->first_resource,
        g_state_03002810->second_resource,
        data_03002740[5], data_03002740[5] + 0x152, 0, 0,
        0, 6, 13, 13, 0, 6, 13, 13, 13, 13);
    data_030009E0[5].x = 0;
    data_030009E0[5].y = 7;
    for (i = 0; i < 10; i += 2)
        func_0808B7C0(5, func_0808B8E4(5, 1, 0, i + 2),
            (u16)(0x12B + 13 * i), 13, 0xC000);
    func_08016344(data_030009E0[5].second_plane, data_030009E0[5].width,
        (u8)(count * 2 + 3), 0xC0, data_030009E0[5].width, 5, 12);
    func_08016560(data_030009E0[5].first_plane, 13, (u8)(count * 2 + 3),
        0xC0, 13, 1, 12);
    func_08035678(0xC03E, func_0808B8E4(5, 1, 1, 1),
        func_08018524(text, 0x3E, 13), 1);
    CpuFill16(0, (u8 *)0x0600A560, 0x1040);
    for (i = 0; i < count; i++) {
        u8 *buffer = data_02003CB0;

        /* The loop condition already holds here, but the ROM tests it
         * again on the way in: cmp r8, r1 at 0x0804AB54, branching to the
         * empty row at 0x0804ACD4 (the same test is at 0x0804A7E6 in
         * func_0804A6B0). */
        if (i < count && g_state_03002810->entries[i].id != 0) {
            if (g_state_03002810->entries[i].kind == 1) {
                /* value holds the item number here and the icon below:
                 * r7 both times (0x0804AB82, 0x0804AC3E), copied to the
                 * icon in r4 at 0x0804AC4E. */
                value = g_table_08521214[g_state_03002810->entries[i].id].index;
                category = &g_table_08521214[value - 375];
                DRAW_ICON(category->category ? 0x18A + category->category : 0,
                    0x340);
                name = g_table_08526680[value + 0x7B];
                func_08015110(g_state_03002810->text_state,
                    (u8 *)0x0600A5E0 + i * 0x340, name, 0, 1);
            } else {
                index = g_state_03002810->entries[i].id;
                if (index <= 85) {
                    value = 0x189;
                } else {
                    index -= 85;
                    value = 0x18A;
                }
                /* This clear and the empty row's cover 0x2C0 bytes from the
                 * row start (0x01000160 at 0x0804AC64 and 0x0804ACE0), where
                 * the item arm clears the whole 0x340-byte row (0x010001A0
                 * at 0x0804ABEC), so they leave the last 0x80 bytes of the
                 * text area.  Those are zero already: the fill before the
                 * loop clears five rows (0x1040 bytes), and the one caller,
                 * func_0804AFE0 (bl at 0x0804B6CE), passes the entry count
                 * func_08038734 returns, at most 4. */
                DRAW_ICON(value, 0x2C0);
                name = g_table_08526680[index + 0x271];
                func_08015110(g_state_03002810->text_state,
                    (u8 *)0x0600A5E0 + i * 0x340, name, 0, 1);
            }
        } else {
            tiles = (u8 *)0x0600A560 + i * 0x340;
            CpuFill16(0, tiles, 0x2C0);
            name = data_085668B0[42];
            func_08015110(g_state_03002810->text_state,
                (u8 *)0x0600A5E0 + i * 0x340, name, 5, 1);
        }
    }
}
