#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value_18;
    u8 unknown_1A[0xD8];
    u8 counter_F2;
} Unit080A22F0;

typedef struct {
    Unit080A22F0 *unit;
    u8 unknown_04[0x7C];
    void *entries;
} UnitState080A22F0;

typedef struct {
    UnitState080A22F0 *state;
    u16 flags;
    u16 adjustment;
} Update080A22F0;

typedef struct {
    u8 unknown_0000[0x3C2B];
    u8 counter_3C2B;
} Global080A22F0;

extern Global080A22F0 g_state_02000000;
extern u8 func_080C8280(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_0812F17C(void *unit);
extern u8 func_080CD8CC(const void *object);
extern u8 func_080C8240(void *data);
extern void func_08099BAC(UnitState080A22F0 *state);

/* 0x080A22F0..0x080A23B8:
 * 30 B5 04 1C 20 68 00 68 25 F0 C2 FF 00 06 00 28
 * 52 D1 20 68 00 68 13 21 25 F0 CC FD E1 88 00 04
 * 00 14 40 1A 00 04 05 0C 00 28 32 DC 00 25 20 68
 * 00 68 8C F0 2B FF 00 06 00 28 05 D0 A1 88 80 22
 * 12 01 10 1C 08 43 A0 80 A1 88 80 22 52 01 10 1C
 * 08 43 A0 80 20 68 00 68 2B F0 C0 FA 00 06 00 28
 * 14 D1 20 68 00 68 F2 30 01 78 FE 29 00 D8 01 31
 * 01 70 20 68 00 68 25 F0 6B FF 00 06 00 28 05 D0
 * 0F 49 10 48 09 18 08 78 01 30 08 70 20 68 F7 F7
 * 15 FC 20 68 00 68 14 21 25 F0 8C FD 29 04 00 04
 * 81 42 06 DD 20 68 00 68 14 21 25 F0 83 FD 00 04
 * 05 0C 20 68 00 68 05 83 30 BC 01 BC 00 47 00 00
 * 00 00 00 02 2B 3C 00 00. */
void func_080A22F0(Update080A22F0 *update)
{
    s16 value;
    s32 current;

    if (func_080C8280(update->state->unit))
        return;

    current = (s16)func_080C7EA4(update->state->unit, 0x13);
    value = current - update->adjustment;
    if (value <= 0) {
        value = 0;
        if (func_0812F17C(update->state->unit))
            update->flags |= 0x800;
        update->flags |= 0x1000;
        if (!func_080CD8CC(update->state->unit)) {
            u32 count = update->state->unit->counter_F2;

            if (count < 255)
                ++count;
            update->state->unit->counter_F2 = count;
            if (func_080C8240(update->state->unit))
                ++g_state_02000000.counter_3C2B;
        }
        func_08099BAC(update->state);
    }
    if (value > (s16)func_080C7EA4(update->state->unit, 0x14))
        value = (s16)func_080C7EA4(update->state->unit, 0x14);
    update->state->unit->value_18 = value;
}
