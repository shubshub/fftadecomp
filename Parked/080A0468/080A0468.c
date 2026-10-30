#include "ffta.h"

typedef struct {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    s16 field_06;
    s16 field_08;
    s16 field_0a;
    s16 field_0c;
    s16 field_0e;
    s16 field_10;
    s16 field_12;
} Struct080A0468;

extern s32 func_081426B8(s32 numerator, s32 denominator);

/* 0x080A0468..0x080A04E8: complete 128-byte target.
 * 70b5041c049821806280a380e0800420215e0022a05e0d1a0620215e0222a05e0e1a
 * 2b1c002d00da6b422382321c002e00da7242628219041004814201db638100e06281
 * 60890004401400212081a181e181002d07d0291c002900da4942281ca2f0f6f8a081
 * 002e07d0311c002900da4942301ca2f0ecf8e08170bc01bc0047
 */
void func_080A0468(void *object, s16 first, s16 second,
                   s16 third, s16 fourth)
{
    Struct080A0468 *state = object;
    s32 first_difference;
    s32 second_difference;

    state->field_00 = first;
    state->field_02 = second;
    state->field_04 = third;
    state->field_06 = fourth;
    first_difference = state->field_04 - state->field_00;
    second_difference = state->field_06 - state->field_02;
    state->field_10 = first_difference < 0 ? -first_difference : first_difference;
    state->field_12 = second_difference < 0 ? -second_difference : second_difference;
    if (state->field_10 >= state->field_12)
        state->field_0a = state->field_10;
    else
        state->field_0a = state->field_12;
    state->field_08 = state->field_0a >> 1;
    state->field_0c = 0;
    state->field_0e = 0;
    if (first_difference != 0)
        state->field_0c = func_081426B8(first_difference,
            first_difference < 0 ? -first_difference : first_difference);
    if (second_difference != 0)
        state->field_0e = func_081426B8(second_difference,
            second_difference < 0 ? -second_difference : second_difference);
}
