/* Target: [0x08042E48, 0x08042EB8), 112 bytes.
 * f0b557464e464546e0b4061c09040c0cd4f77afe4004717d8846b768050c002d1dd0
 * c146114b9a46f17d4900201cfff06bfd0004040c414661434900f0684018391c4a46
 * 53461a40fef0ecfcb07f40003f18013d601c0004040c002de4d138bc9846a146aa46
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
} Record08042E48;

extern u16 func_08017B50(Record08042E48 *state);
extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08042E48(Record08042E48 *state, u16 selection)
{
    u16 remaining = (u16)(func_08017B50(state) * 2);
    s32 width = state->field_15;
    u16 *destination = state->field_08;

    while (remaining != 0) {
        selection = func_08142950(selection, state->field_17 * 2);
        func_0814186C(state->field_0C + selection * width, destination,
                      width & 0x1FFFFF);
        destination += state->field_1E;
        remaining--;
        selection++;
    }
}
