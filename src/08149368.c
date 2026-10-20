#include "ffta.h"

typedef struct {
    u8 unknown_00[0x980];
    u8 category;
} CategoryObject;

u32 func_08149368(const void *object)
{
    const CategoryObject *state = object;

    if ((state->category & 0x7F) == 4)
        return 1;
    return 0;
}
