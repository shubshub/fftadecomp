#include "ffta.h"

/* 0x080DE244..0x080DE266: 34 bytes. */
extern u8 func_08099C9C(void *state);
extern u8 func_08099C64(void *state);

u8 func_080DE244(void *state)
{
    if (func_08099C9C(state))
        return 0;
    return func_08099C64(state);
}
