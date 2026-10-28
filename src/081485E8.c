#include "ffta.h"

typedef struct {
    u16 state;
    u16 unknown_02;
    u16 value;
} EffectValue;

u16 func_081485E8(const EffectValue *effect)
{
    if (effect->state == 0)
        return 0x8000;
    return effect->value;
}
