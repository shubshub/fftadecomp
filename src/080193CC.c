#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 value;
} NumberState080193CC;

extern NumberState080193CC data_020021B4;
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x080193CC, 0x080193FC): 48 bytes, 19 instructions. */
u32 func_080193CC(u8 *destination)
{
    NumberState080193CC *state = &data_020021B4;
    u8 *cursor = destination;

    if (state->value < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, state->value);
    return 0;
}
