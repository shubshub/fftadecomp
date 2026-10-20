#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    u32 *primary;
    u32 unknown_48;
    u32 *additional[2];
} ObjectFlags;

u8 func_0802202C(const u32 *flags);

u8 func_0809A3BC(void *object)
{
    ObjectFlags *flags = object;
    s32 index;

    if (!func_0802202C(flags->primary))
        return 0;
    for (index = 0; index < 2; index++) {
        if (flags->additional[index] != 0 && !func_0802202C(flags->additional[index]))
            return 0;
    }
    return 1;
}
