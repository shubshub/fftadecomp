#include "ffta.h"

/* 0x080BCA54: 32 bytes. */
typedef struct {
    u8 unknown_00[0x3C];
    void *allocation;
} AllocatedState;

void func_08022854(void *allocation);

void func_080BCA54(void *object)
{
    AllocatedState *state = object;

    if (state->allocation != 0) {
        func_08022854(state->allocation);
        state->allocation = 0;
    }
    func_08022854(object);
}
