#include "ffta.h"

/* 0x080BD328: 22 bytes. */
typedef struct {
    u8 unknown_00[0x4C];
} ObjectState;

void *func_08022840(u32 size);
void func_080BD14C(ObjectState *state);

ObjectState *func_080BD328(void)
{
    ObjectState *state = func_08022840(sizeof(ObjectState));

    func_080BD14C(state);
    return state;
}
