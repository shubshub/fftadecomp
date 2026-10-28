#include "ffta.h"

typedef struct Object Object;

extern s32 func_0812C8DC(const Object *source, const Object *target,
                        u32 mode, u32 option);

s32 func_0812F068(const Object *source, const Object *target)
{
    s32 value = func_0812C8DC(source, target, 2, 0) * 2;

    if (value > 100)
        value = 100;
    return value;
}
