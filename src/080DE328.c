#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 value;
} ValueState;

typedef struct {
    ValueState *state;
} Object;

extern void func_080DDDA0(Object *object, s8 value);

void func_080DE328(Object *object)
{
    func_080DDDA0(object, (s8)object->state->value);
}
