#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State080D39D4;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 080D39D4..080D39F0: 28 bytes, including the data_020159C0 pointer literal. */
void func_080D39D4(void)
{
    State080D39D4 *state = func_08005BFC(data_020159C0);

    state->flags |= 2;
}
