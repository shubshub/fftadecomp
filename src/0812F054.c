#include "ffta.h"

typedef struct Object Object;
extern s32 func_0812C8DC(const Object *source, const Object *target,
                         u32 mode, u32 option);

/* Complete [0x0812F054, 0x0812F068): 20 bytes, 9 instructions. */
s32 func_0812F054(const Object *source, const Object *target)
{
    s32 value = func_0812C8DC(source, target, 2, 0);

    if (value < 100)
        value >>= 1;
    return value;
}
