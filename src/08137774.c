#include "ffta.h"

typedef struct {
    void *effect;
    u8 active;
} PaletteTransition;

void func_08137774(PaletteTransition *state)
{
    state->effect = 0;
    state->active = 0;
}
