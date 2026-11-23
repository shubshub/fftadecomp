#include "ffta.h"

/* One row of a menu: the item it stands for, its cursor position and the
 * rows the four directions move to (as src/08088FEC.c reads them). */
typedef struct {
    u8 id;
    u8 x;
    u8 y;
    u8 unknown_03;
    u8 left;
    u8 right;
    u8 up;
    u8 down;
} MenuEntry0807F7B4;

/* The menu object at +0x45C, laid out as src/08088DF0.c builds it. */
typedef struct {
    u32 active : 1;
    u32 unknown_00 : 31;
    MenuEntry0807F7B4 entries[32];
    u8 count;
    u8 option;
    u8 unknown_106[2];
    u16 field_108;
} Menu0807F7B4;

typedef struct {
    u8 unknown_00[0x2a];
    u16 items[5];
} Unit0807F7B4;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u8 unknown_0026[0x404];
    u8 saved_submode;
    u8 field_42b;
    u8 unknown_042c[0xc];
    s16 marker_y;
    u8 mode;
    u8 saved_mode;
    u8 unknown_043c[0x20];
    Menu0807F7B4 menu;
    u8 unknown_0568[0x68d];
    u8 ready;
    u8 unknown_0bf6[0x16];
    u16 counter;
    u8 unknown_0c0e[0x626];
    u16 texts[5];
    u8 unknown_123e[0xac6];
    u8 submode;
    u8 unknown_1d05;
    u8 field_1d06;
    u8 unknown_1d07[5];
    Unit0807F7B4 *unit;
} State0807F7B4;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input0807F7B4;

/* `x` is read with ldrsb (0x080800AC, 0x08080108), as in src/0807DDB8.c. */
typedef struct {
    u8 state;
    u8 unknown_01[0x33];
    s8 x;
    u8 unknown_35[0x17];
} Window0807F7B4;

typedef struct {
    u16 name;
    u16 description;
    u8 unknown_04[0x1c];
} Item0807F7B4;

extern State0807F7B4 *data_03002818;
extern Table data_03002730;
extern Input0807F7B4 data_03000000;
extern Window0807F7B4 data_030009E0[];
extern const Item0807F7B4 g_table_0851D180[];
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_0200F246;
extern u8 data_0200F247;
extern u8 data_0200F248;
extern MenuEntry0807F7B4 data_0200F250[];
extern const MenuEntry0807F7B4 data_08393C04[];

extern u32 func_080C92F0(void *unit, u32 selector);
extern u16 func_080C9314(const void *data);
extern void func_08074CE8(u32 width);
extern void func_08074908(Unit0807F7B4 *unit);
extern void func_08074A54(Unit0807F7B4 *unit);
extern void func_08075620(s32 mode, Unit0807F7B4 *unit, s32 redraw,
                          s32 numbered);
extern void func_0808A604(u32 object, u32 command);
extern void func_08141540(u16 song_id);
extern void func_08019A8C(void *data, u16 index, void *first, void *second);
extern u16 func_08011860(void);
extern void func_08088DF0(Menu0807F7B4 *object,
                          const MenuEntry0807F7B4 *entries, s32 count,
                          s32 graphic, u32 palette, u32 visible, u32 enabled,
                          u32 mode, u32 variant, u32 style, u32 option);
extern u16 func_08088FEC(Menu0807F7B4 *object, u16 input);
extern void func_08088F5C(Menu0807F7B4 *object);
extern void func_08089CAC(Menu0807F7B4 *object);
extern void func_08089CE4(Menu0807F7B4 *object);
extern void func_0808A1EC(Menu0807F7B4 *object);
extern void func_0807E2C4(void *unused, u8 *state);

/* Complete [0x0807F7B4, 0x080802E2): 2862 bytes, 1053 instructions. */
void func_0807F7B4(void *unused, u8 *state)
{
    u16 value;

    switch (*state) {
    case 0:
        data_0200F248 = func_080C92F0(data_03002818->unit, 12);
        data_03002818->ready = 2;
        func_08074CE8(30);
        func_08074908(data_03002818->unit);
        func_0808A604(4, 3);
        data_0200F246 = 3;
        *state = 34;
        break;
    case 3:
        /* The byte is cleared here and again in the first arm (strb at
         * 0x0807F8FA and 0x0807F918). */
        data_03002818->field_1d06 = 0;
        if (data_03000000.pressed & 3) {
            func_08141540(0x68);
            data_0200F246 = 0xfe;
            data_03002818->field_1d06 = 0;
            *state = 37;
        } else if (data_03000000.pressed & 0x20) {
            /* Left and right do the same; the ROM has both bodies
             * (0x0807F934-0x0807F952 and 0x0807F958-0x0807F97A). */
            func_08141540(0x6c);
            func_0808A604(4, 1);
            data_0200F246 = 15;
            *state = 41;
        } else if (data_03000000.pressed & 0x10) {
            func_08141540(0x6c);
            func_0808A604(4, 1);
            data_0200F246 = 15;
            *state = 41;
        } else if (data_03000000.pressed == 4) {
            data_03002818->saved_submode = data_03002818->submode;
            data_03002818->submode = 0;
            *state = 24;
        }
        break;
    case 15:
        if (data_0200F248)
            data_03002818->field_1d06 = 2;
        if (data_03000000.pressed & 3) {
            func_08141540(0x68);
            data_03002818->field_1d06 = 0;
            data_0200F246 = 0xfe;
            *state = 37;
        } else if (data_03000000.pressed & 0x20) {
            /* Both bodies again: 0x0807FA04-0x0807FA20, 0x0807FA28-0x0807FA48. */
            func_08141540(0x6c);
            func_0808A604(4, 1);
            data_0200F246 = 3;
            *state = 41;
        } else if (data_03000000.pressed & 0x10) {
            func_08141540(0x6c);
            func_0808A604(4, 1);
            data_0200F246 = 3;
            *state = 41;
        } else if (data_03000000.pressed == 4) {
            data_03002818->saved_submode = data_03002818->submode;
            data_03002818->submode = 0;
            *state = 26;
        } else if (data_0200F248 && (data_03000000.pressed & 0x100)) {
            data_03002818->field_1d06 = 0;
            func_08141540(0x68);
            data_0200F246 = 42;
            *state = 37;
        }
        break;
    case 21:
        value = func_080C9314(data_03002818->unit);
        data_03002818->saved_submode = data_03002818->submode;
        data_03002818->submode = 0;
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->counter = 0;
        data_03002818->mode = 3;
        func_08019A8C(data_02003CB0, value, data_03000990, data_03000E80);
        *state = 22;
        break;
    case 22:
        if (func_08011860()) {
            data_03002818->marker_y -= 128;
            data_03002818->field_42b = 10;
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->submode = data_03002818->saved_submode;
            data_03002818->timer = 15;
            *state = 23;
        }
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        break;
    case 23:
        data_03000000.held = 0;
        data_03000000.repeated = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer != 0) {
            data_03002818->timer--;
            data_03000000.held = 0;
            data_03000000.pressed = 0;
        } else {
            *state = data_0200F246;
        }
        break;
    case 24: {
        Unit0807F7B4 *unit = data_03002818->unit;
        int i, n;

        for (i = 0, n = 0; i < 5; i++) {
            if (unit->items[i] != 0) {
                data_0200F250[n + 1] = data_08393C04[n + 1];
                data_0200F250[n + 1].y = 0x41 + i * 16;
                data_0200F250[n + 1].id = i;
                data_0200F250[n + 1].up = n;
                data_0200F250[n + 1].down = n + 2;
                n++;
            }
        }
        data_0200F250[n].down = 0;
        data_0200F250[0] = data_08393C04[0];
        data_0200F250[0].up = n;
        func_08141540(0x64);
        func_08088DF0(&data_03002818->menu, data_0200F250, n + 1, 0x1f,
                      2, 1, 0, 2, 0, 2, 0);
        func_08088FEC(&data_03002818->menu, 0);
        *state = 25;
        break;
    }
    case 25: {
        /* Each arm has its own text id and its own copy of the tail: case 27
         * keeps both copies (0x0807FE4A-0x0807FEB4, 0x0807FEE8-0x0807FF46) and
         * this case's arms branch into them (0x0807FCC8, 0x0807FD02). */
        u8 option;

        if (data_03000000.pressed & 1) {
            option = data_03002818->menu.option;
            if (option == 0) {
                u16 text = func_080C9314(data_03002818->unit);

                func_08088F5C(&data_03002818->menu);
                data_03002818->counter = 0;
                data_03002818->saved_mode = data_03002818->mode;
                data_03002818->mode = 3;
                data_03002818->marker_y -= 128;
                func_08019A8C(data_02003CB0, text, data_03000990,
                              data_03000E80);
                data_0200F246 = *state;
                *state = 28;
            } else {
                /* The unit (0x0807FCE4) and the row's slot (0x0807FCEC) are
                 * read before the item table's address (0x0807FCEE). */
                Unit0807F7B4 *unit = data_03002818->unit;
                u8 slot = data_0200F250[option].id;
                u16 text = g_table_0851D180[unit->items[slot]].description;

                func_08089CE4(&data_03002818->menu);
                data_03002818->counter = 0;
                data_03002818->saved_mode = data_03002818->mode;
                data_03002818->mode = 3;
                data_03002818->marker_y -= 128;
                func_08019A8C(data_02003CB0, text, data_03000990,
                              data_03000E80);
                data_0200F246 = *state;
                *state = 28;
            }
            break;
        }
        if (data_03000000.pressed & 2) {
            func_08141540(0x68);
            data_03002818->field_42b = 10;
            func_08089CAC(&data_03002818->menu);
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->submode = data_03002818->saved_submode;
            data_03002818->timer = 15;
            data_0200F246 = 3;
            *state = 23;
        }
        if (data_03002818->menu.count > 1 && data_03002818->menu.active
            && func_08088FEC(&data_03002818->menu, data_03000000.repeated))
            func_08141540(0x6d);
        break;
    }
    case 26: {
        int i, n;

        for (i = 0, n = 0; i < 5; i++) {
            if (data_03002818->texts[i] != 0) {
                data_0200F250[n + 1] = data_08393C04[n + 1];
                data_0200F250[n + 1].id = i;
                data_0200F250[n + 1].y = 0x41 + i * 16;
                data_0200F250[n + 1].up = n;
                data_0200F250[n + 1].down = n + 2;
                n++;
            }
        }
        data_0200F250[n].down = 0;
        data_0200F250[0] = data_08393C04[0];
        data_0200F250[0].up = n;
        func_08141540(0x64);
        func_08088DF0(&data_03002818->menu, data_0200F250, n + 1, 0x1f,
                      2, 1, 0, 2, 0, 2, 0);
        func_08088FEC(&data_03002818->menu, 0);
        *state = 27;
        break;
    }
    case 27: {
        u8 option;

        if (data_03000000.pressed & 1) {
            option = data_03002818->menu.option;
            if (option == 0) {
                u16 text = func_080C9314(data_03002818->unit);

                func_08088F5C(&data_03002818->menu);
                data_03002818->counter = 0;
                data_03002818->saved_mode = data_03002818->mode;
                data_03002818->mode = 3;
                data_03002818->marker_y -= 128;
                func_08019A8C(data_02003CB0, text, data_03000990,
                              data_03000E80);
                data_0200F246 = *state;
                *state = 28;
            } else {
                u16 text = data_03002818->texts[data_0200F250[option].id];

                func_08089CE4(&data_03002818->menu);
                data_03002818->counter = 0;
                data_03002818->saved_mode = data_03002818->mode;
                data_03002818->mode = 3;
                data_03002818->marker_y -= 128;
                func_08019A8C(data_02003CB0, text, data_03000990,
                              data_03000E80);
                data_0200F246 = *state;
                *state = 28;
            }
            break;
        }
        if (data_03000000.pressed & 2) {
            func_08141540(0x68);
            func_08089CAC(&data_03002818->menu);
            data_03002818->field_42b = 10;
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->submode = data_03002818->saved_submode;
            data_03002818->timer = 15;
            data_0200F246 = 15;
            *state = 23;
        }
        if (data_03002818->menu.count > 1 && data_03002818->menu.active
            && func_08088FEC(&data_03002818->menu, data_03000000.repeated))
            func_08141540(0x6d);
        break;
    }
    case 28:
        if (func_08011860()) {
            data_03002818->field_42b = 10;
            data_03002818->timer = 15;
            data_03002818->marker_y += 128;
            *state = 29;
        }
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        break;
    case 29:
        func_0808A1EC(&data_03002818->menu);
        data_03000000.held = 0;
        data_03000000.repeated = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer != 0) {
            data_03002818->timer--;
            data_03000000.held = 0;
            data_03000000.pressed = 0;
        } else {
            *state = data_0200F246;
        }
        break;
    case 34:
        if (data_030009E0[4].x == 16)
            *state = data_0200F246;
        else if (data_030009E0[4].x > 16)
            data_030009E0[4].x -= 2;
        else if (data_030009E0[4].x < 16) /* cmp #15 at 0x080800D0 */
            data_030009E0[4].x += 2;
        data_03002818->menu.field_108 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 37:
        if (data_030009E0[4].x > 30)
            *state = data_0200F246;
        else
            data_030009E0[4].x += 2;
        data_03002818->menu.field_108 = data_030009E0[4].x * 8;
        func_0808A604(4, 3);
        break;
    case 42:
        data_03002818->submode = 0;
        func_08006ADC(&data_03002730, 3, (u32)func_0807E2C4);
        *state = 44;
        break;
    case 44:
        if (data_03002730.flags[3] == 18) {
            func_08075620(1, data_03002818->unit, 1, 1);
            *state = 43;
        }
        break;
    case 43:
        data_0200F247 = 3;
        func_0808A604(3, 2);
        data_03002818->submode = 2;
        data_03002818->ready = 2;
        *state = 45;
        break;
    case 45:
        if (data_030009E0[data_0200F247].state == 0) {
            if (data_0200F248)
                data_03002818->field_1d06 = 2;
            data_0200F246 = 15;
            *state = 41;
        }
        break;
    case 40:
        /* An empty case: the switch tests 40 at 0x0807F83A and goes to the
         * common exit 0x080802D2. */
        break;
    case 41:
        /* Each arm stores the next state (0x08080260, 0x0808028E). */
        if (data_03002818->ready == 2) {
            data_03002818->ready = 3;
            func_08074CE8(30);
            func_08074A54(data_03002818->unit);
            func_08088FEC(&data_03002818->menu, 0);
            *state = 34;
        } else {
            data_03002818->ready = 2;
            func_08074CE8(30);
            func_08074908(data_03002818->unit);
            *state = 34;
        }
        func_0808A604(4, 3);
        break;
    case 46:
        if (data_030009E0[data_0200F247].state == 0)
            *state = data_0200F246;
        break;
    case 254:
        *state = 255;
        break;
    case 255:
        /* Empty and never tested, but the compare tree's pivots (29 at
         * 0x0807F7C4, 43 at 0x0807F82E, 46 at 0x0807F86E) split 23 case
         * values, two of them above 46; only one above 254 leaves no test. */
        break;
    }
}
