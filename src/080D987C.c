#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 values[0];
} ObjectState;

extern ObjectState *func_08005BFC(void *object);

void func_080D987C(void *object, u8 index, u16 value)
{
    ObjectState *state = func_08005BFC(object);

    state->values[index] = value;
}
