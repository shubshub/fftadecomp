#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
} State080D3A14;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D3A14..0x080D3A30: 28 bytes, including alignment and the pointer literal. */
void func_080D3A14(void)
{
    State080D3A14 *state = func_08005BFC(data_020159C0);

    state->flags |= 0x20;
}
