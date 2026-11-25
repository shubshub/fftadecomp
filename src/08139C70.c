#include "ffta.h"

/* Complete target: [0x08139C70, 0x0813ADF0), 4480 bytes, 1202 instructions.
 * The load scene, the counterpart of the save scene func_08138EFC on the same
 * state object: it reads the headers of save slots 0 and 1 and of the
 * suspended game (slot 2), offers to resume the suspended game or to load a
 * slot, and copies the chosen data into g_state_02000000.  A state machine on
 * *state, dispatched through the 256-entry jump table at 0x08139C94 (cases
 * 0-32 and the finished state 0xFF), followed by func_0813B6A4 every frame. */

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08139C70;

typedef struct {
    u32 unknown_00;
    void *entries;
} SharedResource08139C70;

typedef struct {
    u8 state;
    u8 unknown_01[4];
    u8 step;
    u8 unknown_06[0x46];
} Window08139C70;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry08139C70;

/* The play-time timer that func_0813BBB8 advances (enabled at +5). */
typedef struct {
    u8 unknown_00[5];
    u8 enabled;
} Timer08139C70;

typedef struct {
    u8 unknown_000[0x105];
    u8 cursor;
    u8 unknown_106[0x111 - 0x106];
    u8 unknown_111;
} Menu08139C70;

/* The scene state at data_030027D8, laid out and named as func_08138EFC's
 * Context: one summary and one presence bit per slot. */
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
    Menu08139C70 menu;
} Context08139C70;

typedef struct {
    u8 unknown_0000[0x72];
    u16 save_slot;
    u8 unknown_0074[0x2FC0 - 0x74];
    u8 unknown_2FC0_0 : 1;
    u8 speed : 2;           /* func_08008954's options.speed: the key repeat */
} GameState08139C70;

extern Context08139C70 *data_030027D8;
extern Input08139C70 data_03000000;
extern SharedResource08139C70 data_03000E30;
extern Table data_03000880;
extern Window08139C70 data_030009E0[];
extern const struct FlashType *data_0200F370;
extern u8 data_030009CC;
extern u8 data_02003CB0[];
extern u8 data_0201C3D2;
extern u8 data_0201C3D3;
extern u8 data_0201C3D4;
extern u8 data_03000E08;
extern Timer08139C70 data_03000ED0;
extern u8 data_0300284C;
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_0600C120[];
extern u8 data_0600CD20[];
extern GameState08139C70 g_state_02000000;
extern const u8 *const data_085668B0[];
extern const MenuEntry08139C70 data_083A8E64[];
extern const MenuEntry08139C70 data_083A8E74[];
extern const MenuEntry08139C70 data_083A8E94[];

extern void func_08003888(void);
extern void func_080038C8(u16 value);
extern void func_080039E8(u16 value, u8 mode);
extern void func_08006B8C(Table *t, u8 index);
extern void func_08009920(u8 mode);
extern void func_08009AFC(u16 event);
extern u16 func_08011860(void);
extern void func_0801174C(void *context, u8 kind, u16 selection, void *first,
                          void *second, u32 field5, s32 field6, u32 width,
                          u32 height, u32 tile);
extern void func_08013364(void);
extern s8 func_08013380(void);
extern void func_0804C834(void *entries, s32 count);
extern void func_08088DF0(Menu08139C70 *object,
                          const MenuEntry08139C70 *entries, s32 count,
                          s32 graphic, u32 palette, u32 visible, u32 enabled,
                          u32 mode, u32 variant, u32 style, u32 option);
extern u16 func_08088FEC(Menu08139C70 *object, u16 input);
extern int func_0808A604(int index, u16 mode);
extern void func_0808B288(int unused, u8 *initialized);
extern u32 func_08137B50(void);
extern void func_08137CC4(void);
extern void func_08137EC4(void);
extern int func_08137C48(void);
extern void func_081380A8(void);
extern void func_081380B8(void);
extern void func_08138284(void);
extern void func_08138354(const u8 *text);
extern void func_0813839C(u8 steps, u8 phase);
extern void func_081384B0(u32 enabled);
extern void func_081385CC(u32 index, u16 base);
extern void func_081386BC(u32 index, void *record, u8 *tiles, u32 present,
                          u16 mode, u16 empty_mode);
extern void func_08138A3C(void);
extern void func_08138B4C(void *entry);
extern void func_08138DA4(Menu08139C70 *object, u32 mode);
extern void func_08138E80(Menu08139C70 *menu);
extern u32 func_0813B480(u8 mode, void *data);
extern void func_0813B6A4(void);
extern void func_0813BC7C(u8 group);
extern void func_08141540(u16 song_id);
extern void func_08141570(s32 player_id, u16 song_id);
extern void func_081416DC(u16 value);
extern void func_08141748(u16 interval);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08139C70(u8 index, u8 *state)
{
    switch (*state) {
    case 0:
    case 1:
        func_08137B50();
        func_08137CC4();
        func_08137EC4();
        func_081380A8();
        func_0804C834(data_03000E30.entries, 4);
        func_08006B8C(&data_03000880, 0);
        func_08006B8C(&data_03000880, 1);
        func_08006ADC(&data_03000880, 0, (u32)func_0808B288);
        func_081416DC(0x31);
        data_030027D8->has_slot0 = 0;
        data_030027D8->has_slot1 = 0;
        data_030027D8->has_slot2 = 0;
        if (data_0200F370) {
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
                /* Slot 1 also falls back to 0 (movs r5, #0 at 0x0813A168),
                 * as in the save scene's case 7; its case 3 picks 1.  The
                 * test never holds: data_030009CC is only ever stored as 0
                 * or 1 (see func_08138EFC). */
                if (slot == 2)
                    slot = 0;
            }
            if (func_0813B480(2, buffer)) {
                func_0814186C(buffer, data_030027D8->summaries[2], 0x40);
                data_030027D8->has_slot2 = 1;
            }
            data_030009CC = slot;
            /* The top menu opens on row 0 (the suspended game) when there
             * is one, else on row 1 (the save slots).  The test of slots 0
             * and 1 has identical arms, and the ROM keeps its instructions:
             * the flags byte loaded at 0x0813A1A0 for the slot 2 test is
             * masked again (movs r0, #3; ands r0, r1 at 0x0813A1E0).  The
             * compiler merged the arms after register allocation into the
             * store at 0x0813A1E8, which the slot 2 arm shares, and dropped
             * the compare and branch but not the mask.  Without the test the
             * function is 4,476 bytes, exactly those two instructions short. */
            if (data_030027D8->has_slot2)
                data_0201C3D4 = 0;
            else if (data_030027D8->has_slot0 || data_030027D8->has_slot1)
                data_0201C3D4 = 1;
            else
                data_0201C3D4 = 1;
            *state = 3;
        } else {
            func_081380B8();
            func_08138284();
            func_08141540(0x6A);
            func_08138354(data_085668B0[0x44]);
            func_0808A604(3, 2);
            func_0808A604(2, 2);
            data_030027D8->ticks = 0;
            data_030027D8->fade_step = 8;
            data_0201C3D2 = 0x1D;
            *state = 0x10;
        }
        break;
    case 29:
        if (!(data_03000000.pressed & 1))
            break;
        func_08141748(3);
        data_03000E08 = 0xFF;
        data_030027D8->ticks = 0;
        data_030027D8->fade_step = 0;
        data_0201C3D2 = 0x1C;
        *state = 0x12;
        break;
    case 2:
        func_081380B8();
        func_0808A604(2, 2);
        func_08088DF0(&data_030027D8->menu, data_083A8E64, 2, 0,
                      0, 0, 0, 1, 0, 1, data_0201C3D4);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138E80(&data_030027D8->menu);
        data_0201C3D2 = 4;
        *state = 0x13;
        break;
    case 3:
        func_081380B8();
        func_08088DF0(&data_030027D8->menu, data_083A8E64, 2, 0,
                      0, 0, 0, 1, 0, 1, data_0201C3D4);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138E80(&data_030027D8->menu);
        data_030027D8->ticks = 0;
        data_030027D8->fade_step = 8;
        data_0201C3D2 = 4;
        *state = 0x11;
        break;
    case 4:
        if (func_08088FEC(&data_030027D8->menu, data_03000000.repeated)) {
            func_08138E80(&data_030027D8->menu);
            data_0201C3D3 = 2;
            func_0808A604(2, 2);
            data_0201C3D2 = 4;
            *state = 0x13;
            break;
        }
        if (data_03000000.pressed == 1) {
            if (data_030027D8->menu.cursor == 0) {
                data_0201C3D4 = data_030027D8->menu.cursor;
                if (!data_030027D8->has_slot2) {
                    func_08141540(0x6A);
                    break;
                }
                data_030027D8->menu.unknown_111 = 0xF0;
                func_08141540(0x64);
                data_0201C3D3 = 2;
                data_030009E0[2].step = 2;
                func_0808A604(2, 12);
                data_0201C3D2 = 7;
                *state = 0x13;
                break;
            } else if (data_030027D8->menu.cursor == 1) {
                data_0201C3D4 = data_030027D8->menu.cursor;
                if (!data_030027D8->has_slot0 && !data_030027D8->has_slot1) {
                    func_08141540(0x6A);
                    break;
                }
                data_030027D8->menu.unknown_111 = 0xF0;
                func_08141540(0x64);
                data_0201C3D3 = 2;
                data_030009E0[2].step = 2;
                func_0808A604(2, 12);
                data_0201C3D2 = 5;
                *state = 0x13;
                break;
            }
        }
        if (data_03000000.pressed != 2)
            break;
        func_08141748(3);
        data_030027D8->menu.unknown_111 = 0xF0;
        func_08141540(0x68);
        data_03000E08 = 0xFF;
        data_030027D8->ticks = 0;
        data_030027D8->fade_step = 0;
        data_0201C3D2 = 0x1C;
        *state = 0x12;
        break;
    case 5:
        func_08138284();
        func_08138354(data_085668B0[0x3D]);
        func_0808A604(3, 2);
        *state = 6;
        break;
    case 6:
        func_081384B0(1);
        func_081385CC(4, 0x209);
        func_081386BC(4, data_030027D8->summaries[0], data_0600C120,
                      data_030027D8->has_slot0, 0, 1);
        func_08138A3C();
        func_081385CC(5, 0x269);
        func_081386BC(5, data_030027D8->summaries[1], data_0600CD20,
                      data_030027D8->has_slot1, 0, 1);
        /* The awaited window is indexed through data_0201C3D3: the ROM
         * forms &data_030009E0[4] (movs r3, #0x98; lsls r3, #1 at
         * 0x0813A58E) and stores at #5, while the literal [5] below folds
         * to 0x181. */
        data_0201C3D3 = 4;
        data_030009E0[data_0201C3D3].step = 1;
        func_0808A604(4, 11);
        data_030009E0[5].step = 1;
        func_0808A604(5, 11);
        func_08088DF0(&data_030027D8->menu, data_083A8E74, 2, 0,
                      0, 0, 0, 1, 0, 1, data_030009CC);
        func_08088FEC(&data_030027D8->menu, 0);
        func_08138DA4(&data_030027D8->menu, 0);
        func_08141540(0x65);
        data_0201C3D2 = 0xB;
        *state = 0x13;
        break;
    case 7:
        func_08138284();
        func_08138354(data_085668B0[0x46]);
        func_0808A604(3, 2);
        *state = 8;
        break;
    case 8:
        func_08088DF0(&data_030027D8->menu, data_083A8E94, 1, 0,
                      0, 0, 0, 1, 0, 1, 0);
        func_081384B0(0);
        func_081385CC(4, 0x209);
        func_081386BC(4, data_030027D8->summaries[2], data_0600C120,
                      data_030027D8->has_slot2, 0, 1);
        func_08138B4C(data_030027D8->summaries[2]);
        data_0201C3D3 = 4;
        data_030009E0[data_0201C3D3].step = 1;
        func_0808A604(4, 11);
        data_030009E0[7].step = 1;
        func_0808A604(7, 11);
        func_08141540(0x65);
        func_08138DA4(&data_030027D8->menu, 0);
        data_0201C3D2 = 0xD;
        *state = 0x13;
        break;
    case 13:
        if (func_08088FEC(&data_030027D8->menu, data_03000000.repeated)) {
            func_08138DA4(&data_030027D8->menu, 0);
            func_0808A604(4, 2);
            func_0808A604(5, 2);
        }
        if (data_03000000.pressed & 1) {
            func_0801174C(data_02003CB0, 1, 0x26, data_03000990, data_03000E80,
                          3, 2, 0x17, 4, 0x3A0);
            *state = 0xE;
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x68);
            data_030027D8->menu.unknown_111 = 0xF0;
            data_03000E08 = 0xFF;
            data_030027D8->ticks = 0;
            data_030027D8->fade_step = 0;
            data_0201C3D3 = 4;
            data_030009E0[data_0201C3D3].step = 1;
            func_0808A604(4, 12);
            data_030009E0[7].step = 1;
            func_0808A604(7, 12);
            data_030009E0[3].step = 1;
            func_0808A604(3, 12);
            data_0201C3D2 = 2;
            *state = 0x13;
        }
        break;
    case 14: {
        /* A 16-bit local, as in the save scene's case 17: the s8 answer is
         * widened by lsls #24; asrs #8; lsrs #16 at 0x0813A844. */
        u16 choice;

        if (!func_08011860())
            break;
        choice = func_08013380();
        if (choice == 0) {
            func_08013364();
            data_03000ED0.enabled = 0;
            func_08138354(data_085668B0[0x3F]);
            func_0808A604(3, 2);
            func_08141748(3);
            data_030027D8->ticks = 0x1E;
            data_0201C3D2 = 0xF;
            *state = 0x16;
        } else {
            func_08013364();
            data_0201C3D2 = 0xD;
            *state = 0xD;
        }
        break;
    }
    case 11:
        if (func_08088FEC(&data_030027D8->menu, data_03000000.repeated)) {
            func_08138DA4(&data_030027D8->menu, 0);
            func_0808A604(4, 2);
            func_0808A604(5, 2);
            break;
        }
        if (data_03000000.pressed == 1) {
            if (data_030027D8->menu.cursor == 0 && !data_030027D8->has_slot0) {
                func_08141540(0x6A);
                break;
            }
            if (data_030027D8->menu.cursor == 1 && !data_030027D8->has_slot1) {
                func_08141540(0x6A);
                break;
            }
            func_08141540(0x64);
            data_03000ED0.enabled = 0;
            func_08138354(data_085668B0[0x3F]);
            func_0808A604(3, 2);
            func_08141748(3);
            data_030027D8->ticks = 0x1E;
            data_0201C3D2 = 0xC;
            *state = 0x16;
        } else if (data_03000000.pressed == 2) {
            func_08141540(0x68);
            data_030027D8->menu.unknown_111 = 0xF0;
            data_03000E08 = 0xFF;
            data_030027D8->ticks = 0;
            data_030027D8->fade_step = 0;
            data_0201C3D3 = 4;
            data_030009E0[data_0201C3D3].step = 1;
            func_0808A604(4, 12);
            data_030009E0[5].step = 1;
            func_0808A604(5, 12);
            data_030009E0[3].step = 1;
            func_0808A604(3, 12);
            data_0201C3D2 = 2;
            *state = 0x13;
        }
        break;
    case 12: {
        u8 *buffer = data_02003CB0;

        if (!func_0813B480(data_030027D8->menu.cursor, buffer)) {
            func_08141540(0x6A);
            *state = 0x19;
            break;
        }
        func_0814186C(buffer, &g_state_02000000, 0x1E54);
        func_08009920(g_state_02000000.speed);
        if (g_state_02000000.save_slot == 0)
            g_state_02000000.save_slot = data_030027D8->menu.cursor + 1;
        func_08141570(1, 0x72);
        func_08138354(data_085668B0[0x41]);
        func_0808A604(3, 2);
        data_030027D8->ticks = 0x3C;
        data_0201C3D2 = 0x1F;
        *state = 0x16;
        break;
    }
    case 15: {
        u8 *buffer = data_02003CB0;

        if (!func_0813B480(2, buffer)) {
            func_08141540(0x6A);
            *state = 0x1A;
            break;
        }
        func_0814186C(buffer, &g_state_02000000, 0x1E54);
        func_08009920(g_state_02000000.speed);
        data_030027D8->has_slot2 = 0;
        func_0813BC7C(2);
        func_08141570(1, 0x72);
        func_08138354(data_085668B0[0x41]);
        func_0808A604(3, 2);
        data_030027D8->ticks = 0x3C;
        data_0201C3D2 = 0x1E;
        *state = 0x16;
        break;
    }
    case 17:
        /* Cases 17 and 16 share their text; the ROM holds both copies up
         * to the common tail (jump table entries 17 and 16: 0x0813AB5C and
         * 0x0813ABA4). */
        data_030027D8->ticks = (data_030027D8->ticks + 1) % 240;
        if (data_030027D8->fade_step == 4)
            func_0808A604(2, 2);
        if (--data_030027D8->fade_step == 0)
            *state = data_0201C3D2;
        func_0813839C(8, data_030027D8->fade_step);
        break;
    case 16:
        data_030027D8->ticks = (data_030027D8->ticks + 1) % 240;
        if (data_030027D8->fade_step == 4)
            func_0808A604(2, 2);
        if (--data_030027D8->fade_step == 0)
            *state = data_0201C3D2;
        func_0813839C(8, data_030027D8->fade_step);
        break;
    case 18:
        data_030027D8->ticks = (data_030027D8->ticks + 1) % 240;
        if (++data_030027D8->fade_step == 8)
            *state = data_0201C3D2;
        func_0813839C(8, data_030027D8->fade_step);
        break;
    case 19:
        if (data_030009E0[data_0201C3D3].state == 0)
            *state = data_0201C3D2;
        break;
    case 22:
        if (data_030027D8->ticks != 0)
            data_030027D8->ticks--;
        else
            *state = data_0201C3D2;
        break;
    case 24:
        func_08138354(data_085668B0[0x40]);
        func_0808A604(3, 2);
        *state = 0x1B;
        break;
    case 25:
        func_08138354(data_085668B0[0x43]);
        func_0808A604(3, 2);
        data_030027D8->ticks = 0xB4;
        data_0201C3D2 = 5;
        *state = 0x16;
        break;
    case 26:
        func_08138354(data_085668B0[0x43]);
        func_0808A604(3, 2);
        data_030027D8->ticks = 0xB4;
        data_0201C3D2 = 7;
        *state = 0x16;
        break;
    case 27:
        func_08137C48();
        *state = 0x1F;
        break;
    case 28:
        func_08137C48();
        if (data_0300284C != 0)
            *state = 0x1F;
        else
            *state = 0x20;
        break;
    case 31:
        func_08006B8C(&data_03000880, 0);
        if (data_0300284C != 0) {
            func_08003888();
            func_080039E8(1, 9);
        } else {
            func_08003888();
            func_080039E8(1, 1);
        }
        data_0300284C = 0;
        *state = 0xFF;
        break;
    case 32:
        func_08006B8C(&data_03000880, 0);
        data_0300284C = 2;
        func_08003888();
        func_080038C8(0xB);
        *state = 0xFF;
        break;
    case 30:
        func_08137C48();
        func_08006B8C(&data_03000880, 0);
        if (data_0300284C != 0) {
            func_08003888();
            func_080039E8(1, 10);
        } else {
            func_08009AFC(0xAC);
            func_080038C8(2);
        }
        data_0300284C = 0;
        *state = 0xFF;
        break;
    case 0xFF:
        /* The finished state: the table bound is cmp r0, #0xff at
         * 0x08139C7E and entry 0xFF goes straight to the call below. */
        break;
    }
    func_0813B6A4();
}
