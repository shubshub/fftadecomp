#include "ffta.h"

// Complete target [0x08080F68,0x08081078), 272 bytes:
// f0b557464e464546e0b486b080460c1c1206120e00921b061b0e0193407d8246
// 051c240624164146488b00194004000cc97d4900c1f0d8fc0004000c68434000
// 4246d1680f186400907f60434000916809180291009bff2b01d1d07f00904146
// 0a8a0221081c10400004000c4042c01781464b460b409946042010402e1c0028
// 00d0023e00204946490004915246520005924b46f31a039300244a4601308246
// b24214da1848844600990d035000c319b21a201c01340199884204da19886046
// 0840284318800233013a002af1d1049ab818029b99180d4a039b1a40c0f012fc
// 05983f184146887f4000029a1218029250460128d0dd06b038bc9846a146aa46
// f0bc01bc00470000ff0f0000ffff1f00

typedef struct {
    u8 unknown_00[8];
    u16 *unknown_08;
    u16 *unknown_0C;
    u16 unknown_10;
    u8 unknown_12[3];
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
    s16 unknown_18;
    u16 unknown_1A;
    u16 unknown_1C;
    u8 unknown_1E;
    u8 unknown_1F;
} State08080F68;

extern s32 func_08142950(s32 value, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 count);

void func_08080F68(State08080F68 *state, s8 offset, u8 palette, u8 count)
{
    u16 *rows;
    u16 *destination;
    u16 frame;
    s32 line;
    s32 start;
    s32 end;
    s32 size;
    s32 row;
    s32 column;
    s32 colored;
    u32 stride = state->unknown_15;
    u8 width = stride;

    frame = state->unknown_1A + offset;
    frame *= 2;
    frame = func_08142950(frame, state->unknown_17 * 2);
    rows = state->unknown_0C + frame * width;
    line = offset * 2;
    destination = state->unknown_08 + line * state->unknown_1E;
    if (palette == 0xFF)
        palette = state->unknown_1F;
    start = (state->unknown_10 & 2) ? 2 : 0;
    if (state->unknown_10 & 4)
        end = width - 2;
    else
        end = width;
    for (row = 0; row < 2; row++) {
        colored = 0;
        size = end - start;
        for (column = start; column < end; column++) {
            if (colored++ < count)
                rows[column] = (rows[column] & 0xFFF) | (palette << 12);
        }
        func_0814186C(rows + start, destination + start, size & 0x1FFFFF);
        rows += stride;
        destination += state->unknown_1E;
    }
}
