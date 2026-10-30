#include "ffta.h"

typedef struct State08122DE8 State08122DE8;

typedef union {
    u8 raw;
    s8 signed_value;
} Value08122DE8;

typedef struct {
    u8 unknown_00;
    Value08122DE8 value;
} Record08122DE8;

extern void func_081263DC(State08122DE8 *state, u8 first, u8 second);

/* 0x08122DE8..0x08122E1C:
 * 00 B5 03 1C 4A 78 01 20 08 56 00 28 07 DA 80 32
 * 12 06 12 0E 18 1C 01 21 03 F0 EC FA 04 E0 4A 78
 * 18 1C 02 21 03 F0 E6 FA 01 48 02 BC 08 47 00 00
 * 15 01 00 00. */
u32 func_08122DE8(State08122DE8 *state, const Record08122DE8 *record)
{
    u8 value = record->value.raw;

    if (record->value.signed_value < 0) {
        value += 0x80;
        func_081263DC(state, 1, value);
    } else {
        func_081263DC(state, 2, record->value.raw);
    }
    return 0x115;
}
