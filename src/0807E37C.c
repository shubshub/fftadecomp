#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit0807E37C;

typedef struct {
    u32 unknown_00[3];
    u16 field_0c;
    u16 unknown_0e;
} Block0807E37C;

typedef struct {
    u8 unknown_000[0x105];
    u8 option;
    u8 selection;
    u8 unknown_107[0x3F9];
} Menu0807E37C;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u16 step;
    u8 unknown_0028[0x402];
    u8 saved_submode;
    u8 unknown_042b[0xb];
    s16 marker_x, marker_y;
    u8 mode;
    u8 saved_mode;
    u8 unknown_043c[4];
    void *field_440;
    u8 unknown_0444[9];
    u8 field_44d;
    u8 unknown_044e;
    u8 saved_phase;
    u8 field_450;
    u8 unknown_0451;
    u8 changed;
    u8 field_453;
    const u8 *field_454;
    s16 offset_x, offset_y;
    Menu0807E37C menu;
    u8 unknown_095c[0x2a];
    u8 selected_entry;
    u8 unknown_0987[5];
    Block0807E37C block_98c;
    u8 unknown_099c[0x24c];
    s16 field_be8, field_bea;
    u8 unknown_0bec[4];
    s16 target_x, target_y;
    u8 unknown_0bf4;
    u8 ready;
    u8 unknown_0bf6[6];
    Block0807E37C block_bfc;
    u16 counter;
    u8 unknown_0c0e[0xf];
    u8 field_c1d;
    u8 unknown_0c1e[0x10e6];
    u8 submode;
    u8 unknown_1d05[4];
    u8 field_1d09;
    u8 unknown_1d0a[2];
    Unit0807E37C *unit;
} State0807E37C;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display0807E37C;

typedef struct {
    u8 unknown_00[0x14];
    u16 enabled;
    u8 unknown_16[6];
} EntryFlags0807E37C;

typedef struct {
    u8 unknown_00[12];
    u8 width;
    u8 height;
    u8 unknown_0e[6];
    u16 *map;
} Layer0807E37C;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input0807E37C;

typedef struct {
    u8 state;
    u8 unknown_01[4];
    u8 unknown_05;
    u8 unknown_06[0x2f];
    s8 y;
    u8 unknown_36[0x16];
} Window0807E37C;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry0807E37C;

extern State0807E37C *data_03002818;
extern Table data_03002730;
extern Display0807E37C data_03000E30;
extern Input0807E37C data_03000000;
extern Window0807E37C data_030009E0[];
extern Unit0807E37C *data_030027F4;
extern Layer0807E37C data_030008B0;
extern Layer0807E37C data_03000990;
extern Layer0807E37C data_03000E80;
extern u8 data_02003CB0[];
extern u8 data_06014300[];
extern u8 data_0894EAF4[];
extern u8 data_0894EB80[];
extern u16 data_03003860[];
extern const MenuEntry0807E37C data_08393B7C[];
/* 0x0200F23C..0x0200F241 are named by this function's literal pools only. */
extern u8 data_0200F23C;
extern u8 data_0200F23D;
extern u8 data_0200F23E;
extern u8 data_0200F23F;
extern u8 data_0200F240;
extern u8 data_0200F241;

extern void func_08079690(u32 mode);
extern void func_080753C8(void);
extern void func_08075620(s32 mode, Unit0807E37C *unit, s32 redraw,
                          s32 numbered);
extern void func_0804C524(u8 *, u16, u32, u8, u8, u32, u8, u32, u8 *, u16,
                          u8);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern void func_0804C7A0(void *entries, u16 index);
extern u8 func_080CB7C0(Unit0807E37C *unit, u8 selector);
extern const u8 *func_080CB808(Unit0807E37C *unit);
extern u8 *func_080CB868(u8 *buffer, Unit0807E37C *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit0807E37C *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_080C8240(void *data);
extern void func_08019A8C(void *context, u16 value, void *first, void *second);
/* Halfword results: func_08011860 and func_08088FEC (src/08011860.c and
 * src/08088FEC.c return u32) are tested through lsls #16 (0x0807E7A4,
 * 0x0807E948), as in src/080775A8.c.  For func_08089D64 the ROM rules out
 * only the u8 of src/08089D64.c, which narrows to a byte after the call
 * (0x0807E730); the lsls #16 at 0x0807E734 and 0x0807E840 narrow the u16
 * locals, and a u32 result compiles alike. */
extern u16 func_08011860(void);
extern int func_0808A604(int index, u16 mode);
extern void func_080748AC(Unit0807E37C *unit);
extern void func_08141540(u16 song_id);
extern void func_08087554(u8 period, u8 phase);
extern u16 func_08089D64(Menu0807E37C *menu);
extern void func_08089CAC(Menu0807E37C *menu);
extern u16 func_08088FEC(Menu0807E37C *menu, u16 input);
extern void func_08088DF0(Menu0807E37C *menu, const MenuEntry0807E37C *entries,
                          s32 count, s32 graphic, u32 palette, u32 visible,
                          u32 enabled, u32 mode, u32 variant, u32 style,
                          u32 option);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B890(int index, u16 *destination, u16 count, u16 flags);
extern u32 func_080751AC(Unit0807E37C *unit);
extern void func_08076420(s32 selected);
extern void *func_08021AD0(void *process);
extern void func_080775A8(void *unused, u8 *state);
extern void func_08078818(void *unused, u8 *state);
extern void func_08085AA8(void *unused, u8 *state);

/* Complete [0x0807E37C, 0x0807F168): 3564 bytes including literal pools,
 * 1329 reachable instructions.  The three-entry counterpart of
 * func_08076560 (src/08076560.c) for the unit at data_030027F4, called as
 * (unused, &state); *state selects a case by a binary tree of compares.  Its
 * submenus are the dispatchers 080775A8, 08078818 and 08085AA8, started in
 * cases 13, 15 and 17. */
void func_0807E37C(void *unused, u8 *state)
{
    u16 value;

    switch (*state) {
    case 0: {
        int x, y;
        u8 *buffer = data_02003CB0;
        const u8 *resource;

        data_03002818->unit = data_030027F4;
        data_03002818->block_bfc = data_03002818->block_98c;
        data_03002818->field_44d = 1;
        func_08079690(1);
        data_03002818->field_1d09 = data_03002818->unit->flags & 0x1c;
        /* The ROM copies the block a second time here (ldm/stm at
         * 0x0807E486 and again at 0x0807E4BC). */
        data_03002818->block_bfc = data_03002818->block_98c;
        data_03002818->block_bfc.field_0c = 0;
        data_0200F23F = data_0200F240 = 0;
        data_03002818->counter = data_03002818->ready = 0;
        data_03002818->menu.option = 0;
        data_03002818->field_c1d = 0;
        data_0200F241 = 0;
        func_080753C8();
        func_08075620(1, data_03002818->unit, 0, 1);
        x = data_03002818->target_x / 8;
        y = data_03002818->target_y / 8;
        data_03002818->marker_x = x;
        data_03002818->marker_y = y;
        func_0804C524(data_03000E30.entries, 25, 0, 0, 0, 0, 3,
                      (u32)data_0894EAF4, data_0894EB80, 0x1b0, 0);
        ((EntryFlags0807E37C *)data_03000E30.entries)[25].enabled = 1;
        data_03002818->marker_x = 120;
        data_03002818->marker_y = -8;
        data_03002818->offset_x = -64;
        data_03002818->offset_y = 56;
        data_03002818->changed = 3;
        resource = func_080CB808(data_03002818->unit);
        func_080CB868(buffer, data_03002818->unit);
        func_0814186C(buffer, data_06014300, ((u32)resource << 10) >> 11);
        if (func_080C8240(data_03002818->unit))
            func_080CB8D4((u8 *)data_03002818 + 0x2E8,
                          func_080CB7C0(data_03002818->unit, 0));
        else
            func_080CB8D4((u8 *)data_03002818 + 0x2E8,
                          func_080CB7C0(data_03002818->unit, 1));
        data_03002818->field_454 = func_080CB928(data_03002818->unit);
        data_03002818->changed = 3;
        data_03002818->submode = 0;
        *state = 35;
        break;
    }
    case 35:
        if (data_03002818->counter++ > 10) {
            func_0808A604(3, 2);
            data_03002730.flags[5] = 3;
            func_080748AC(data_03002818->unit);
            data_03002818->step = 8;
            data_0200F23E = 0;
            data_0200F23C = 3;
            *state = 24;
        }
        break;
    case 26:
        value = func_08089D64(&data_03002818->menu) + 0x2c;
        data_03002818->saved_submode = data_03002818->submode;
        data_03002818->submode = 0;
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->counter = 0;
        data_03002818->mode = 3;
        func_08019A8C(data_02003CB0, value, &data_03000990, &data_03000E80);
        *state = 27;
        break;
    case 27:
        if (func_08011860()) {
            data_03002818->timer = 15;
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->submode = data_03002818->saved_submode;
            *state = 28;
        }
        break;
    case 28:
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer != 0)
            data_03002818->timer--;
        else
            *state = 2;
        break;
    case 2:
        if (data_03000000.pressed == 4) {
            *state = 26;
        } else if (data_03000000.pressed & 1) {
            u16 choice = func_08089D64(&data_03002818->menu);

            func_08141540(0x64);
            if (choice == 0)
                data_0200F23C = 13;
            else if (choice == 1)
                data_0200F23C = 15;
            else if (data_0200F241 == 0) {
                func_08141540(0x6a);
                break;
            } else
                data_0200F23C = 17;
            func_08089CAC(&data_03002818->menu);
            data_0200F23D = 4;
            /* Indexed by the window just stored, as in src/08076560.c: the
             * ROM adds 4 * 0x4C to the table and stores at [r0, #5]
             * (0x0807E8A0-0x0807E8AA, and 0x0807E8F8-0x0807E902 below). */
            data_030009E0[data_0200F23D].unknown_05 = 3;
            func_0808A604(4, 12);
            *state = 34;
        } else if (data_03000000.pressed & 2) {
            data_03002818->submode = 0;
            func_08089CAC(&data_03002818->menu);
            func_08141540(0x69);
            data_0200F23D = 4;
            data_030009E0[data_0200F23D].unknown_05 = 3;
            func_0808A604(4, 12);
            data_0200F23E = 5;
            data_0200F23C = 25;
            *state = 34;
            break;
        }
        if (func_08088FEC(&data_03002818->menu, data_03000000.repeated)) {
            func_0808B890(4, func_0808B8E4(4, 1, 1,
                                           data_03002818->menu.selection * 2 + 2),
                          10, 0xC000);
            func_0808B890(4, func_0808B8E4(4, 1, 1,
                                           data_03002818->menu.option * 2 + 2),
                          10, 0xB000);
            func_0808A604(4, 2);
        }
        break;
    case 3:
        func_08141540(0x65);
        data_0200F241 = func_080751AC(data_03002818->unit);
        func_08088DF0(&data_03002818->menu, data_08393B7C, 3, 0x1C,
                      0, 1, 0, 1, 0, 0, data_03002818->menu.option);
        func_08088FEC(&data_03002818->menu, 0);
        func_0808B890(4, func_0808B8E4(4, 1, 1,
                                       data_03002818->menu.selection * 2 + 2),
                      10, 0xC000);
        func_0808B890(4, func_0808B8E4(4, 1, 1,
                                       data_03002818->menu.option * 2 + 2),
                      10, 0xB000);
        func_0808A604(4, 2);
        data_0200F23D = 4;
        func_0808A604(4, 2);
        data_0200F23C = 2;
        *state = 34;
        break;
    case 4:
        break;
    case 5:
        /* The fills of src/08076560.c's case 5, in the text of
         * src/0807B858.c: the SDK's vu16 temporary, spelled through a
         * pointer until fftadecomp-kit#164.  The address comes before the
         * zero (add r0, sp, #0x1C; movs r5, #0 at 0x0807EA8C-0x0807EA8E). */
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 6, 9), 0x01000001);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 6, 10), 0x01000001);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 11, 14), 0x01000003);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 11, 15), 0x01000003);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 11, 17), 0x01000003);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, func_0808B8E4(0, 1, 11, 18), 0x01000003);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_030008B0.map,
                          (data_030008B0.width * data_030008B0.height) |
                              0x01000000);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_03000990.map,
                          (data_03000990.width * data_03000990.height) |
                              0x01000000);
        }
        data_03002818->counter = 0;
        data_03002818->field_453 = 8;
        data_0200F23C = 0xfe;
        *state = 22;
        break;
    case 13:
        func_08006ADC(&data_03002730, 2, (u32)func_080775A8);
        *state = 14;
        break;
    case 14:
        if (data_03002730.flags[2] == 0xff) {
            data_03002818->menu.option = 0;
            *state = 3;
        }
        break;
    case 15:
        func_08006ADC(&data_03002730, 2, (u32)func_08078818);
        *state = 16;
        break;
    case 16:
        if (data_03002730.flags[2] == 0xff) {
            data_03002818->menu.option = 1;
            *state = 3;
        }
        break;
    case 17:
        func_08006ADC(&data_03002730, 2, (u32)func_08085AA8);
        *state = 18;
        break;
    case 18:
        if (data_03002730.flags[2] == 0xff) {
            data_03002818->menu.option = 2;
            *state = 3;
        }
        break;
    case 21:
        if (data_03002818->counter++ < 15) {
            if (data_030009E0[2].y < 0) {
                data_030009E0[2].y++;
                func_0808A604(2, 2);
            }
        } else {
            data_03002818->field_1d09 |= 1;
            func_08076420(data_03002818->selected_entry);
            func_0808A604(3, 2);
            func_0808A604(2, 2);
            *state = data_0200F23C;
        }
        break;
    case 22:
        if (data_03002818->counter++ < 10) {
            if (data_030009E0[2].y > -9) {
                data_030009E0[2].y--;
                func_0808A604(2, 2);
            }
            data_0200F23F = data_03002818->field_be8 / 8;
            data_0200F240 = data_03002818->field_bea / 8;
            data_03002818->marker_x = data_0200F23F;
            data_03002818->marker_y = data_0200F240;
            func_0804C788(data_03000E30.entries, 25, data_0200F23F,
                          data_0200F240);
            if (data_03002818->field_450 == 8) {
                data_03002818->changed = 3;
                data_03002818->offset_x -= 8;
                data_03002818->offset_y = 56;
            }
            data_03002818->field_bea -= 64;
        } else {
            func_0804C7A0(data_03000E30.entries, 26);
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_03000E80.map,
                              (data_03000E80.width * data_03000E80.height) |
                                  0x01000000);
            }
            *state = data_0200F23C;
        }
        break;
    case 23:
        if (data_03002818->counter++ < 10) {
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8 - data_03002818->counter * 8;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 25, x, y);
            data_03002818->changed = 3;
            data_03002818->offset_x -= 8;
            data_03002818->offset_y = 56;
        } else {
            u8 *buffer = data_02003CB0;
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8;
            const u8 *resource;
            void *object;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 25, x, y);
            func_080748AC(data_03002818->unit);
            data_03002818->offset_x = 0;
            data_03002818->offset_y = 56;
            func_0804C788(data_03000E30.entries, 25, x, y);
            resource = func_080CB808(data_03002818->unit);
            func_080CB868(buffer, data_03002818->unit);
            func_0814186C(buffer, data_06014300, ((u32)resource << 10) >> 11);
            object = (u8 *)data_03002818 + 0x2E8;
            func_080CB8D4(object, func_080CB7C0(data_03002818->unit, 1));
            data_03002818->field_454 = func_080CB928(data_03002818->unit);
            data_03002818->changed = 3;
            func_0814186C((u8 *)data_03002818 + 0x28,
                          data_03003860, 0x04000080);
            func_0814186C((u8 *)data_03002818 + 0x228,
                          data_03003860 + 0x100, 0x04000080);
            *state = 1;
        }
        break;
    case 34:
        if (data_030009E0[data_0200F23D].state == 0) {
            *state = data_0200F23C;
            data_0200F23C = data_0200F23E;
        }
        break;
    case 24:
        data_03002818->marker_y += 8;
        func_0804C788(data_03000E30.entries, 25, data_03002818->marker_x,
                      data_03002818->marker_y);
        data_03002818->offset_x += 8;
        data_030009E0[2].y++;
        func_0808A604(2, 3);
        data_03002818->timer = (data_03002818->timer + 1) % 240;
        if (data_03002818->step == 4)
            func_08141540(0x8e);
        if (--data_03002818->step == 0) {
            *state = data_0200F23C;
            data_0200F23C = data_0200F23E;
        }
        func_08087554(8, data_03002818->step);
        break;
    case 25:
        data_03002818->marker_y -= 8;
        data_03002818->offset_x -= 8;
        func_0804C788(data_03000E30.entries, 25, data_03002818->marker_x,
                      data_03002818->marker_y);
        data_030009E0[2].y--;
        func_0808A604(2, 3);
        data_03002818->timer = (data_03002818->timer + 1) % 240;
        if (++data_03002818->step == 8) {
            *state = data_0200F23C;
            data_0200F23C = data_0200F23E;
        }
        func_08087554(8, data_03002818->step);
        break;
    case 0xfe:
        if (data_03002818->counter++ > 10) {
            func_08021AD0(data_03002818->field_440);
            *state = 0xff;
        }
        break;
    case 0xff:
        data_03002818->saved_phase = 0xfe;
        break;
    }
}
