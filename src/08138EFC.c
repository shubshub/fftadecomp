#include "ffta.h"

/* Complete target [0x08138EFC, 0x08139C70): 3444 bytes, 1220 instructions,
 * including the literal pools.  The phase handler of the save-slot menu: one
 * switch on the phase byte at *state, each phase storing the next one. */

typedef struct {
    u8 unknown_000[0x105];
    u8 cursor;
} Menu08138EFC;

typedef struct {
    u8 unknown_0000[0xA19];
    u8 ticks;
    u16 fade_step;
    u8 unknown_0A1C[0xE1C - 0xA1C];
    u8 summaries[3][0x80];
    u8 unknown_0F9C[0x2155 - 0xF9C];
    u8 has_slot0 : 1;
    u8 has_slot1 : 1;
    u8 has_slot2 : 1;
    u8 unknown_2155_3 : 5;
    u8 unknown_2156[2];
    Menu08138EFC menu;
} Context08138EFC;

typedef struct {
    u8 unknown_0000[0x72];
    u16 save_slot;
    u8 unknown_0074[0x2C11 - 0x74];
    u8 unknown_2C11_0 : 1;
    u8 unknown_2C11_1 : 1;
    u8 unknown_2C11_2 : 6;
} GameState08138EFC;

typedef struct {
    u8 state;
    u8 unknown_01[4];
    u8 step;
    u8 unknown_06[0x46];
} Window08138EFC;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[5];
    u8 enabled;
} UpdateState;

typedef struct {
    u32 unknown_00;
    void *entries;
} SharedResource;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry08138EFC;

extern Context08138EFC *data_030027D8;
extern GameState08138EFC g_state_02000000;
extern Window08138EFC data_030009E0[];
extern InputState data_03000000;
extern UpdateState data_03000ED0;
extern SharedResource data_03000E30;
extern Table data_03000880;
extern const struct FlashType *data_0200F370;
extern const u8 *const data_085668B0[];
extern const MenuEntry08138EFC data_083A8E74[];
extern const MenuEntry08138EFC data_083A8E84[];
extern const MenuEntry08138EFC data_083A8E8C[];
extern u8 data_02003CB0[];
extern u8 data_030009CC;
extern u8 data_03000E08;
extern u8 data_0201C3CC;
extern u8 data_0201C3CD;
extern u8 data_0201C3CE;
extern u16 data_0201C3D0;
extern u16 data_020084D4;
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_0600C120[];
extern u8 data_0600CD20[];

extern u32 func_08137B50(void);
extern void func_08137CC4(void);
extern void func_08137EC4(void);
extern void func_081416DC(u16 value);
extern u16 func_080CE8A8(void);
extern u16 func_080CED2C(void);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_081380A8(void);
extern void func_0804C834(void *entries, s32 count);
extern void func_08006B8C(Table *t, u8 index);
extern void func_0808B288(int unused, u8 *initialized);
extern void func_08138284(void);
extern int func_0808A604(int index, u16 mode);
extern void func_08003398(void);
extern void func_08138354(const u8 *text);
extern void func_08141540(u16 song_id);
extern void func_08141748(u16 interval);
extern u32 func_0813B480(u8 mode, void *data);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_081386BC(u32 index, void *record, u8 *tiles, u32 present,
                          u16 mode, u16 empty_mode);
extern void func_081384B0(u32 enabled);
extern void func_081385CC(u32 index, u16 base);
extern void func_08138A3C(void);
extern void func_08088DF0(Menu08138EFC *object,
                          const MenuEntry08138EFC *entries, s32 count,
                          s32 graphic, u32 palette, u32 visible, u32 enabled,
                          u32 mode, u32 variant, u32 style, u32 option);
extern u16 func_08088FEC(Menu08138EFC *object, u16 input);
extern void func_08138DA4(Menu08138EFC *object, u32 mode);
extern void func_0801174C(void *context, u8 kind, u16 selection,
                          void *first, void *second, u32 field5, s32 field6,
                          u32 width, u32 height, u32 tile);
extern u32 func_0813B0D4(u8 mode, void *data);
extern void func_0813BC7C(u8 group);
extern void func_08141570(s32 player_id, u16 song_id);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013364(void);
extern void func_0813BB04(u8 mode, void *context);
extern void func_0813839C(u8 steps, u8 phase);
extern int func_08137C48(void);
extern void func_08003888(void);
extern void func_080039E8(u16 value, u8 mode);
extern void func_0813B6A4(void);

void func_08138EFC(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
    case 1:
        func_08137B50();
        func_08137CC4();
        func_08137EC4();
        func_081416DC(0x31);
        if (func_080CE8A8() == func_080CED2C())
            func_080C9574(0x5AE, 1);
        func_081380A8();
        func_0804C834(data_03000E30.entries, 4);
        func_08006B8C(&data_03000880, 0);
        func_08006B8C(&data_03000880, 1);
        func_08006ADC(&data_03000880, 0, (u32)func_0808B288);
        data_030027D8->has_slot0 = 0;
        data_030027D8->has_slot1 = 0;
        data_030027D8->has_slot2 = 0;
        data_030027D8->ticks = 0;
        data_030027D8->fade_step = 8;
        data_0201C3CE = g_state_02000000.unknown_2C11_1;
        g_state_02000000.unknown_2C11_1 = 0;
        if (data_0201C3CE)
            func_080C9574(0x4B, 0);
        func_08138284();
        func_0808A604(3, 2);
        func_08003398();
        if (data_0200F370) {
            func_08138354(data_085668B0[72]);
            func_0808A604(3, 2);
            data_0201C3CC = 3;
            *state = 10;
        } else {
            func_08141540(0x6A);
            func_08138354(data_085668B0[68]);
            func_0808A604(3, 2);
            data_0201C3CC = 21;
            *state = 10;
        }
        break;
    case 21:
        if (!(data_03000000.pressed & 1))
            break;
        func_08141748(3);
        data_03000E08 = 0xFF;
        data_030027D8->ticks = 0;
        data_030027D8->fade_step = 0;
        data_0201C3CC = 20;
        *state = 11;
        break;
    case 3: {
        u8 *buffer = data_02003CB0;
        u8 slot = data_030009CC;

        if (func_0813B480(2, buffer)) {
            func_0814186C(buffer, data_030027D8->summaries[2], 0x40);
            data_030027D8->has_slot2 = 1;
        }
        if (func_0813B480(0, buffer)) {
            func_0814186C(buffer, data_030027D8->summaries[0], 0x40);
            data_030027D8->has_slot0 = 1;
            if (slot == 2)
                slot = 0;
        }
        if (func_0813B480(1, buffer)) {
            func_0814186C(buffer, data_030027D8->summaries[1], 0x40);
            data_030027D8->has_slot1 = 1;
            if (slot == 2)
                slot = 1;
        }
        data_030009CC = slot;
        *state = 4;
        break;
    }
    case 7: {
        u8 *buffer = data_02003CB0;
        u8 slot = data_030009CC;

        if (func_0813B480(0, buffer)) {
            func_0814186C(buffer, data_030027D8->summaries[0], 0x40);
            data_030027D8->has_slot0 = 1;
            if (slot == 2)
                slot = 0;
        }
        if (func_0813B480(1, buffer)) {
            func_0814186C(buffer, data_030027D8->summaries[1], 0x40);
            data_030027D8->has_slot1 = 1;
            /* Case 3 picks slot 1 here (movs r5, #1 at 0x08139226); this
             * copy picks slot 0 (movs r5, #0 at 0x081392B4).  The test
             * never holds: data_030009CC is only ever stored as 0 or 1
             * (0x0813AF60 and 0x0813AF80 in func_0813AE30, 0x0813B674 in
             * func_0813B57C, and these menus' write-backs). */
            if (slot == 2)
                slot = 0;
        }
        data_030009CC = slot;
        func_081386BC(4, data_030027D8->summaries[0], data_0600C120,
                      data_030027D8->has_slot0, 0, 0);
        func_081386BC(5, data_030027D8->summaries[1], data_0600CD20,
                      data_030027D8->has_slot1, 0, 0);
        func_0808A604(4, 2);
        func_0808A604(5, 2);
        data_0201C3CD = 3;
        data_030027D8->ticks = 30;
        data_0201C3CC = 8;
        *state = 16;
        break;
    }
    case 4:
        func_08138354(data_085668B0[60]);
        func_081384B0(1);
        func_081385CC(4, 0x209);
        func_081386BC(4, data_030027D8->summaries[0], data_0600C120,
                      data_030027D8->has_slot0, 0, 0);
        func_08138A3C();
        func_081385CC(5, 0x269);
        func_081386BC(5, data_030027D8->summaries[1], data_0600CD20,
                      data_030027D8->has_slot1, 0, 0);
        data_0201C3CD = 4;
        /* Indexed by the window case 12 waits on: the ROM forms the window's
         * address apart from the member offset (0x081393B4-0x081393BC,
         * strb [r0, #5]), where window 5's store uses the folded 0x181. */
        data_030009E0[data_0201C3CD].step = 1;
        func_0808A604(4, 11);
        data_030009E0[5].step = 1;
        func_0808A604(5, 11);
        func_08088DF0(&data_030027D8->menu, data_083A8E74, 2, 0, 0, 0, 0, 1,
                      0, 1, data_030009CC);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138DA4(&data_030027D8->menu, 0);
        func_08141540(0x65);
        data_0201C3CC = 8;
        *state = 12;
        break;
    case 5:
        func_08138354(data_085668B0[71]);
        func_081384B0(1);
        func_081385CC(4, 0x209);
        func_081386BC(4, data_030027D8->summaries[0], data_0600C120,
                      data_030027D8->has_slot0, 0, 0);
        func_08138A3C();
        func_081385CC(5, 0x269);
        func_081386BC(5, data_030027D8->summaries[1], data_0600CD20,
                      data_030027D8->has_slot1, 1, 1);
        data_0201C3CD = 4;
        data_030009E0[data_0201C3CD].step = 1;
        func_0808A604(4, 11);
        data_030009E0[5].step = 1;
        func_0808A604(5, 11);
        func_08088DF0(&data_030027D8->menu, data_083A8E84, 1, 0, 0, 0, 0, 1,
                      0, 1, 0);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138DA4(&data_030027D8->menu, 1);
        func_08141540(0x65);
        data_0201C3CC = 8;
        *state = 12;
        break;
    case 6:
        func_08138354(data_085668B0[71]);
        func_081384B0(1);
        func_081385CC(4, 0x209);
        func_081386BC(4, data_030027D8->summaries[0], data_0600C120,
                      data_030027D8->has_slot0, 1, 1);
        func_08138A3C();
        func_081385CC(5, 0x269);
        func_081386BC(5, data_030027D8->summaries[1], data_0600CD20,
                      data_030027D8->has_slot1, 0, 0);
        data_0201C3CD = 4;
        data_030009E0[data_0201C3CD].step = 1;
        func_0808A604(4, 11);
        data_030009E0[5].step = 1;
        func_0808A604(5, 11);
        func_08088DF0(&data_030027D8->menu, data_083A8E8C, 1, 0, 0, 0, 0, 1,
                      0, 1, 0);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138DA4(&data_030027D8->menu, 2);
        func_08141540(0x65);
        data_0201C3CC = 8;
        *state = 12;
        break;
    case 8:
        if (func_08088FEC(&data_030027D8->menu, data_03000000.repeated)) {
            func_08138DA4(&data_030027D8->menu, 0);
            func_0808A604(4, 2);
            func_0808A604(5, 2);
        }
        if (data_03000000.pressed & 1) {
            u8 *buffer = data_02003CB0;

            if (data_030027D8->menu.cursor == 0) {
                if (data_030027D8->has_slot0 && data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x25, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else if (data_030027D8->has_slot0
                           && !data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x20, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else if (!data_030027D8->has_slot0
                           && data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x25, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else {
                    func_08141540(0x64);
                    data_03000ED0.enabled = 0;
                    func_08138354(data_085668B0[62]);
                    func_0808A604(3, 2);
                    data_0201C3D0 = data_020084D4;
                    func_08141748(3);
                    data_030027D8->ticks = 30;
                    g_state_02000000.save_slot = data_030027D8->menu.cursor + 1;
                    data_0201C3CC = 9;
                    *state = 15;
                }
            } else {
                if (data_030027D8->has_slot1 && data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x25, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else if (data_030027D8->has_slot1
                           && !data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x20, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else if (!data_030027D8->has_slot1
                           && data_030027D8->has_slot2) {
                    func_0801174C(buffer, 1, 0x25, data_03000990,
                                  data_03000E80, 3, 2, 0x17, 4, 0x3A0);
                    *state = 17;
                } else {
                    func_08141540(0x64);
                    data_03000ED0.enabled = 0;
                    func_08138354(data_085668B0[62]);
                    func_0808A604(3, 2);
                    data_0201C3D0 = data_020084D4;
                    func_08141748(3);
                    data_030027D8->ticks = 30;
                    g_state_02000000.save_slot = data_030027D8->menu.cursor + 1;
                    data_0201C3CC = 9;
                    *state = 15;
                }
            }
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x68);
            data_03000E08 = 0xFF;
            func_08141748(3);
            data_030027D8->ticks = 0;
            data_030027D8->fade_step = 0;
            data_0201C3CC = 20;
            *state = 11;
        }
        break;
    case 9:
        if (g_state_02000000.save_slot != 0
            && func_0813B0D4(g_state_02000000.save_slot - 1,
                             &g_state_02000000)) {
            data_030027D8->has_slot2 = 0;
            func_0813BC7C(2);
            if (data_0201C3CE)
                func_080C9574(0x4B, 1);
            func_081416DC(0x31);
            func_08141570(1, 0x72);
            data_03000E08 = data_030027D8->menu.cursor;
            *state = 18;
        } else {
            func_081416DC(0x31);
            func_08141540(0x6A);
            data_03000E08 = 0xFF;
            *state = 19;
        }
        break;
    case 17: {
        /* A 16-bit local: the s8 answer is widened by lsls #24, asrs #8,
         * lsrs #16 at 0x08139A0C-0x08139A10. */
        u16 choice;

        if (!func_08011860())
            break;
        choice = func_08013380();
        if (choice == 0) {
            func_08013364();
            data_03000ED0.enabled = 0;
            func_0813BB04(data_030027D8->menu.cursor, &g_state_02000000);
            g_state_02000000.save_slot = data_030027D8->menu.cursor + 1;
            func_08138354(data_085668B0[62]);
            func_0808A604(3, 2);
            data_0201C3D0 = data_020084D4;
            func_08141748(3);
            data_030027D8->ticks = 30;
            data_0201C3CC = 9;
            *state = 14;
        } else {
            func_08013364();
            data_0201C3CC = 8;
            *state = 13;
        }
        break;
    }
    case 10:
        data_030027D8->ticks = (data_030027D8->ticks + 1) % 240;
        if (--data_030027D8->fade_step == 0)
            *state = data_0201C3CC;
        func_0813839C(8, data_030027D8->fade_step);
        break;
    case 11:
        data_030027D8->ticks = (data_030027D8->ticks + 1) % 240;
        if (++data_030027D8->fade_step == 8)
            *state = data_0201C3CC;
        func_0813839C(8, data_030027D8->fade_step);
        break;
    case 12:
        if (data_030009E0[data_0201C3CD].state == 0)
            *state = data_0201C3CC;
        break;
    case 13:
        if (func_08011860())
            *state = data_0201C3CC;
        break;
    case 14:
        if (!func_08011860())
            break;
        *state = 15;
        /* fallthrough */
    case 15:
        if (data_030027D8->ticks)
            data_030027D8->ticks--;
        else
            *state = data_0201C3CC;
        break;
    case 16:
        if (data_030027D8->ticks) {
            data_030027D8->ticks--;
        } else {
            func_08138354(data_085668B0[60]);
            *state = data_0201C3CC;
        }
        break;
    case 18:
        data_03000ED0.enabled = 1;
        func_08138354(data_085668B0[64]);
        func_0808A604(3, 2);
        *state = 3;
        break;
    case 19:
        data_03000ED0.enabled = 1;
        func_08138354(data_085668B0[66]);
        func_0808A604(3, 2);
        data_030027D8->ticks = 180;
        data_0201C3CC = 3;
        *state = 15;
        break;
    case 20:
        func_08137C48();
        *state = 22;
        break;
    case 22:
        func_08006B8C(&data_03000880, 0);
        func_08003888();
        func_080039E8(1, 8);
        *state = 0xFF;
        break;
    case 0xFF:
        /* The finished state.  Its label stretches the case range to 0..0xFF,
         * which is why the ROM dispatches with a compare tree rooted at 12
         * (0x08138F08-0x08139012) instead of a jump table. */
        break;
    }
    func_0813B6A4();
}
