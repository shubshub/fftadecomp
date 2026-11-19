#include "ffta.h"

/* Complete [0x080CFAD4, 0x080CFCD0): 508 bytes, 228 instructions, an
 * alignment halfword at 0x080CFBBA and five literal words (0x0836D4B8,
 * 0x02002CC0, 0x08565416, 0x0000059F, 0x00000581).
 * f0b557464e464546e0b483b082460906090e35480268504672f0aefb00200190
 * 3249894600220092012302221d20804648464178181c0840002808d0101c0840
 * 002804d0009801300006000e00900121494288440c20814441460029e8da009a
 * 1e2a01d91e2300930620804641464800404480001d4940188146262041464143
 * 1b480f18424615324b46597801200840434601330293002800d19fe008250820
 * 0840002848d01004050c281cf9f712fd0006000e00281dd001380006040e002c
 * 18d0281c211cf9f711fde000001b4000ba78f9780902114372f084fd0f21091a
 * 484681707ae00000b8d43608c02c0002165456084a465178f520084000245070
 * 0b480021f9f7ccfc0a4840440004000c0121f9f7c5fc4b469c70404601305146
 * 087001229244019b01330193029055e09f050000810500000220084000284dd0
 * 1004060c301cf9f7c5fc0006002839d132f7eefd000400146424642172f08efe
 * 00040014009ab918c979641aa04213da4b4658782843587001209870b978301c
 * f9f7b4fc40467f385146087001229244019b0133019321e07c782406250e32f7
 * c7fd00040014640e211c72f067fe28180006050e002d00d10125301c291cf9f7
 * 95fc0be0301cf9f785fc011c0906ff2000060918090e301cf9f788fc02998846
 * 1d2900dc42e7019a1006000e03b038bc9846a146aa46f0bc02bc0847
 */

/* The 12-byte record as src/080D2FD8.c declares it. */
typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 value;
    u8 unknown_03[9];
} Record080D2FD8;

/* A 38-byte row (muls #0x26 at 0x080CFB52).  The halfword at +2 is read
 * unaligned, low byte first and or-ed into the high byte (0x080CFBA4 to
 * 0x080CFBAA); func_080D1218 reads +4/+5 the same way (0x080D13CA). */
typedef struct {
    u8 unknown_00;
    u8 base;
    u16 duration;
    u8 unknown_04[3];
    u8 chance[31];
} __attribute__((packed)) CounterDefinition;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern Record080D2FD8 g_state_02002CC0[];
extern const CounterDefinition g_table_08565416[];

u32 func_08002804(void);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
void func_080C9574(u16 bitIndex, u16 enabled);

/* The counter's base value, byte 1 of a definition row.  The ROM narrows
 * the byte loaded at 0x080CFC6C to u8 again (lsls #24 / lsrs #24 at
 * 0x080CFC6E..0x080CFC70; the halving reuses the shifted value as lsrs #25
 * at 0x080CFC7A).  The same helper as func_080CFA48's counter_base, typed
 * for this file's row struct: the same 18 instructions at
 * [0x080CFA76, 0x080CFAA0) with the same result registers. */
static inline u8 counter_base(const CounterDefinition *definition)
{
    return definition->base;
}

u8 func_080CFAD4(u8 *output, u8 clear_count)
{
    u8 active;
    s32 appended;
    s32 index;
    Record080D2FD8 *record;

    g_callbacks_0836D4B8[0](output, clear_count);
    appended = 0;
    record = g_state_02002CC0;
    active = 0;
    for (index = 0; index < 30; index++, record++) {
        if ((record->flags & 1) && (record->flags & 2))
            active++;
    }
    /* The ROM keeps this clamp (cmp #0x1E / bls / movs / str at
     * 0x080CFB32..0x080CFB3A). */
    if (active > 30)
        active = 30;
    for (index = 6; index < 30; index++) {
        const CounterDefinition *definition;
        s32 counterIndex;

        record = &g_state_02002CC0[index];
        definition = &g_table_08565416[index];
        counterIndex = index + 0x15;
        if (record->flags & 1) {
            if (record->flags & 8) {
                u8 remaining = func_080C95A8(counterIndex);

                if (remaining != 0 && --remaining != 0) {
                    func_080C95C0(counterIndex, remaining);
                    record->value = 15 - (14 * remaining) / definition->duration;
                } else {
                    record->flags &= 0xF5;
                    func_080C9574(0x59F, 0);
                    func_080C9574(0x581 + index, 1);
                    record->value = 0;
                    *output++ = index + 1;
                    appended++;
                }
            } else if (record->flags & 2) {
                if (func_080C95A8(counterIndex) == 0) {
                    s16 roll = (s16)func_08002804() % 100;

                    /* The ROM adds the count to the row before the +7
                     * displacement (adds r1, r7, r2; ldrb r1, [r1, #7] at
                     * 0x080CFC3A). */
                    if (roll < 100 - ((const u8 *)definition + active)[7]) {
                        record->flags |= 8;
                        record->value = 1;
                        func_080C95C0(counterIndex, (u8)definition->duration);
                        *output++ = (index + 1) + 0x80;
                        appended++;
                    } else {
                        u8 amount;

                        amount = counter_base(definition);
                        /* Row 29 (base 255) wraps here: the u8 sum at
                         * 0x080CFC82..0x080CFC86 is (255 + rand % 127) & 0xFF.
                         * Row 29 is a disabled row whose chance[] is 100 for
                         * every active count >= 1 (its own record counts), so
                         * it never starts; this counter only times the next
                         * roll, which always fails. */
                        amount += (s16)func_08002804() % (amount >> 1);
                        if (amount == 0)
                            amount = 1;
                        func_080C95C0(counterIndex, amount);
                    }
                } else {
                    u8 remaining = func_080C95A8(counterIndex);

                    func_080C95C0(counterIndex, --remaining);
                }
            }
        }
    }
    return appended;
}
