#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 category;
} CategoryObject;

u32 func_0809A398(const void *object)
{
    const CategoryObject *state = object;

    switch (state->category) {
    case 0x1D:
    case 0x20:
    case 0x48:
    case 0x49:
        return 4;
    default:
        return 0;
    }
}
