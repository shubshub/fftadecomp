#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit0807F168;

typedef struct {
    u32 unknown_00[3];
    u16 field_0c;
    u16 unknown_0e;
} Block0807F168;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u16 step;
    u8 unknown_0028[0x402];
    u8 saved_submode;
    u8 field_42b;
    u8 unknown_042c[0xa];
    s16 marker_x, marker_y;
    u8 mode;
    u8 saved_mode;
    u8 unknown_043c[8];
    u32 field_444;
    u8 unknown_0448[5];
    u8 field_44d;
    u8 unknown_044e;
    u8 saved_phase;
    u8 unknown_0450[2];
    u8 changed;
    u8 unknown_0453;
    const u8 *field_454;
    s16 offset_x, offset_y;
    u8 unknown_045c[0x530];
    Block0807F168 block_98c;
    u8 unknown_099c[0x254];
    s16 target_x, target_y;
    u8 unknown_0bf4;
    u8 ready;
    u8 unknown_0bf6[6];
    Block0807F168 block_bfc;
    u16 counter;
    u8 unknown_0c0e[0xe];
    u8 entry_mode;
    u8 unknown_0c1d[0x3f];
    u16 entries[6];
    u8 unknown_0c68[0x109c];
    u8 submode;
    u8 unknown_1d05[4];
    u8 field_1d09;
    u8 unknown_1d0a[2];
    Unit0807F168 *unit;
} State0807F168;

typedef struct {
    u32 unknown_00;
    u8 *entries;
} Display0807F168;

typedef struct {
    u8 unknown_00[0x14];
    u16 enabled;
    u8 unknown_16[6];
} EntryFlags0807F168;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState0807F168;

typedef struct {
    u8 unknown_00[0x35];
    u8 y;
    u8 unknown_36[0x16];
} TileRenderer0807F168;

extern State0807F168 *data_03002818;
extern Table data_03002730;
extern Display0807F168 data_03000E30;
extern InputState0807F168 data_03000000;
extern TileRenderer0807F168 data_030009E0[];
extern Unit0807F168 *data_030027F4;
extern u32 data_030027D4;
extern u8 data_02003CB0[];
extern u8 data_06014300[];
extern u8 data_0894EAF4[];
extern u8 data_0894EB80[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
/* 0x0200F242..0x0200F245 are named by this function's literal pools only. */
extern u8 data_0200F242;
extern u8 data_0200F243;
extern u8 data_0200F244;
extern u8 data_0200F245;

extern void func_08073380(u32 value);
extern void func_08079690(u32 mode);
extern void func_080753C8(void);
extern void func_08075620(u32, Unit0807F168 *, u32, u32);
extern void func_0804C524(u8 *, u16, u32, u8, u8, u32, u8, u32, u8 *, u16,
                          u8);
extern void func_0804C788(u8 *base, u16 index, u8 lo, u8 hi);
extern u8 func_080CB7C0(Unit0807F168 *unit, u8 selector);
extern const u8 *func_080CB808(Unit0807F168 *unit);
extern u8 *func_080CB868(u8 *buffer, Unit0807F168 *unit);
extern void func_080CB8D4(void *object, u8 index);
extern const u8 *func_080CB928(Unit0807F168 *unit);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u8 func_080C8240(void *data);
extern u16 func_080C9314(const void *data);
extern void func_08019A8C(void *context, u16 value, void *first, void *second);
extern u16 func_08011860(void);
extern void func_0808A604(u8, u8);
extern void func_080748AC(void *state);
extern void func_08141540(u16 song_id);
extern void func_08087554(u8 period, u8 phase);
extern void func_0807F7B4(u32, u8 *);

/* An inlined copy of func_08080E80 (src/08080E80.c).  The ROM has the
 * operation out of line at 0x08080E80 and inlined here at
 * 0x0807F1E8-0x0807F204, where the loop reloads the 0xC5C offset on every
 * pass (ldr r5 at 0x0807F1F8); written out in the caller, the same text
 * loads that offset once in front of the loop, as 0x08080E80 itself does. */
static inline void clear_entries(u8 mode)
{
    int i;

    data_03002818->entry_mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}

/* Complete [0x0807F168, 0x0807F7B4): 1612 bytes, 606 instructions. */
void func_0807F168(u32 index, u8 *state)
{
    u16 value;

    switch (*state) {
    case 0: {
        int x, y;
        u8 *buffer = data_02003CB0;
        const u8 *resource;

        func_08073380(index);
        data_03002818->unit = data_030027F4;
        data_03002818->block_bfc = data_03002818->block_98c;
        clear_entries(0);
        data_03002818->field_44d = 1;
        func_08079690(1);
        data_03002818->block_bfc.field_0c = 0;
        data_0200F244 = data_0200F245 = 0;
        data_03002818->counter = data_03002818->ready = 0;
        func_080753C8();
        func_08075620(1, data_03002818->unit, 0, 1);
        x = data_03002818->target_x / 8;
        y = data_03002818->target_y / 8;
        data_03002818->marker_x = x;
        data_03002818->marker_y = y;
        data_03002818->mode = 3;
        func_0804C524(data_03000E30.entries, 25, 0, 0, 0, 0, 3,
                      (u32)data_0894EAF4, data_0894EB80, 0x1b0, 0);
        ((EntryFlags0807F168 *)data_03000E30.entries)[25].enabled = 1;
        data_03002818->marker_x = 120;
        data_03002818->marker_y = -8;
        data_03002818->offset_x = -64;
        data_03002818->offset_y = 56;
        data_03002818->changed = 3;
        data_03002818->field_1d09 = data_03002818->unit->flags & 0x1c;
        data_03002818->field_1d09 |= 1;
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
            data_03002818->counter = 0;
            data_0200F242 = 0xfe;
            *state = 25;
        }
        break;
    case 26:
        value = func_080C9314(data_03002818->unit);
        data_03002818->saved_submode = data_03002818->submode;
        data_03002818->submode = 0;
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->counter = 0;
        data_03002818->mode = 3;
        func_08019A8C(data_02003CB0, value, data_03000990, data_03000E80);
        *state = 27;
        break;
    case 27:
        if (func_08011860()) {
            data_03002818->marker_y -= 128;
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
            *state = 2;
        }
        break;
    case 35:
        if (data_03002818->counter++ > 10) {
            func_0808A604(3, 2);
            if (data_030027D4 != 0) {
                data_03002818->field_444 = data_030027D4;
                data_03002730.flags[5] = 4;
            } else {
                data_03002730.flags[5] = 3;
            }
            func_080748AC(data_03002818->unit);
            data_03002818->step = 8;
            data_0200F243 = 0;
            data_0200F242 = 2;
            *state = 24;
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
            func_08006ADC(&data_03002730, 2, (u32)func_0807F7B4);
            *state = data_0200F242;
            data_0200F242 = data_0200F243;
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
            *state = data_0200F242;
            data_0200F242 = data_0200F243;
        }
        func_08087554(8, data_03002818->step);
        break;
    case 0xfe:
        if (data_03002818->counter++ > 10) {
            if (data_030027D4 == 0)
                data_03002730.flags[5] = 0xfe;
            *state = 0xff;
        }
        break;
    case 0xff:
        data_03002818->saved_phase = 0xfe;
        break;
    }
}
