#include "ffta.h"

/* 0x0813EF38..0x0813EF4C: 20 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u16 position[4];
} PositionState;

extern void func_0814186C(const void *, void *, u32);

void func_0813EF38(PositionState *state, const u16 *position)
{
    func_0814186C(position, state->position, 4);
}
