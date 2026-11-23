#include "ffta.h"

/* Complete target [0x08076560, 0x080774B4): 3924 bytes including literal
 * pools, 1461 reachable instructions.  The unit menu's state machine, called
 * through a function pointer as (unused, &state); *state selects a case by a
 * binary tree of compares from 0x08076570.  Its four submenus are the
 * dispatchers 080775A8, 08078818, 08085AA8 and 080868D4, started in cases
 * 0xD, 0xF, 0x11 and 0x13. */

typedef struct {
    u8 unknown_00[4];
    u8 type;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07[0x21];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit08076560;

typedef struct {
    u8 unknown_0000[0x80];
    Unit08076560 units[24];
} Game08076560;

typedef struct {
    u8 unknown_000[0x105];
    u8 option;
    u8 selection;
    u8 unknown_107[0x3F9];
} Menu08076560;

typedef struct {
    u32 unknown_00[3];
    u16 field_0c;
    u16 unknown_0e;
} Block08076560;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u16 step;
    u8 unknown_0028[0x402];
    u8 saved_submode;
    u8 unknown_042b[0xB];
    s16 marker_x;
    s16 marker_y;
    u8 mode;
    u8 saved_mode;
    u8 unknown_043c[0x11];
    u8 field_44d;
    u8 unknown_044e[2];
    u8 field_450;
    u8 unknown_0451;
    u8 changed;
    u8 field_453;
    const u8 *field_454;
    s16 offset_x;
    s16 offset_y;
    Menu08076560 menu;
    u8 item_count;
    u8 unknown_095d[0x13];
    u8 control;
    u8 unknown_0971[0x15];
    u8 selected_entry;
    u8 selected_unit;
    u8 unknown_0988[4];
    Block08076560 block_98c;
    u8 unknown_099c[0x24C];
    s16 field_be8;
    s16 field_bea;
    u8 unknown_0bec[4];
    s16 target_x;
    s16 target_y;
    u8 unknown_0bf4;
    u8 ready;
    u8 unknown_0bf6[6];
    Block08076560 block_bfc;
    u16 counter;
    u8 unknown_0c0e[0xE];
    u8 entry_mode;
    u8 field_c1d;
    u8 unknown_0c1e[0x3E];
    u16 entries[6];
    u8 unknown_0c68[0x109C];
    u8 submode;
    u8 unknown_1d05[4];
    u8 field_1d09;
    u8 unknown_1d0a[2];
    Unit08076560 *unit;
} State08076560;

typedef struct {
    u8 state;
    u8 unknown_01[4];
    u8 unknown_05;
    u8 unknown_06[0x2F];
    s8 y;
    u8 unknown_36[0x16];
} Window08076560;

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[0x06];
    u16 *map;
} Layer08076560;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08076560;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display08076560;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry08076560;

extern State08076560 *data_03002818;
extern Game08076560 g_state_02000000;
extern Unit08076560 g_state_02000080[];
extern Window08076560 data_030009E0[];
extern Input08076560 data_03000000;
extern Display08076560 data_03000E30;
extern Table data_03002730;
extern Layer08076560 data_030008B0;
extern Layer08076560 data_03000990;
extern Layer08076560 data_03000E80;
extern const MenuEntry08076560 data_08393B5C[];
extern u8 data_02003CB0[];
extern u8 data_06014300[];
extern u16 data_03003860[];
/* 0x0200F228..0x0200F22B are named by this function's literal pools. */
extern u8 data_0200F228;
extern u8 data_0200F229;
extern u8 data_0200F22A;
extern u8 data_0200F22B;

extern void func_08141540(u16 song_id);
extern void func_08079690(u32 mode);
extern void func_080895D0(void);
extern void func_080753C8(void);
extern int func_0808A604(int index, u16 mode);
extern void func_08075620(s32 mode, Unit08076560 *unit, s32 redraw, s32 numbered);
extern void func_08076420(s32 selected);
extern void func_08074FA4(Unit08076560 *unit);
extern void func_080750D8(Unit08076560 *unit);
extern void func_08074DC4(void);
extern void func_08088DF0(Menu08076560 *menu, const MenuEntry08076560 *entries,
                          s32 count, s32 graphic, u32 palette, u32 visible,
                          u32 enabled, u32 mode, u32 variant, u32 style,
                          u32 option);
/* Halfword results here and below (src/08088FEC.c and src/08011860.c
 * return u32): each is narrowed with lsls #16 before its test (0x08076CBE,
 * 0x0807690C), as in src/080775A8.c. */
extern u16 func_08088FEC(Menu08076560 *menu, u16 input);
/* Not the u8 of src/08089D64.c, which narrows to a byte after the call;
 * the lsls/lsrs #16 at 0x08076A2E and after the + 0x2C at 0x08076894
 * narrow the u16 locals, and a u32 result compiles alike. */
extern u16 func_08089D64(Menu08076560 *menu);
extern void func_08089CAC(Menu08076560 *menu);
extern void func_08089CE4(Menu08076560 *menu);
extern void func_0808A1EC(Menu08076560 *menu);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B890(int index, u16 *destination, u16 count, u16 flags);
extern void func_08073254(void);
extern void func_08019A8C(void *context, u16 value, void *first, void *second);
extern u16 func_08011860(void);
extern u8 func_080C8194(const void *object, u8 category);
extern void func_08072C78(u16 keys, int fast);
/* An empty function (src/08080D34.c); both calls pass 0 in r0
 * (0x08077026, 0x08077458). */
extern void func_08080D34(u32 unused);
extern void func_08087554(u8 period, u8 phase);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern void func_0804C7A0(void *entries, u16 index);
extern void func_080748AC(Unit08076560 *unit);
extern u8 func_080CB7C0(Unit08076560 *unit, u8 selector);
extern const u8 *func_080CB808(Unit08076560 *unit);
extern u8 *func_080CB868(u8 *buffer, Unit08076560 *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit08076560 *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080775A8(void *unused, u8 *state);
extern void func_08078818(void *unused, u8 *state);
extern void func_08085AA8(void *unused, u8 *state);
extern void func_080868D4(void *unused, u8 *state);

/* An inlined copy of func_08080E80 (src/08080E80.c), as in 080775A8 and
 * 0807F168: the loops at 0x080766A6, 0x08076BFA and 0x08076C7A reload the
 * 0xC5C offset on every pass. */
static inline void clear_entries(u8 mode)
{
    int i;

    data_03002818->entry_mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}

void func_08076560(void *unused, u8 *state)
{
    s32 i;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        data_03002818->field_44d = 1;
        clear_entries(0);
        data_03002818->unit =
            &g_state_02000080[data_03002818->selected_unit];
        data_03002818->field_1d09 = data_03002818->unit->flags & 0x1C;
        data_03002818->block_bfc = data_03002818->block_98c;
        data_03002818->block_bfc.field_0c = 0;
        data_0200F22A = data_0200F22B = 0;
        data_03002818->counter = data_03002818->ready = 0;
        data_03002818->menu.option = 0;
        func_08079690(0);
        func_080895D0();
        data_03002818->field_c1d = 0;
        func_080753C8();
        data_03002818->changed = 3;
        data_0200F22B = data_030009E0[2].y;
        func_0808A604(3, 2);
        data_0200F228 = 3;
        *state = 0x15;
        break;
    case 1:
        data_03002818->unit =
            &g_state_02000080[data_03002818->selected_unit];
        data_03002818->field_1d09 = data_03002818->unit->flags & 0x1C;
        data_03002818->field_1d09 |= 1;
        func_08075620(0, data_03002818->unit, 0, 1);
        func_08076420(data_03002818->selected_entry);
        func_08074FA4(data_03002818->unit);
        func_080750D8(data_03002818->unit);
        func_08088FEC(&data_03002818->menu, 0);
        func_0808B890(4, func_0808B8E4(4, 1, 1,
                      data_03002818->menu.option * 2 + 2), 10, 0xB000);
        func_0808A604(4, 2);
        func_0808A604(3, 2);
        func_0808A604(2, 2);
        data_03002818->counter = 10;
        func_08073254();
        *state = 2;
        break;
    case 0x1A: {
        u16 value = func_08089D64(&data_03002818->menu) + 0x2C;

        data_03002818->saved_submode = data_03002818->submode;
        data_03002818->submode = 0;
        func_08089CE4(&data_03002818->menu);
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->counter = 0;
        data_03002818->mode = 3;
        func_08019A8C(data_02003CB0, value, &data_03000990, &data_03000E80);
        *state = 0x1B;
        break;
    }
    case 0x1B:
        if (func_08011860() == 0)
            break;
        data_03002818->timer = 15;
        data_03002818->mode = data_03002818->saved_mode;
        data_03002818->submode = data_03002818->saved_submode;
        *state = 0x1C;
        break;
    case 0x1C:
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer) {
            data_03002818->timer--;
        } else {
            func_0808A1EC(&data_03002818->menu);
            *state = 2;
        }
        break;
    case 2: {
        s32 count;
        u16 choice;

        func_08073254();
        count = 0;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.units[i].type)
                count++;
        }
        if (count > 1) {
            data_03002818->submode = 1;
        } else {
            data_03002818->saved_submode = data_03002818->submode = 0;
        }
        if (data_03002818->counter) {
            data_03002818->counter--;
            break;
        }
        if (data_03000000.pressed == 4) {
            *state = 0x1A;
        } else if (data_03000000.pressed & 1) {
            choice = func_08089D64(&data_03002818->menu);
            func_08141540(0x64);
            if (choice == 0) {
                data_0200F228 = 0xD;
            } else if (choice == 1) {
                data_0200F228 = 0xF;
            } else if (choice == 2) {
                if (data_03002818->unit->unknown_06 > 5) {
                    func_08141540(0x6A);
                    break;
                }
                data_0200F228 = 0x11;
            } else {
                if ((data_03002818->unit->flags & 0x1C)
                    || !(data_03002818->unit->type == 1
                         || func_080C8194(data_03002818->unit, 0x5E)
                         || func_080C8194(data_03002818->unit, 10)
                         || func_080C8194(data_03002818->unit, 9)
                         || func_080C8194(data_03002818->unit, 4)
                         || func_080C8194(data_03002818->unit, 12)
                         || func_080C8194(data_03002818->unit, 6))) {
                    func_08141540(0x6A);
                    break;
                }
                data_0200F228 = 0x13;
            }
            func_08089CAC(&data_03002818->menu);
            data_0200F229 = 4;
            /* Indexed by the window just stored: the ROM adds 4 * 0x4C to
             * the table and stores at [r0, #5] (0x08076B26-0x08076B2E, and
             * 0x08076B98, 0x08076DE4 below). */
            data_030009E0[data_0200F229].unknown_05 = 3;
            func_0808A604(4, 0xC);
            *state = 0x22;
        } else if (data_03000000.pressed & 2) {
            if (!(data_03002818->control & 2)) {
                data_03002818->submode = 0;
                func_08089CAC(&data_03002818->menu);
                func_08141540(0x69);
                data_0200F229 = 4;
                data_0200F228 = 5;
                data_030009E0[data_0200F229].unknown_05 = 3;
                func_0808A604(4, 0xC);
                *state = 0x22;
                break;
            }
        } else if (data_03000000.pressed & 0x20) {
            if (data_03002818->item_count == 1)
                break;
            if (!(data_03002818->control & 2)) {
                clear_entries(0);
                func_08141540(0x74);
                func_08072C78(0x2000, 1);
                data_03002818->counter = 0;
                *state = 0x17;
            }
        } else if (data_03000000.pressed & 0x10) {
            if (data_03002818->item_count == 1)
                break;
            if (!(data_03002818->control & 2)) {
                clear_entries(0);
                func_08141540(0x74);
                data_03002818->counter = 0;
                func_08072C78(0x1000, 1);
                *state = 0x17;
            }
        }
        if (func_08088FEC(&data_03002818->menu, data_03000000.repeated)) {
            func_0808B890(4, func_0808B8E4(4, 1, 1,
                          data_03002818->menu.selection * 2 + 2),
                          10, 0xC000);
            func_0808B890(4, func_0808B8E4(4, 1, 1,
                          data_03002818->menu.option * 2 + 2), 10, 0xB000);
            func_0808A604(4, 2);
        }
        break;
    }
    case 3:
        func_08141540(0x65);
        func_08074DC4();
        func_08074FA4(data_03002818->unit);
        func_080750D8(data_03002818->unit);
        func_08088DF0(&data_03002818->menu, data_08393B5C, 4, 0x1C,
                      0, 1, 0, 1, 0, 0, data_03002818->menu.option);
        func_08088FEC(&data_03002818->menu, 0);
        func_0808B890(4, func_0808B8E4(4, 1, 1,
                      data_03002818->menu.selection * 2 + 2),
                      10, 0xC000);
        func_0808B890(4, func_0808B8E4(4, 1, 1,
                      data_03002818->menu.option * 2 + 2), 10, 0xB000);
        func_0808A604(4, 2);
        data_0200F229 = 4;
        data_030009E0[data_0200F229].unknown_05 = 3;
        func_0808A604(4, 0xB);
        data_03002818->counter = 6;
        data_0200F228 = 2;
        *state = 0x22;
        break;
    case 4:
        break;
    case 5:
        /* CpuFill16 of the six cells src/0807B858.c clears, then of two
         * layers: the SDK's vu16 temporary, spelled through a pointer until
         * fftadecomp-kit#164, with the text of 0807B858.  Each of the nine
         * fills (eight here, one in case 0x16) has its own halfword,
         * sp+0x1C..sp+0x2C, and takes its address before the zero:
         * add r0, sp, #0x1C; movs r5, #0 at 0x08076E30-0x08076E32. */
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
        data_0200F228 = 0xFE;
        *state = 0x16;
        break;
    case 0xD:
        func_08006ADC(&data_03002730, 2, (u32)func_080775A8);
        *state = 0xE;
        break;
    case 0xE:
        if (data_03002730.flags[2] != 0xFF)
            break;
        data_03002818->menu.option = 0;
        *state = 3;
        break;
    case 0xF:
        func_08006ADC(&data_03002730, 2, (u32)func_08078818);
        *state = 0x10;
        break;
    case 0x10:
        if (data_03002730.flags[2] != 0xFF)
            break;
        data_03002818->menu.option = 1;
        *state = 3;
        break;
    case 0x11:
        func_08006ADC(&data_03002730, 2, (u32)func_08085AA8);
        *state = 0x12;
        break;
    case 0x12:
        if (data_03002730.flags[2] != 0xFF)
            break;
        data_03002818->menu.option = 2;
        *state = 3;
        break;
    case 0x13:
        func_08006ADC(&data_03002730, 2, (u32)func_080868D4);
        *state = 0x14;
        break;
    case 0x14:
        if (data_03002730.flags[2] == 0xFE) {
            if (data_03002818->item_count - 1 <= data_03002818->selected_entry) {
                func_08072C78(0x2000, 1);
                func_08073254();
            }
            func_08080D34(0);
            data_03002818->timer = 0;
            data_03002818->step = 0;
            data_0200F228 = 0xFD;
            *state = 0xC8;
        } else if (data_03002730.flags[2] == 0xFF) {
            data_03002818->menu.option = 3;
            *state = 3;
        }
        break;
    case 0xC8:
        data_03002818->timer = (data_03002818->timer + 1) % 240;
        if (++data_03002818->step == 8)
            *state = data_0200F228;
        func_08087554(8, data_03002818->step);
        break;
    case 0x15:
        if (data_03002818->counter == 0) {
            func_08075620(0, data_03002818->unit, 0, 1);
            func_0808A604(3, 2);
        }
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
            *state = data_0200F228;
        }
        break;
    case 0x16:
        if (data_03002818->counter++ < 10) {
            if (data_030009E0[2].y > -9) {
                data_030009E0[2].y--;
                func_0808A604(2, 2);
            }
            data_0200F22A = data_03002818->field_be8 / 8;
            data_0200F22B = data_03002818->field_bea / 8;
            data_03002818->marker_x = data_0200F22A;
            data_03002818->marker_y = data_0200F22B;
            func_0804C788(data_03000E30.entries, 0x19,
                          data_0200F22A, data_0200F22B);
            if (data_03002818->field_450 == 8) {
                data_03002818->changed = 3;
                data_03002818->offset_x -= 8;
                data_03002818->offset_y = 0x38;
            }
            data_03002818->field_bea -= 0x40;
        } else {
            func_0804C7A0(data_03000E30.entries, 0x1A);
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_03000E80.map,
                              (data_03000E80.width * data_03000E80.height) |
                                  0x01000000);
            }
            *state = data_0200F228;
        }
        break;
    case 0x17:
        if (data_03002818->counter++ < 10) {
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8 - data_03002818->counter * 8;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
            data_03002818->changed = 3;
            data_03002818->offset_x -= 8;
            data_03002818->offset_y = 0x38;
        } else {
            u8 *buffer = data_02003CB0;
            s32 x = data_03002818->target_x / 8;
            s32 y = data_03002818->target_y / 8;
            const u8 *resource;
            void *object;

            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
            func_080748AC(data_03002818->unit);
            data_03002818->offset_x = 0;
            data_03002818->offset_y = 0x38;
            func_0804C788(data_03000E30.entries, 0x19, x, y);
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
    case 0x22:
        if (data_030009E0[data_0200F229].state)
            break;
        *state = data_0200F228;
        break;
    case 0xFE:
        func_08080D34(0);
        data_03002818->field_44d = 0;
        *state = 0xFF;
        break;
    case 0xFD:
        data_03002818->field_44d = 0;
        break;
    /* 0xFF shares the default label: the dispatch tree is balanced over
     * 25 values (root 0x13 at 0x08076570, node 0xFE at 0x0807666A), and the
     * 0xFF test itself folds into the jump to the default (0x08076676). */
    case 0xFF:
    default:
        data_03002818->field_44d = 0;
        break;
    }
}
