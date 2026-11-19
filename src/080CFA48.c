#include "ffta.h"

/* Complete [0x080CFA48, 0x080CFAD4): 140 bytes, 60 instructions and three
 * literal words (0x02002CB4, 0x085653F0, 0x0000059F).
 * f0b50006000e4200121892001c4fd2192621031c4b431b495b18061c14365178f7200840
 * 002402210843507094705c782406250e32f7c2fe00040014640e211c72f062ff28180006
 * 050e002d00d10125301c291cf9f790fd012303243a1c0c325178201c0840032807d10c32
 * 01331e2bf6dd05480121f9f759fdf0bc01bc0047b42c0002f05356089f050000
 */

/* The 12-byte record as src/080D2FD8.c declares it (ResourceEntry in
 * src/0804EC74.c). */
typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 value;
    u8 unknown_03[9];
} Record080D2FD8;

extern Record080D2FD8 g_state_02002CB4[];
extern const u8 g_table_085653F0[][38];

u32 func_08002804(void);
void func_080C95C0(u16 index, u32 value);
void func_080C9574(u16 bitIndex, u16 enabled);

/* The counter's base value, byte 1 of a definition row.  The ROM narrows
 * the byte loaded at 0x080CFA76 to u8 again (lsls #24 / lsrs #24 at
 * 0x080CFA78..0x080CFA7A; the halving reuses the shifted value as lsrs #25
 * at 0x080CFA84).  func_080CFAD4 repeats the same 18 instructions at
 * [0x080CFC6C, 0x080CFC96) with the same result registers, differing only
 * in the row register and the BL offsets. */
static inline u8 counter_base(const u8 *definition)
{
    return definition[1];
}

void func_080CFA48(u8 index)
{
    Record080D2FD8 *record = &g_state_02002CB4[index];
    const u8 *definition = g_table_085653F0[index];
    u16 counterIndex = index + 20;
    u8 amount;
    s32 scan;

    record->flags &= ~8;
    record->flags |= 2;
    record->value = 0;
    amount = counter_base(definition);
    /* Index 30 (row 29, base 255) wraps: the u8 sum at 0x080CFA8C..0x080CFA90
     * is (255 + rand % 127) & 0xFF.  Row 29 never starts in func_080CFAD4 (its
     * chance is 100 for every active count >= 1), so this counter only times a
     * roll that always fails. */
    amount += (s16)func_08002804() % (amount >> 1);
    if (amount == 0)
        amount = 1;
    func_080C95C0(counterIndex, amount);

    for (scan = 1; scan <= 30; scan++) {
        if ((g_state_02002CB4[scan].flags & 3) != 3)
            return;
    }
    func_080C9574(0x59F, 1);
}
