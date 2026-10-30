#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    const u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 value_16;
    u8 field_17;
    s16 value_18;
    u16 value_1A;
    u8 unknown_1C[2];
    u8 destination_stride;
} Record080401F4;

extern u16 func_08017B50(Record080401F4 *state);
extern s32 func_08142950(s32 numerator, s32 denominator);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x080401F4, 0x08040264), 112 bytes.
 * f0b557464e464546e0b4061c09040c0cd7f7a4fc4004717d8846b768050c002d1dd0
 * c146114b9a46f17d4900201c02f195fb0004040c414661434900f0684018391c4a46
 * 53461a4001f116fbb07f40003f18013d601c0004040c002de4d138bc9846a146aa46
 * f0bc01bc0047ffff1f00
 */
void func_080401F4(Record080401F4 *state, u16 index)
{
    s32 remaining = (u16)(func_08017B50(state) * 2);
    u32 width = state->width;
    u16 *destination = state->destination;

    while (remaining != 0) {
        index = func_08142950(index, state->field_17 * 2);
        func_0814186C(state->source + index * width, destination,
                      width & 0x1FFFFF);
        destination += state->destination_stride;
        remaining--;
        index++;
    }
}
