#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA];
    s8 coordinate_A;
    s8 coordinate_B;
} Record080D8C58;

extern void *func_080A880C(void *record);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                         s16 *firstOutput, s16 *secondOutput, s16 *thirdOutput);
extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *firstOutput, s16 *secondOutput);

/* 0x080D8C58..0x080D8CD2:
 * 70 B5 56 46 4D 46 44 46 70 B4 85 B0 8A 46 91 46
 * 6E 46 0A 36 03 A9 88 46 04 AC 6D 46 12 35 CF F7
 * C9 FD 0A 21 41 56 21 80 0B 21 41 56 29 80 20 78
 * 09 06 09 0E 43 F7 C4 FF 01 1C 09 06 09 0E 00 22
 * A0 5E 00 23 EA 5E 00 96 44 46 01 94 02 AB 43 F7
 * E7 FE 02 A8 00 21 40 5E 00 22 B1 5E 00 23 E2 5E
 * 4C 46 00 94 53 46 43 F7 61 FE 05 B0 38 BC 98 46
 * A1 46 AA 46 70 BC 01 BC 00 47. */
void func_080D8C58(void *input, s16 *firstOutput, s16 *secondOutput)
{
    s16 first;
    s16 second;
    s16 third;
    s16 coordinates[2];
    Record080D8C58 *record = func_080A880C(input);
    u8 value;

    coordinates[0] = record->coordinate_A;
    coordinates[1] = record->coordinate_B;
    value = func_0801CC18(coordinates[0], coordinates[1]);
    func_0801CA78(coordinates[0], value, coordinates[1],
                  &first, &second, &third);
    func_0801C984(first, second, third,
                  firstOutput, secondOutput);
}
