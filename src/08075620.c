#include "ffta.h"

/* Complete target [0x08075620, 0x08075E24): 2052 bytes, 835 instructions.
 * Draws a unit's status panel: name and job text, HP/MP with gauges, the
 * unit fields at 0xD6, 0x09, 0x0A, 0x103 and 0x102, the eight stat values that
 * func_0807614C (src/0807614C.c) later compares against, and the unit number.
 * The unit number is an unsigned division by the 0x108-byte unit size; it
 * compiles to __udivsi3 (func_08142AB0, the libgcc runtime). */

typedef struct {
    u8 unknown_00[9];
    u8 level;
    u8 unknown_0A;
    u8 unknown_0B[0x0D];
    u16 hp;
    u16 max_hp;
    u16 mp;
    u16 max_mp;
    u8 unknown_20[8];
    u16 flags;
    u8 unknown_2A[0xAC];
    u16 unknown_D6;
    u8 unknown_D8[0x2A];
    u8 unknown_102;
    u8 unknown_103;
    u8 unknown_104[4];
} Unit08075620;

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

typedef struct {
    u8 unknown_0000[0x44C];
    u8 unknown_44C;
    u8 mode;
    u8 unknown_044E[0x68C - 0x44E];
    u8 text[0x1CEC - 0x68C];
    s16 value_1cec;
    s16 value_1cee;
    s16 value_1cf0;
    u8 unknown_1cf2[6];
    s16 value_1cf8;
    s16 value_1cfa;
    s16 value_1cfc;
    s16 value_1cfe;
    s16 value_1d00;
} State08075620;

typedef struct {
    u8 unknown_00[0x5C];
    s16 unknown_5C;
} Member08075620;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ScriptControl;

extern State08075620 *data_03002818;
extern TileRenderer data_030009E0[];
extern ScriptControl g_state_0200F390;
extern Unit08075620 g_state_02000080[];
extern const u8 *const g_table_08526680[];
extern const u16 data_0894F7DC[];
extern u8 data_0600AEE0[];
extern u8 data_0600B1E0[];

extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u32 func_080C92F0(void *unit, u32 selector);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 style, u32 spacing);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035A68(u16 *destination, u16 count, u32 value, u16 base);
extern void func_080896C0(void *buffer, u16 first, u16 second, u16 third);
extern void func_08035578(const u16 *source, u16 *destination, u32 count, u16 offset);
extern void func_080899AC(u32 position, u8 stride, u32 spacing, u16 value,
                          u32 digits, u32 alignment, u16 tile);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern s32 func_080CA394(void *unit);
extern s32 func_080CA610(void *unit);
extern s32 func_080CA5C4(void *unit);
extern s32 func_080CA520(void *unit);
extern s32 func_080CA550(void *unit);
extern s32 func_080CA538(void *unit);
extern s32 func_080CA568(void *unit);
extern s32 func_080CA580(void *unit);
extern u8 func_080CDBE4(void *unit);
extern u8 func_080CDBFC(void *unit);
extern u8 func_080CDC44(void *unit);
extern u8 func_080CDC5C(void *unit);
extern u8 func_080CDC14(void *unit);
extern u8 func_080CDC2C(void *unit);
extern u8 func_080CDC74(void *unit);
extern u8 func_080CDC8C(void *unit);
extern u8 func_080CDA34(void *unit);
extern u8 func_080C95A8(u16 index);
extern u8 func_08133BC4(void *unit);
extern u8 func_080C832C(void *unit);
extern void func_08075574(void);
extern void *func_08096D7C(void);
extern Member08075620 *func_08099560(void *owner, void *unit);
extern u32 func_08099CC4(void *owner);
extern u32 func_08099CD0(void *owner);
extern void *func_08099544(void *owner);

void func_08075620(s32 mode, Unit08075620 *unit, s32 redraw, s32 numbered)
{
    u16 blank_name;
    u16 blank_job;
    const void *text;
    u32 value;
    u32 max;
    u16 tile;
    u16 kind;

    if (redraw == 0) {
        text = (const void *)func_080C7EA4(unit, 0);
        blank_name = 0;
        func_0814186C(&blank_name, data_0600AEE0, 0x01000180);
        func_08015110(data_03002818->text, data_0600AEE0, text, 0, 1);
    }
    if (redraw != 1) {
        value = func_080C92F0(unit, 0);
        text = g_table_08526680[value];
        blank_job = 0;
        func_0814186C(&blank_job, data_0600B1E0, 0x01000180);
        func_08015110(data_03002818->text, data_0600B1E0, text, 0, 1);
    }

    value = unit->hp;
    max = unit->max_hp;
    func_08035A68(func_0808B8E4(2, 1, 22, 1), 3, value, value != 0 ? 0xf000 : 0xa000);
    func_08035A68(func_0808B8E4(2, 1, 26, 1), 3, max, 0xf000);
    func_080896C0(func_0808B8E4(2, 1, 21, 2), max, value, 0);

    value = unit->mp;
    max = unit->max_mp;
    func_08035A68(func_0808B8E4(2, 1, 22, 3), 3, value, value != 0 ? 0xf000 : 0xa000);
    func_08035A68(func_0808B8E4(2, 1, 26, 3), 3, max, 0xf000);
    func_080896C0(func_0808B8E4(2, 1, 21, 4), max, value, 1);

    value = unit->unknown_D6;
    func_08035A68(func_0808B8E4(2, 1, 23, 5), 2, value, value != 0 ? 0xf000 : 0xa000);
    value = unit->level;
    func_08035A68(func_0808B8E4(2, 1, 2, 6), 2, value, 0xf000);
    value = unit->unknown_0A;
    func_08035A68(func_0808B8E4(2, 1, 6, 6), 2, value, 0xf000);
    value = unit->unknown_103;
    func_08035A68(func_0808B8E4(2, 1, 11, 1), 1, value, 0xf000);
    value = unit->unknown_102;
    func_08035A68(func_0808B8E4(2, 1, 15, 1), 1, value, 0xf000);

    if (mode != 3) {
        func_08035578(data_0894F7DC, data_030009E0[3].second_plane, 0xc0, 0xfe);

        data_03002818->value_1cec = func_080CA394(unit);
        func_080899AC((u32)func_0808B8E4(3, 1, 6, 1), data_030009E0[3].stride, 100,
                      data_03002818->value_1cec, 1, 0, 0xd000);
        data_03002818->value_1cee = func_080CA610(unit);
        func_080899AC((u32)func_0808B8E4(0, 1, 6, 9), 0x20, 120,
                      data_03002818->value_1cee, 1, 0, 0xd000);
        data_03002818->value_1cf0 = func_080CA5C4(unit);
        func_080899AC((u32)func_0808B8E4(3, 1, 12, 2), data_030009E0[3].stride, 120,
                      data_03002818->value_1cf0, 3, 0, 0xd000);

        if (func_080CDBE4(unit) && !func_080CDBFC(unit))
            tile = 0x8000;
        else if (!func_080CDBE4(unit) && func_080CDBFC(unit))
            tile = 0xa000;
        else
            tile = 0xd000;
        data_03002818->value_1cf8 = func_080CA520(unit);
        func_080899AC((u32)func_0808B8E4(3, 1, 11, 4), data_030009E0[3].stride, 120,
                      data_03002818->value_1cf8, 3, 0, tile);

        if (func_080CDC44(unit) && !func_080CDC5C(unit))
            tile = 0x8000;
        else if (!func_080CDC44(unit) && func_080CDC5C(unit))
            tile = 0xa000;
        else
            tile = 0xd000;
        data_03002818->value_1cfa = func_080CA550(unit);
        func_080899AC((u32)func_0808B8E4(3, 1, 11, 6), data_030009E0[3].stride, 100,
                      data_03002818->value_1cfa, 3, 0, tile);

        if (func_080CDC14(unit) && !func_080CDC2C(unit))
            tile = 0x8000;
        else if (!func_080CDC14(unit) && func_080CDC2C(unit))
            tile = 0xa000;
        else
            tile = 0xd000;
        data_03002818->value_1cfc = func_080CA538(unit);
        func_080899AC((u32)func_0808B8E4(0, 1, 11, 14), 0x20, 120,
                      data_03002818->value_1cfc, 3, 0, tile);

        if (func_080CDC74(unit) && !func_080CDC8C(unit))
            tile = 0x8000;
        else if (!func_080CDC74(unit) && func_080CDC8C(unit))
            tile = 0xa000;
        else
            tile = 0xd000;
        data_03002818->value_1cfe = func_080CA568(unit);
        func_080899AC((u32)func_0808B8E4(3, 1, 11, 9), data_030009E0[3].stride, 100,
                      data_03002818->value_1cfe, 3, 0, tile);

        if (func_080CDA34(unit))
            tile = 0xa000;
        else
            tile = 0xd000;
        data_03002818->value_1d00 = func_080CA580(unit);
        func_080899AC((u32)func_0808B8E4(0, 1, 11, 17), 0x20, 120,
                      data_03002818->value_1d00, 3, 0, tile);

        if (data_03002818->unknown_44C != 4 && mode == 1) {
            kind = func_080C95A8(0x33);
            if (kind >= 1 && kind <= 5) {
                if (func_08133BC4(unit) == 1 && data_03002818->mode != 4
                    && !(unit->flags & 0xb000)) {
                    u32 number = ((u32)unit - (u32)g_state_02000080) / sizeof(Unit08075620) + 1;

                    func_08035678(0xd0bf, func_0808B8E4(0, 1, 26, 19), 2, 1);
                    func_08035A68(func_0808B8E4(0, 1, 28, 19), 2, number, 0xf000);
                }
                if (func_080C832C(unit))
                    *func_0808B8E4(2, 1, 28, 5) = 0xd154;
                else
                    *func_0808B8E4(2, 1, 28, 5) = 0;
            } else if (g_state_0200F390.flags & 2) {
                /* The ROM keeps two copies of the unit-number and
                 * func_080C832C blocks (0x08075B58, 0x08075D2C); this
                 * branch's copy joins the first one at 0x08075C54, which
                 * branches to 0x08075B6C. */
                func_08075574();
                func_08035678(0xc152, func_0808B8E4(3, 1, 7, 0), 2, 1);
                func_08035678(0xd091, func_0808B8E4(3, 1, 12, 0), 1, 1);
                if (numbered && func_08133BC4(unit) == 1 && data_03002818->mode != 4
                    && !(unit->flags & 0xb000)) {
                    u32 number = ((u32)unit - (u32)g_state_02000080) / sizeof(Unit08075620) + 1;

                    func_08035678(0xd0bf, func_0808B8E4(0, 1, 26, 19), 2, 1);
                    func_08035A68(func_0808B8E4(0, 1, 28, 19), 2, number, 0xf000);
                }
                if (func_080C832C(unit))
                    *func_0808B8E4(2, 1, 28, 5) = 0xd154;
                else
                    *func_0808B8E4(2, 1, 28, 5) = 0;
            } else {
                void *owner = func_08096D7C();
                s16 member = func_08099560(owner, unit)->unknown_5C;
                s16 shown;
                u16 total;

                if (member == -1)
                    shown = 0;
                else
                    shown = member + 1;
                total = func_08099CC4(owner) + func_08099CD0(owner);
                if (func_08099544(func_08096D7C()))
                    total++;
                func_08035A68(func_0808B8E4(3, 1, 10, 0), 2, shown,
                              shown != 0 ? 0xf000 : 0xa000);
                func_08035A68(func_0808B8E4(3, 1, 13, 0), 2, total,
                              total != 0 ? 0xf000 : 0xa000);
                func_08035678(0xd062, func_0808B8E4(3, 1, 7, 0), 2, 1);
                func_08035678(0xd091, func_0808B8E4(3, 1, 12, 0), 1, 1);
                if (numbered && func_08133BC4(unit) == 1 && data_03002818->mode != 4
                    && !(unit->flags & 0xb000)) {
                    u32 number = ((u32)unit - (u32)g_state_02000080) / sizeof(Unit08075620) + 1;

                    func_08035678(0xd0bf, func_0808B8E4(0, 1, 26, 19), 2, 1);
                    func_08035A68(func_0808B8E4(0, 1, 28, 19), 2, number, 0xf000);
                }
                if (func_080C832C(unit))
                    *func_0808B8E4(2, 1, 28, 5) = 0xd154;
                else
                    *func_0808B8E4(2, 1, 28, 5) = 0;
            }
        }
    }

    if (unit->unknown_D6 > 9)
        *func_0808B8E4(2, 1, 26, 5) = 0xd090;
    else
        *func_0808B8E4(2, 1, 26, 5) = 0;
}
