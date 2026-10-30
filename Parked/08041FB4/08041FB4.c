/* Target: [0x08041FB4, 0x08042024), 112 bytes.
 * f0b557464e464546e0b4061c09040c0cd5f7c4fd4004717d8846b768050c002d1dd0
 * c146114b9a46f17d4900201c00f1b5fc0004040c414661434900f0684018391c4a46
 * 53461a40fff036fcb07f40003f18013d601c0004040c002de4d138bc9846a146aa46
 * f0bc01bc0047ffff1f00
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *field_08;
    const u16 *field_0C;
    u8 unknown_10[5];
    u8 field_15;
    u8 field_16;
    u8 field_17;
    s16 field_18;
    u8 unknown_1A[4];
    u8 field_1E;
} Record08041FB4;

extern u16 func_08017B50(Record08041FB4 *state);
extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08041FB4(Record08041FB4 *state, u16 selection)
{
    s32 count = (u16)(func_08017B50(state) * 2);
    s32 width = state->field_15;
    u16 *destination = state->field_08;
    s32 row;

    for (row = 0; row < count; row++) {
        selection = func_08142950(selection, state->field_17 * 2);
        func_0814186C(state->field_0C + selection * width, destination,
                      width & 0x1FFFFF);
        destination += state->field_1E;
        selection++;
    }
}
