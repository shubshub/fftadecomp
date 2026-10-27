#include "ffta.h"

typedef struct Object Object;
extern s32 func_0812C8DC(const Object *source, const Object *target,
                         u32 mode, u32 option);

/* Complete [0x0812F080, 0x0812F090): 16 bytes, 7 instructions. */
s32 func_0812F080(const Object *source, const Object *target, u8 mode)
{
    return func_0812C8DC(source, target, mode, 0);
}
