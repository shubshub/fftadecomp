#include "ffta.h"

/* Complete target [0x080802E4, 0x08080D34): 2640 bytes, 980 reachable
 * instructions.  A state-machine step called as (index, &state), the
 * counterpart of func_0807F168 (src/0807F168.c): the cases it shares with
 * that function (0, 2, 26, 27, 28, 35, 24, 25, 0xFE, 0xFF) come in the same
 * order, each a variant of its text; cases 6-11 and 1 are new here.  The
 * switch is a compare tree; its far arms are reached through bl (the first
 * at 0x080802F8). */

typedef struct {
    u8 unknown_00[4];
    u8 type;
    u8 unknown_05[0x103];
} Unit080802E4;

typedef struct {
    u8 unknown_0000[0x80];
    Unit080802E4 units[24];
    u8 unknown_1940[0x1338];
    Unit080802E4 *character;
} Game080802E4;

typedef struct {
    u32 unknown_00[2];
    u16 field_08;
    u16 unknown_0a;
    u16 field_0c;
    u16 unknown_0e;
} Block080802E4;

typedef struct {
    u8 unknown_0000[0x24];
    u8 wait;
    u8 timer;
    u16 step;
    u8 unknown_0028[0x402];
    u8 saved_submode;
    u8 field_42b;
    u8 unknown_042c[0xa];
    s16 marker_x, marker_y;
    u8 mode;
    u8 saved_mode;
    u8 field_43c;
    u8 unknown_043d[0x10];
    u8 field_44d;
    u8 unknown_044e;
    u8 saved_phase;
    u8 unknown_0450[2];
    u8 changed;
    u8 unknown_0453;
    const u8 *field_454;
    s16 offset_x, offset_y;
    u8 unknown_045c[0x504];
    u16 field_960;
    /* One bit, as in src/08070C94.c, which sets and clears it: tested with
     * ldrb; movs #1; ands (0x08080842-0x08080846, 0x080808AA, 0x080809F2,
     * 0x08080A2A). */
    u8 field_962_0 : 1;
    u8 unknown_962_1 : 7;
    u8 unknown_0963[0x29];
    Block080802E4 block_98c;
    u8 unknown_099c[0x254];
    s16 target_x, target_y;
    u8 unknown_0bf4;
    u8 ready;
    u8 unknown_0bf6[6];
    Block080802E4 block_bfc;
    u16 counter;
    u8 unknown_0c0e[0x10f6];
    u8 submode;
    u8 unknown_1d05[7];
    Unit080802E4 *unit;
    u8 window[0];
} State080802E4;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display080802E4;

typedef struct {
    u8 unknown_00[0x14];
    u16 enabled;
    u8 unknown_16[6];
} EntryFlags080802E4;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState080802E4;

typedef struct {
    u8 unknown_00[0x35];
    u8 y;
    u8 unknown_36[0x16];
} TileRenderer080802E4;

extern State080802E4 *data_03002818;
extern Game080802E4 g_state_02000000;
extern Table data_03002730;
extern Display080802E4 data_03000E30;
extern InputState080802E4 data_03000000;
extern TileRenderer080802E4 data_030009E0[];
extern Unit080802E4 *data_030027F4;
extern u8 data_02003CB0[];
extern u8 data_06014300[];
extern u8 data_0894EAF4[];
extern u8 data_0894EB80[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
/* 0x0200F288..0x0200F28A are named by this function's literal pools only. */
extern u8 data_0200F288;
extern u8 data_0200F289;
extern u8 data_0200F28A;

extern void func_08073380(u32 value);
extern void func_08079690(u32 mode);
extern void func_080753C8(void);
extern void func_08075620(s32 mode, Unit080802E4 *unit, s32 redraw,
                          s32 numbered);
extern void func_0804C524(u8 *, u16, u32, u8, u8, u32, u8, u32, u8 *, u16,
                          u8);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern u8 func_080CB7C0(Unit080802E4 *unit, u8 selector);
extern const u8 *func_080CB808(Unit080802E4 *unit);
extern u8 *func_080CB868(u8 *buffer, Unit080802E4 *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit080802E4 *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_080C8240(void *data);
extern u16 func_080C9314(const void *data);
extern void func_08019A8C(void *context, u16 value, void *first, void *second);
extern void func_0801174C(void *window, u32 kind, u8 index, void *first,
                          void *second, u32 x, u32 y, u32 width, u32 height,
                          u32 tile);
/* A halfword result (src/08011860.c returns u32): narrowed with lsls #16
 * before each test (0x080806DC, 0x08080780, 0x08080908), as in
 * src/0807F168.c. */
extern u16 func_08011860(void);
extern void func_08013364(void);
extern s8 func_08013380(void);
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080D2F2C(void);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern void func_08141520(u16 sound);
extern void func_08141540(u16 song_id);
extern int func_0808A604(int index, u16 mode);
extern void func_080748AC(Unit080802E4 *unit);
extern void func_08087554(u8 period, u8 phase);
extern void func_0807F7B4(u32, u8 *);

/* Complete [0x080802E4, 0x08080D34): 2640 bytes. */
void func_080802E4(u32 index, u8 *state)
{
    s8 choice;
    s32 count;
    s32 i;

    switch (*state) {
    case 0: {
        int x, y;
        u8 *buffer = data_02003CB0;
        const u8 *resource;

        func_08073380(index);
        data_03002818->unit = data_030027F4;
        data_03002818->block_bfc = data_03002818->block_98c;
        data_03002818->field_44d = 4;
        func_08079690(1);
        data_03002818->block_bfc.field_0c = 0;
        data_0200F289 = data_0200F28A = 0;
        data_03002818->counter = data_03002818->ready = 0;
        /* The ROM stores each of the pair twice: 0x0C04, 0x0994, 0x0C04,
         * 0x0994 at 0x080803F0-0x080803FA. */
        data_03002818->block_98c.field_08 = data_03002818->block_bfc.field_08 = 0;
        data_03002818->block_98c.field_08 = data_03002818->block_bfc.field_08 = 0;
        func_080753C8();
        func_08075620(0, data_03002818->unit, 0, 1);
        x = data_03002818->target_x / 8;
        y = data_03002818->target_y / 8;
        data_03002818->marker_x = x;
        data_03002818->marker_y = y;
        func_0804C524(data_03000E30.entries, 25, 0, 0, 0, 0, 3,
                      (u32)data_0894EAF4, data_0894EB80, 0x1b0, 0);
        ((EntryFlags080802E4 *)data_03000E30.entries)[25].enabled = 1;
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
        data_03002818->submode = 2;
        *state = 35;
        break;
    }
    case 2:
        if (data_03002730.flags[2] == 0xff) {
            data_03002818->submode = 0;
            data_03002818->saved_mode = data_03002818->mode;
            data_03002818->counter = 0;
            data_03002818->mode = 3;
            func_0801174C(data_03002818->window, 1, 0x15, data_03000990,
                          data_03000E80, 2, 6, 0x18, 4, 0x30d);
            if (data_03002818->field_960 == 0)
                *state = 6;
            else
                *state = 7;
        }
        break;
    case 26: {
        u16 value = func_080C9314(data_03002818->unit);

        data_03002818->saved_submode = data_03002818->submode;
        data_03002818->submode = 0;
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->counter = 0;
        data_03002818->mode = 3;
        func_08019A8C(data_02003CB0, value, data_03000990, data_03000E80);
        *state = 27;
        break;
    }
    case 27:
        if (func_08011860()) {
            data_03002818->field_42b = 10;
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->submode = data_03002818->saved_submode;
            data_03002818->timer = 15;
            *state = 28;
        }
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        break;
    case 28:
        data_03000000.held = 0;
        data_03000000.repeated = 0;
        data_03000000.pressed = 0;
        if (data_03002818->timer != 0) {
            data_03002818->timer--;
            data_03000000.held = 0;
            data_03000000.pressed = 0;
        } else {
            data_03002818->submode = 2;
            *state = 2;
        }
        break;
    case 6:
        if (func_08011860() == 0)
            break;
        data_03002818->wait = 0;
        func_08013364();
        choice = func_08013380();
        if (choice == -1) {
            data_0200F288 = 2;
            *state = 1;
        } else if (choice == 0) {
            func_081443FC(g_state_02000000.character, data_03002818->unit,
                          sizeof(Unit080802E4));
            func_080D2F2C();
            switch (data_03002818->unit->type) {
            case 10:
                func_080C9574(0x258, 1);
                break;
            case 9:
                func_080C9574(0x259, 1);
                break;
            case 4:
                func_080C9574(0x25a, 1);
                break;
            case 12:
                func_080C9574(0x25b, 1);
                break;
            case 0x5e:
                func_080C9574(0x25c, 1);
                break;
            }
            if (data_03002818->field_962_0)
                func_08141520(8);
            func_0801174C(data_03002818->window, 1, 0x16, data_03000990,
                          data_03000E80, 2, 6, 0x18, 4, 0x30d);
            data_03002818->field_43c = 0x18;
            *state = 9;
        } else {
            if (data_03002818->field_962_0)
                func_08141520(0x9e);
            func_0801174C(data_03002818->window, 1, 0x17, data_03000990,
                          data_03000E80, 2, 6, 0x18, 4, 0x30d);
            data_03002818->field_43c = 2;
            *state = 10;
        }
        break;
    case 7:
        if (func_08011860() == 0)
            break;
        data_03002818->wait = 0;
        func_08013364();
        choice = func_08013380();
        if (choice == -1) {
            data_0200F288 = 2;
            *state = 1;
        } else if (choice == 0) {
            count = 0;
            for (i = 0; i < 24; i++) {
                if (g_state_02000000.units[i].type)
                    count++;
            }
            if (count < 24) {
                func_081443FC(g_state_02000000.character, data_03002818->unit,
                              sizeof(Unit080802E4));
                func_080D2F2C();
                switch (data_03002818->unit->type) {
                case 10:
                    func_080C9574(0x258, 1);
                    break;
                case 9:
                    func_080C9574(0x259, 1);
                    break;
                case 4:
                    func_080C9574(0x25a, 1);
                    break;
                case 12:
                    func_080C9574(0x25b, 1);
                    break;
                case 0x5e:
                    func_080C9574(0x25c, 1);
                    break;
                }
                if (data_03002818->field_962_0)
                    func_08141520(8);
                data_03002818->field_43c = 0x18;
                data_03002818->wait = 0;
                *state = 11;
            } else {
                if (data_03002818->field_962_0)
                    func_08141520(0x9e);
                func_0801174C(data_03002818->window, 1, 0x2b, data_03000990,
                              data_03000E80, 2, 6, 0x18, 4, 0x30d);
                data_03002818->field_43c = 2;
                *state = 10;
            }
        } else {
            data_03002818->field_43c = 2;
            data_03002818->wait = 0;
            *state = 11;
        }
        break;
    case 8:
        /* The tree tests 8 by itself (0x08080328) and sends it to the exit. */
        break;
    case 9:
        /* Both short arms count on.  The ROM has one copy of the count
         * (0x08080B18, shared with case 10 by cross-jumping), reached from
         * the tests at 0x08080AB6 and 0x08080AC6 with the loaded byte still
         * in r2 and its address in r3. */
        func_08011860();
        if (data_03002818->wait < 60)
            data_03002818->wait++;
        else if (data_03002818->wait > 90 || (data_03000000.pressed & 3)) {
            data_03002818->wait = 0;
            func_08013364();
            *state = 11;
        } else
            data_03002818->wait++;
        break;
    case 10:
        func_08011860();
        if (data_03002818->wait < 80)
            data_03002818->wait++;
        else if (data_03002818->wait > 90 || (data_03000000.pressed & 3)) {
            data_03002818->wait = 0;
            func_08013364();
            *state = 11;
        } else
            data_03002818->wait++;
        break;
    case 11:
        if (data_03002818->wait++ > 60) {
            func_08013364();
            data_0200F288 = 0xfe;
            *state = 25;
        }
        func_08011860();
        break;
    case 35:
        if (data_03002818->counter++ > 10) {
            func_0808A604(3, 2);
            data_03002730.flags[5] = 3;
            func_080748AC(data_03002818->unit);
            data_03002818->step = 8;
            data_0200F288 = 2;
            *state = 24;
        }
        break;
    case 1:
        data_03002818->submode = 2;
        func_08006ADC(&data_03002730, 2, (u32)func_0807F7B4);
        *state = data_0200F288;
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
            func_08006ADC(&data_03002730, 2, (u32)func_0807F7B4);
            *state = data_0200F288;
        }
        func_08087554(8, data_03002818->step);
        break;
    case 25:
        data_03002818->timer = (data_03002818->timer + 1) % 240;
        if (++data_03002818->step == 8)
            *state = data_0200F288;
        func_08087554(8, data_03002818->step);
        break;
    case 0xfe:
        if (data_03002818->counter++ > 10) {
            /* CpuFill16(0, data_03002818->unit, sizeof(Unit080802E4)): the
             * SDK's vu16 temporary, spelled through a pointer until
             * fftadecomp-kit#164, in the text of src/0807B858.c.  The ROM
             * forms the slot address before the zero (0x08080CDA-0x08080CDE). */
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_03002818->unit, 0x01000084);
            data_03002730.flags[5] = 0xfe;
            *state = 0xff;
        }
        break;
    case 0xff:
        data_03002818->saved_phase = 0xfe;
        break;
    }
}
