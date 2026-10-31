#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2E];
    s16 inputs[3];
    u8 unknown_34[4];
    u16 value_38;
    u8 unknown_3A[4];
    s16 first_values[3];
    s16 second_values[3];
    u16 stored_values[3];
    s16 counters[3];
} Record080A9B00;

extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output);

/* 0x080A9B00..0x080A9BB8, complete 184-byte target:
 * F0 B5 47 46 80 B4 82 B0 05 1C 2E 21 68 5E 30 22
 * A9 5E 32 23 EA 5E 6C 46 06 34 00 94 01 AB 72 F7
 * 31 FF 00 23 26 1C 50 24 64 19 A0 46 01 AC B4 46
 * 5A 00 28 1C 50 30 80 18 00 27 C0 5F 06 28 35 DC
 * 00 28 12 DD 28 1C 3E 30 80 18 00 27 C1 5F 00 27
 * E0 5F 81 42 09 D1 28 1C 44 30 80 18 00 22 81 5E
 * 67 46 00 22 B8 5E 81 42 20 D0 01 33 02 2B DF DD
 * 00 23 5A 00 44 46 A1 18 00 27 C8 5F 00 28 12 DC
 * 08 20 08 80 29 1C 3E 31 89 18 01 A8 00 88 08 80
 * 28 1C 44 30 80 18 31 88 01 80 28 1C 4A 30 80 18
 * 29 8F 01 80 02 E0 01 33 02 2B E2 DD 02 B0 08 BC
 * 98 46 F0 BC 01 BC 00 47
 */
void func_080A9B00(Record080A9B00 *record)
{
    s16 first_output;
    s16 second_output;
    s32 i;

    func_0801C984(record->inputs[0], record->inputs[1], record->inputs[2],
                  &first_output, &second_output);
    for (i = 0; i < 3; i++) {
        if (record->counters[i] > 6)
            return;
        if (record->counters[i] > 0 &&
            record->first_values[i] == first_output &&
            record->second_values[i] == second_output)
            return;
    }
    for (i = 0; i < 3; i++) {
        if (record->counters[i] <= 0) {
            record->counters[i] = 8;
            record->first_values[i] = first_output;
            record->second_values[i] = second_output;
            record->stored_values[i] = record->value_38;
            return;
        }
    }
}
