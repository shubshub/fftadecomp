#include "ffta.h"

/* 0x08050EFC..0x08050F1A: 30 bytes. */
typedef struct {
    u8 unknown_00[0x98];
    u8 mode;
} State08050EFC;

extern void func_080500B0(State08050EFC *state);
extern void func_080501CC(State08050EFC *state);

void func_08050EFC(State08050EFC *state)
{
    state->mode = 2;
    func_080500B0(state);
    func_080501CC(state);
}
