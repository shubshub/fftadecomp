#include "ffta.h"

typedef struct {
    u8 unknown_000[0x6CA];
    u8 flags;
} State0814143C;

extern u8 data_0300280C;
extern u8 func_08141318(State0814143C *state);

/* 0x0814143C..0x08141474:
 * 00 B5 03 1C 09 04 09 0C 08 20 01 40 00 29 07 D0
 * 07 48 19 18 08 78 01 22 10 43 08 70 05 48 02 70
 * 18 1C FF F7 5B FF 00 06 00 0E 02 BC 08 47 00 00
 * CA 06 00 00 0C 28 00 03. */
u8 func_0814143C(State0814143C *state, u16 flags)
{
    if (flags & 8) {
        state->flags |= 1;
        data_0300280C = 1;
    }
    return func_08141318(state);
}
