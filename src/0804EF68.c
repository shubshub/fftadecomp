#include "ffta.h"

/* 0x0804EF68..0x0804EF90: 40 bytes. */
typedef struct {
    u8 unknown_00[9];
    u8 selector;
} State0804EF68;

extern u8 func_080099A4(u8 selector);
extern void func_0804F948(State0804EF68 *state);
extern void func_0804F28C(State0804EF68 *state);

u8 func_0804EF68(State0804EF68 *state)
{
    if (func_080099A4(state->selector) != 0) {
        func_0804F948(state);
        func_0804F28C(state);
        return 1;
    }
    return 0;
}
