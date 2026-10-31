#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *unknown_08;
    u16 *unknown_0C;
    u8 unknown_10[5];
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
    s16 unknown_18;
    u16 unknown_1A;
    u16 unknown_1C;
    u8 unknown_1E;
    u8 unknown_1F;
} State08081B24;

extern u16 func_08017B50(State08081B24 *state);
extern s32 func_08142950(s32 value, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete target [0x08081B24,0x08081BEC),200 bytes:
 * f0b557464e464546e0b40e1cf768f07f0003b18b40180004040c13239846f07d
 * 00281dd0013884464046002812d03b1c4546211c481c0004040c221c1980717d
 * 4900c918501c0004040c0a800233013d002deed1707d80003f1860460028e1d1
 * 708b4004040c301c95f7e0ff4004717d8846b768050c002d1dd0c146114b9a46
 * f17d4900201cc0f0d1fe0004040c414661434900f0684018391c4a4653461a40
 * bff052feb07f40003f18013d601c0004040c002de4d138bc9846a146aa46f0bc
 * 01bc0047ffff1f00
 */
void func_08081B24(void *unknown, State08081B24 *state)
{
    u16 *rows = state->unknown_0C;
    u16 tile = (state->unknown_1F << 12) + state->unknown_1C;
    s32 row;
    s32 column;
    u16 *cursor;
    u16 frame;
    s32 count;
    u32 width;
    u16 *destination;

    for (row = state->unknown_17; row != 0; row--) {
        cursor = rows;
        for (column = 19; column != 0; column--) {
            *cursor = tile++;
            cursor[state->unknown_15] = tile++;
            cursor++;
        }
        rows += state->unknown_15 * 2;
    }

    frame = state->unknown_1A * 2;
    count = (u16)(func_08017B50(state) * 2);
    width = state->unknown_15;
    destination = state->unknown_08;
    while (count != 0) {
        frame = func_08142950(frame, state->unknown_17 * 2);
        func_0814186C(state->unknown_0C + frame * width,
                     destination, width & 0x1FFFFF);
        destination += state->unknown_1E;
        count--;
        frame++;
    }
}
