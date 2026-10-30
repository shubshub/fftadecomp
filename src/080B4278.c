#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1550];
    u8 *unknown_1550;
} State080B4278;

extern void func_08022854(u8 *object);

/* 0x080B4278..0x080B4294: 28 complete bytes, including the field-offset literal. */
void func_080B4278(State080B4278 *state)
{
    func_08022854(state->unknown_1550);
    state->unknown_1550 = 0;
}
