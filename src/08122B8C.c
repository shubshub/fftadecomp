#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *parent;
} CommandState;

extern u32 func_08122454(void *object);

u32 func_08122B8C(CommandState *state, const u8 *command)
{
    func_08122454(state->parent);
    state->parent = 0;
    return 0x11E;
}
