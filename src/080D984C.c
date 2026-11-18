#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u8 first_range[2];
    u8 second_range[2];
} DisplayState;

extern DisplayState *func_08005BFC(void *task);

/* 080D984C..080D987A: 46 bytes. */
void func_080D984C(void *task, u8 selector, u8 start, u8 end)
{
    DisplayState *state = func_08005BFC(task);

    if (selector == 0) {
        state->first_range[0] = start;
        state->first_range[1] = end;
    } else {
        state->second_range[0] = start;
        state->second_range[1] = end;
    }
}
