#include "ffta.h"

typedef struct {
    u8 status;
} State08010FF0;

u8 func_08010FF0(const State08010FF0 *state)
{
    if (state->status == 2)
        return 1;
    return 0;
}
