#include "ffta.h"

extern u8 func_080CAA74(void *);

/* Complete [0x080680E0, 0x080680F6): 22 bytes, 10 instructions. */
u8 func_080680E0(void *state)
{
    return func_080CAA74(state) != 0;
}
