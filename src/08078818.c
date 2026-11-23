#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[3];
    u8 entity;
    u8 unknown_09[0x1f];
    u16 flags;
    u8 unknown_2a[0xc];
    u8 override_36;
    u8 unknown_37[3];
    u8 override_3a;
    u8 override_3b;
    u8 override_3c;
    u8 unknown_3d[0xcb];
} Unit08078818;

typedef struct {
    u8 unknown_0000[0x80];
    Unit08078818 units[24];
    u8 unknown_1940[0x2fc1 - 0x1940];
    u8 flags_2fc1;
} GameState08078818;

typedef struct {
    u32 first;
    u32 second;
} MenuEntry08078818;

typedef struct {
    u32 active : 1;
    u32 unknown_00 : 31;
    u8 unknown_004[0x100];
} Menu08078818;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u8 unknown_0026[0x404];
    u8 unknown_042a;
    u8 unknown_042b[0xd];
    s16 marker_y;
    u8 unknown_043a;
    u8 unknown_043b;
    u8 unknown_043c[0x10];
    u8 unknown_044c;
    u8 unknown_044d[5];
    u8 field_452;
    u8 unknown_453;
    const u8 *field_454;
    s16 offset_x;
    s16 offset_y;
    Menu08078818 object;
    u8 unknown_0560;
    u8 initial_choice;
    u8 unknown_0562[2];
    s16 unknown_0564;
    u8 unknown_0566[0x3f6];
    u8 count;
    u8 unknown_095d[0x13];
    u8 unknown_0970;
    u8 unknown_0971[0x15];
    u8 selected;
    u8 selected_unit;
    u8 unknown_0988[0x268];
    s16 target_x;
    s16 target_y;
    u8 unknown_0bf4;
    u8 unknown_0bf5;
    u8 unknown_0bf6[0x16];
    u16 counter;
    u8 unknown_0c0e[0xe];
    u8 mode;
    u8 unknown_0c1d[0x3f];
    u16 entries[6];
    u8 unknown_0c68[0x5cc];
    u16 texts[5];
    u8 unknown_123e[0xac6];
    u8 unknown_1d04;
    u8 unknown_1d05;
    u8 unknown_1d06;
    u8 unknown_1d07[2];
    u8 unknown_1d09;
    u8 unknown_1d0a[2];
    Unit08078818 *record;
} State08078818;

typedef struct {
    u8 state;
    u8 unknown_01[0x33];
    s8 x;
    u8 unknown_35[0x17];
} Entry08078818;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display08078818;

extern State08078818 *data_03002818;
extern GameState08078818 g_state_02000000;
extern Table data_03002730;
extern Entry08078818 data_030009E0[];
extern InputState data_03000000;
extern Display08078818 data_03000E30;
extern u8 data_0200F22E;
extern u8 data_0200F22F;
extern const MenuEntry08078818 data_08393BBC[];
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_06014300[];
extern u16 data_03003860[];

extern void func_08141540(u32 sound);
extern void func_08074CE8(u32 width);
extern void func_08074A54(Unit08078818 *record);
extern void func_08074908(Unit08078818 *record);
extern void func_080748AC(Unit08078818 *record);
extern void func_08088DF0(Menu08078818 *object, const MenuEntry08078818 *entries,
                          s32 count, s32 graphic, u32 palette, u32 visible,
                          u32 enabled, u32 mode, u32 variant, u32 style, u32 option);
/* The result is tested as a halfword (lsls #16 at 0x08078F06). */
extern u16 func_08088FEC(Menu08078818 *object, u16 input);
extern void func_080774B4(Menu08078818 *object, int alternate);
extern void func_08089CE4(Menu08078818 *object);
extern void func_0808A1EC(Menu08078818 *object);
extern void func_0808A604(u32 object, u32 command);
extern void func_08076420(s32 selected);
extern u8 func_080CB54C(Unit08078818 *unit, u8 enabled);
extern void func_0801174C(void *context, u8 kind, u16 selection, void *first,
                          void *second, u16, u16, u8, u8, u16);
extern void func_08013364(void);
extern u16 func_08011860(void);
extern void func_08075620(s32 mode, Unit08078818 *unit, s32 redraw, s32 numbered);
extern void func_08073254(void);
extern void func_08019A8C(void *buffer, u16 text, void *first, void *second);
extern u8 func_080C9078(const void *data);
extern void func_08072C78(u16 keys, int fast);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern u8 func_080CB7C0(Unit08078818 *unit, u8 selector);
extern const u8 *func_080CB808(Unit08078818 *unit);
extern u8 *func_080CB868(u8 *buffer, Unit08078818 *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit08078818 *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0807DDB8(u8 slot, u8 *state);
extern void func_0807E2C4(u8 slot, u8 *state);

/* An inlined copy of func_08080E80 (src/08080E80.c): the ROM repeats its
 * body at 0x08078910, 0x080791E2 and 0x08079260, and each copy reloads the
 * 0xC5C offset inside its loop (0x08078926, 0x080791F2, 0x08079270) where an
 * open-coded loop hoists it. */
static inline void reset_entries(u8 mode)
{
    int i;

    data_03002818->mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}

/* Complete target [0x08078818, 0x08079690): 3704 bytes, 1387 instructions,
 * including the literal pools. */
void func_08078818(u8 slot, u8 *state)
{
    int i, count;
    u16 text;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        reset_entries(0);
        data_03002818->unknown_0bf5 = 3;
        func_08074CE8(0x1e);
        func_08074A54(data_03002818->record);
        func_08088DF0(&data_03002818->object, data_08393BBC, 4, 0x1c,
                      0, 0, 0, 0, 0, 1, 0);
        func_08088FEC(&data_03002818->object, 0);
        data_03002818->unknown_1d06 = 0;
        data_03002818->unknown_1d05 = 0;
        func_080774B4(&data_03002818->object, 1);
        func_0808A604(4, 3);
        data_0200F22E = 0xf;
        *state = 0x23;
        break;
    case 1:
        data_03002818->record = &g_state_02000000.units[data_03002818->selected_unit];
        data_03002818->unknown_1d09 = data_03002818->record->flags & 0x1c;
        data_03002818->unknown_1d09 |= 1;
        func_08076420(data_03002818->selected);
        func_08074CE8(0x1e);
        func_08074A54(data_03002818->record);
        func_08088DF0(&data_03002818->object, data_08393BBC, 4, 0x1c,
                      0, 0, 0, 0, 0, 1, data_03002818->initial_choice);
        func_08088FEC(&data_03002818->object, 0);
        func_080774B4(&data_03002818->object, 1);
        func_0808A604(2, 3);
        func_0808A604(4, 3);
        data_0200F22E = 0xf;
        *state = 0x23;
        break;
    case 2:
        if (func_080CB54C(data_03002818->record, 1) == 0) {
            *state = 0x14;
        } else {
            data_03002818->object.active = 0;
            data_03002818->unknown_1d04 = 0;
            *state = 0x12;
        }
        break;
    case 0x12: {
        /* The buffer address is loaded first (0x08078AF4), ahead of the
           three stores. */
        u8 *buffer = data_02003CB0;

        data_03002818->unknown_043b = data_03002818->unknown_043a;
        data_03002818->unknown_043a = 3;
        data_03002818->timer = 0;
        func_0801174C(buffer, 1, 0x22, data_03000990, data_03000E80,
                      2, 2, 0x18, 4, 0x3a0);
        *state = 0x13;
        break;
    }
    case 0x13:
        if (data_03002818->timer++ > 70) {
            func_08013364();
            data_03002818->unknown_043a = data_03002818->unknown_043b;
            count = 0;
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].active)
                    count++;
            }
            if (count > 1) {
                data_03002818->unknown_1d04 = 1;
            } else {
                data_03002818->unknown_042a = data_03002818->unknown_1d04 = 0;
            }
            data_0200F22E = 0x14;
            *state = 0x2f;
        }
        func_08011860();
        break;
    case 0x2f:
        if (func_08011860())
            *state = data_0200F22E;
        break;
    case 0x14:
        if (data_03002818->unknown_044c == 0)
            data_03002818->record = &g_state_02000000.units[data_03002818->selected_unit];
        data_03002818->unknown_1d09 = data_03002818->record->flags & 0x1c;
        data_03002818->unknown_1d09 |= 1;
        func_08076420(data_03002818->selected);
        func_08074CE8(0x1e);
        func_08074A54(data_03002818->record);
        data_03002818->object.active = 1;
        func_080774B4(&data_03002818->object, 1);
        func_0808A604(2, 3);
        func_0808A604(4, 3);
        data_0200F22E = 0xf;
        *state = 0x23;
        break;
    case 0x23:
        if (data_030009E0[2].state != 0)
            break;
        if (data_030009E0[4].state != 0)
            break;
        if (data_03002818->unknown_044c == 1)
            func_08075620(1, data_03002818->record, 0, 0);
        else
            func_08075620(data_03002818->unknown_044c != 0, data_03002818->record, 0, 1);
        func_0808A604(2, 2);
        func_0808A604(3, 3);
        *state = 0x24;
        break;
    case 0x24:
        if (data_030009E0[3].state == 0)
            *state = 0x22;
        break;
    case 0x15:
        if (func_08011860() == 0)
            break;
        data_03002818->timer = 0x14;
        data_03002818->unknown_043a = data_03002818->unknown_043b;
        data_03002818->unknown_1d04 = data_03002818->unknown_042a;
        *state = 0x16;
        break;
    case 0x16:
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer != 0) {
            data_03002818->timer--;
            break;
        }
        func_0808A1EC(&data_03002818->object);
        *state = 0xf;
        break;
    case 0xf:
        func_08073254();
        data_03002818->unknown_1d06 = 2;
        if (data_03002818->unknown_044c == 0 && data_03002818->count > 1) {
            data_03002818->unknown_1d04 = 1;
        } else {
            data_03002818->unknown_042a = data_03002818->unknown_1d04 = 0;
        }
        if (data_03002818->unknown_1d09 & 0x1c) {
            data_03002818->unknown_1d05 = 0;
        } else if (data_03002818->initial_choice == 0) {
            if (data_03002818->record->override_36)
                data_03002818->unknown_1d05 = 1;
            else
                data_03002818->unknown_1d05 = 0;
        } else if (data_03002818->initial_choice == 1) {
            if (data_03002818->record->override_3a)
                data_03002818->unknown_1d05 = 1;
            else
                data_03002818->unknown_1d05 = 0;
        } else if (data_03002818->initial_choice == 2) {
            if (data_03002818->record->override_3b)
                data_03002818->unknown_1d05 = 1;
            else
                data_03002818->unknown_1d05 = 0;
        } else if (data_03002818->initial_choice == 3) {
            if (data_03002818->record->override_3c)
                data_03002818->unknown_1d05 = 1;
            else
                data_03002818->unknown_1d05 = 0;
        }
        if (func_08088FEC(&data_03002818->object, data_03000000.repeated)) {
            func_080774B4(&data_03002818->object, 1);
            func_0808A604(4, 3);
        }
        if (data_03000000.pressed == 4) {
            text = data_03002818->texts[data_03002818->initial_choice + 1];
            if (text == 0)
                break;
            data_03002818->unknown_042a = data_03002818->unknown_1d04;
            func_08089CE4(&data_03002818->object);
            data_03002818->unknown_1d04 = 0;
            data_03002818->unknown_043b = data_03002818->unknown_043a;
            data_03002818->counter = 0;
            data_03002818->unknown_043a = 3;
            func_08019A8C(data_02003CB0, text, data_03000990, data_03000E80);
            *state = 0x15;
        } else if (data_03000000.pressed & 1) {
            if (data_03002818->unknown_1d09 & 0x1c) {
                func_08141540(0x6a);
                break;
            }
            data_03002818->unknown_1d05 = 0;
            data_03002818->unknown_1d04 = 0;
            func_08141540(0x64);
            data_0200F22E = 0x10;
            *state = 0x26;
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x68);
            data_03002818->unknown_1d05 = 0;
            data_03002818->unknown_1d06 = 0;
            data_0200F22E = 0xfe;
            *state = 0x25;
        } else if (data_03000000.pressed & 0x200) {
            if (data_03002818->unknown_1d09 & 0x1c) {
                func_08141540(0x6b);
            } else if (data_03002818->initial_choice == 0) {
                if (data_03002818->record->override_36) {
                    func_08141540(0x9c);
                    data_03002818->record->override_36 = 0;
                    data_03002818->record->entity = func_080C9078(data_03002818->record);
                    *state = 2;
                } else {
                    func_08141540(0x6b);
                }
            } else if (data_03002818->initial_choice == 1) {
                if (data_03002818->record->override_3a) {
                    func_08141540(0x9c);
                    data_03002818->record->override_3a = 0;
                    *state = 2;
                } else {
                    func_08141540(0x6b);
                }
            } else if (data_03002818->initial_choice == 2) {
                if (data_03002818->record->override_3b) {
                    func_08141540(0x9c);
                    data_03002818->record->override_3b = 0;
                    *state = 2;
                } else {
                    func_08141540(0x6b);
                }
            } else if (data_03002818->initial_choice == 3) {
                if (data_03002818->record->override_3c) {
                    func_08141540(0x9c);
                    data_03002818->record->override_3c = 0;
                    *state = 2;
                } else {
                    func_08141540(0x6b);
                }
            }
        } else if (data_03000000.pressed & 0x100) {
            func_08141540(0x64);
            data_03002818->unknown_1d04 = 0;
            data_03002818->unknown_1d05 = 0;
            data_03002818->unknown_1d06 = 0;
            data_0200F22E = 0x2a;
            *state = 0x25;
        } else if (data_03002818->unknown_044c == 0) {
            if (data_03000000.pressed & 0x20) {
                if (data_03002818->count == 1)
                    break;
                if (data_03002818->unknown_0970 & 2)
                    break;
                if (g_state_02000000.flags_2fc1 & 2)
                    reset_entries(0);
                func_08141540(0x74);
                func_08072C78(0x2000, 1);
                data_03002818->counter = 0;
                data_0200F22E = 1;
                *state = 0x28;
            } else if (data_03000000.pressed & 0x10) {
                if (data_03002818->count == 1)
                    break;
                if (data_03002818->unknown_0970 & 2)
                    break;
                if (g_state_02000000.flags_2fc1 & 2)
                    reset_entries(0);
                func_08141540(0x74);
                func_08072C78(0x1000, 1);
                data_03002818->counter = 0;
                data_0200F22E = 1;
                *state = 0x28;
            }
        }
        break;
    case 0x10:
        func_08089CE4(&data_03002818->object);
        func_08006ADC(&data_03002730, 3, (u32)func_0807DDB8);
        *state = 0x11;
        break;
    case 0x11:
        if (data_03002730.flags[3] == 0x12)
            *state = 2;
        break;
    case 0x2a:
        func_08089CE4(&data_03002818->object);
        func_08006ADC(&data_03002730, 3, (u32)func_0807E2C4);
        *state = 0x2c;
        break;
    case 0x2c:
        if (data_03002730.flags[3] == 0x12)
            *state = 2;
        break;
    case 0x22:
        if (data_030009E0[4].x == 16)
            *state = data_0200F22E;
        else if (data_030009E0[4].x > 16)
            data_030009E0[4].x -= 2;
        /* The third test is always true here, but the ROM keeps it
           (cmp #15 at 0x0807937C). */
        else if (data_030009E0[4].x < 16)
            data_030009E0[4].x += 2;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 0x25:
        if (data_030009E0[4].x > 30)
            *state = data_0200F22E;
        else
            data_030009E0[4].x += 2;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 0x26:
        if (data_030009E0[4].x > 18)
            *state = data_0200F22E;
        else
            data_030009E0[4].x += 2;
        data_03002818->unknown_0564 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 0x28:
        /* Each branch has its own x and y: the first keeps them in r2/r3
           (0x0807943A, 0x0807944A), the second in r5/r4 across its calls
           (0x080794B4, 0x080794C4). */
        if (data_03002818->counter++ < 10) {
            int x, y;

            x = data_03002818->target_x / 8;
            y = data_03002818->target_y / 8 - data_03002818->counter * 8;
            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 25, x, y);
            data_03002818->field_452 = 3;
            data_03002818->offset_x -= 8;
            data_03002818->offset_y = 56;
        } else {
            /* From func_080CB808 on, this is the body of func_0807478C
               (src/0807478C.c) with 3 stored to field_452. */
            u8 *buffer = data_02003CB0;
            int x, y;
            const u8 *resource;
            void *object;

            x = data_03002818->target_x / 8;
            y = data_03002818->target_y / 8;
            data_03002818->marker_y = y;
            func_0804C788(data_03000E30.entries, 25, x, y);
            func_080748AC(data_03002818->record);
            data_03002818->offset_x = 0;
            data_03002818->offset_y = 56;
            func_0804C788(data_03000E30.entries, 25, x, y);
            resource = func_080CB808(data_03002818->record);
            func_080CB868(buffer, data_03002818->record);
            func_0814186C(buffer, data_06014300, ((u32)resource << 10) >> 11);
            object = (u8 *)data_03002818 + 0x2E8;
            func_080CB8D4(object, func_080CB7C0(data_03002818->record, 1));
            data_03002818->field_454 = func_080CB928(data_03002818->record);
            data_03002818->field_452 = 3;
            func_0814186C((u8 *)data_03002818 + 0x28,
                          data_03003860, 0x04000080);
            func_0814186C((u8 *)data_03002818 + 0x228,
                          data_03003860 + 0x100, 0x04000080);
            func_0808A604(4, 1);
            *state = data_0200F22E;
        }
        break;
    case 0x29:
        if (data_03002818->unknown_0bf5 == 2) {
            data_03002818->unknown_0bf5 = 3;
            func_08074CE8(0x1e);
            func_08074A54(data_03002818->record);
            /* Stored in both arms (0x08079600, 0x0807962A). */
            *state = 0x22;
        } else {
            data_03002818->unknown_0bf5 = 2;
            func_08074CE8(0x1e);
            func_08074908(data_03002818->record);
            *state = 0x22;
        }
        func_0808A604(4, 3);
        break;
    case 0x2e:
        if (data_030009E0[data_0200F22F].state == 0)
            *state = data_0200F22E;
        break;
    case 0xfe:
        data_03002818->unknown_1d04 = 0;
        *state = 0xff;
        break;
    /* The finished state case 0xfe stores.  Its empty body shares the exit,
       but the compare tree is balanced for it: the upper subtree of 0x2e is
       rooted at 0xfe (0x080788F0), and the "> 0xfe" branch to the exit
       (0x080788F8-0x080788FC) is its folded test. */
    case 0xff:
        break;
    }
}
