#include "ffta.h"

typedef struct {
    u8 unknown_000[0x312];
    u8 name[18];
    u8 unknown_324[2];
    u8 length;
} NameState;

extern u32 func_08013A5C(u16 glyph);

/* Complete 0x0812B184..0x0812B208: 132 bytes, 52 instructions. */
u16 func_0812B184(NameState *state)
{
    u16 i = 0;
    u16 advance = 0;

    for (; i < state->length; i++) {
        /* The marker test indexes the buffer (the ROM adds the 1 to the
         * index); the glyph is read through a pointer to the pair (the ROM
         * adds the 1 to the address), as at every other call of
         * func_08013A5C. */
        if (state->name[i * 2] == 0x40 && state->name[i * 2 + 1] == 0x73)
            advance += 6;
        else
            advance += func_08013A5C((((state->name + i * 2)[0] << 8) |
                                      (state->name + i * 2)[1]) & 0x7fff);
    }
    return advance;
}
