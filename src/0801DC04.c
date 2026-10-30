#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 value;
} State0801DC04;

extern State0801DC04 data_02007F10;
extern void func_0801DC24(u16 index);

/* 0801DC04..0801DC18: 00 B5 03 48 40 8A 00 F0 0B F8 01 BC 00 47 00 00 10 7F 00 02. */
void func_0801DC04(void)
{
    State0801DC04 *state = &data_02007F10;

    func_0801DC24(state->value);
}
