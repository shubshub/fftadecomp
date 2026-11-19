#include "ffta.h"

/* Complete [0x080461D4, 0x08046854): 1664 bytes, 656 instructions. */

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
} __attribute__((packed)) Item080461D4;

/* A 0x46-byte row of g_table_0855AE4C (movs r1, #0x46; muls at 0x080461F2).
 * The gains are the bytes func_08046854 (src/08046854.c) adds to the slots;
 * its caller passes the same row (str r4 to 0x0201F508 at 0x0804788A). */
typedef struct {
    u8 unknown_00[0x2A];
    u8 gains[16];
    u8 unknown_3A[0x0C];
} __attribute__((packed)) Entry080461D4;

typedef struct {
    u8 unknown_0000[0x21B4];
    u8 slots[16][2];
} State080461D4;

typedef struct {
    u8 unknown_000[0xC4C];
    u8 text_state[1];
} MenuState080461D4;

extern const Entry080461D4 g_table_0855AE4C[];
extern State080461D4 g_state_02000000;
extern MenuState080461D4 *g_state_03002810;
extern u8 data_0600AFE0[];
extern const u8 *const data_085668B0[];

extern void func_080142DC(u8 *text, u16 value, u8 digits);
extern u8 *func_0808B92C(u32 index, u8 *tiles, u32 column, u32 row);
extern void func_08015110(void *context, void *tiles, const u8 *text,
                          u32 mode, u32 spacing);
extern void func_080379A8(u32 index, s32 x, s32 y, s32 width, s32 height,
                          u16 palette);
extern void func_080378C8(u32 index, u8 *tiles, s32 x, s32 y, u16 graphic,
                          const u8 *text);

void func_080461D4(Item080461D4 *item, u16 flags)
{
    const Entry080461D4 *entry = &g_table_0855AE4C[item->id];
    u8 level = g_state_02000000.slots[0][0];
    u8 gain = entry->gains[0];
    u8 text[32];
    u16 icon;

    func_08015110(g_state_03002810->text_state,
                  func_0808B92C(5, data_0600AFE0, 0, 0), data_085668B0[12], 0, 1);
    if (gain < 10) {
        func_080142DC(text, gain, 1);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 10, 0), text, 0, 1);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 12, 0), data_085668B0[13], 0, 1);
    } else if (gain < 100) {
        func_080142DC(text, gain, 2);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 10, 0), text, 0, 1);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 12, 0), data_085668B0[13], 0, 1);
    } else {
        func_080142DC(text, gain, 3);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 9, 0), text, 0, 1);
        func_08015110(g_state_03002810->text_state,
                      func_0808B92C(5, data_0600AFE0, 12, 0), data_085668B0[13], 0, 1);
    }
    func_08015110(g_state_03002810->text_state,
                  func_0808B92C(5, data_0600AFE0, 20, 0), data_085668B0[40], 0, 1);
    func_080142DC(text, level, level >= 10 ? 2 : 1);
    func_080379A8(5, 23, 2, 2, 2, (flags & 1) ? 11 : 12);
    func_08015110(g_state_03002810->text_state,
                  func_0808B92C(5, data_0600AFE0, 22, 0), text, 0, 1);
    func_08015110(g_state_03002810->text_state,
                  func_0808B92C(5, data_0600AFE0, 0, 2), data_085668B0[14], 0, 1);

    /* Each row sets the icon first: r7 is loaded at the start of the row
     * (movs r7, #0x14 at 0x080463DE and 0x08046688, through #0x1B) and
     * stored as func_080378C8's fifth argument after the other two calls. */
    if (!(flags & 0x8000)) {
        icon = 0x14;
        func_080142DC(text, g_state_02000000.slots[1][0], 2);
        func_080379A8(5, 5, 6, 2, 2, (flags & 0x2) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 1, 4, icon, text);
        icon = 0x15;
        func_080142DC(text, g_state_02000000.slots[2][0], 2);
        func_080379A8(5, 11, 6, 2, 2, (flags & 0x4) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 7, 4, icon, text);
        icon = 0x16;
        func_080142DC(text, g_state_02000000.slots[3][0], 2);
        func_080379A8(5, 17, 6, 2, 2, (flags & 0x8) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 13, 4, icon, text);
        icon = 0x17;
        func_080142DC(text, g_state_02000000.slots[4][0], 2);
        func_080379A8(5, 23, 6, 2, 2, (flags & 0x10) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 19, 4, icon, text);
        icon = 0x18;
        func_080142DC(text, g_state_02000000.slots[5][0], 2);
        func_080379A8(5, 5, 8, 2, 2, (flags & 0x20) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 1, 6, icon, text);
        icon = 0x19;
        func_080142DC(text, g_state_02000000.slots[6][0], 2);
        func_080379A8(5, 11, 8, 2, 2, (flags & 0x40) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 7, 6, icon, text);
        icon = 0x1A;
        func_080142DC(text, g_state_02000000.slots[7][0], 2);
        func_080379A8(5, 17, 8, 2, 2, (flags & 0x80) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 13, 6, icon, text);
        icon = 0x1B;
        func_080142DC(text, g_state_02000000.slots[8][0], 2);
        func_080379A8(5, 23, 8, 2, 2, (flags & 0x100) ? 11 : 12);
        func_080378C8(5, data_0600AFE0, 19, 6, icon, text);
    } else {
        icon = 0x14;
        func_080142DC(text, g_state_02000000.slots[1][1], 2);
        func_080379A8(5, 5, 6, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 1, 4, icon, text);
        icon = 0x15;
        func_080142DC(text, g_state_02000000.slots[2][1], 2);
        func_080379A8(5, 11, 6, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 7, 4, icon, text);
        icon = 0x16;
        func_080142DC(text, g_state_02000000.slots[3][1], 2);
        func_080379A8(5, 17, 6, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 13, 4, icon, text);
        icon = 0x17;
        func_080142DC(text, g_state_02000000.slots[4][1], 2);
        func_080379A8(5, 23, 6, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 19, 4, icon, text);
        icon = 0x18;
        func_080142DC(text, g_state_02000000.slots[5][1], 2);
        func_080379A8(5, 5, 8, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 1, 6, icon, text);
        icon = 0x19;
        func_080142DC(text, g_state_02000000.slots[6][1], 2);
        func_080379A8(5, 11, 8, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 7, 6, icon, text);
        icon = 0x1A;
        func_080142DC(text, g_state_02000000.slots[7][1], 2);
        func_080379A8(5, 17, 8, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 13, 6, icon, text);
        icon = 0x1B;
        func_080142DC(text, g_state_02000000.slots[8][1], 2);
        func_080379A8(5, 23, 8, 2, 2, 12);
        func_080378C8(5, data_0600AFE0, 19, 6, icon, text);
    }
}
