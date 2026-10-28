#include "ffta.h"

struct MenuState;

typedef struct {
    u8 unknown_0000[0x5B0];
    struct MenuState *owner;
} MenuContext;

extern MenuContext *data_0200F44C;

/* Complete [0x0805F588, 0x0805F59C): 20 bytes, 7 reachable instructions. */
void func_0805F588(struct MenuState *state)
{
    data_0200F44C->owner = state;
}
