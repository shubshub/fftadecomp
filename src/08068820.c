#include "ffta.h"

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} Item08068820;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09[7];
    void *item;
    u8 unknown_14[0x70];
    u8 panel[1];
} State08068820;

extern Item08068820 *func_08005BFC(void *);
extern void func_08017E28(void *);

/* Complete [0x08068820, 0x08068848): 40 bytes, 18 instructions. */
void func_08068820(State08068820 *state)
{
    if (state->mode != 4 || !(func_08005BFC(state->item)->flags & 1))
        func_08017E28(state->panel);
}
