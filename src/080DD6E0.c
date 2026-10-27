#include "ffta.h"

struct Owner080DD6E0 {
    const void *object;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

u16 func_080DD6E0(const struct Owner080DD6E0 *owner)
{
    return func_080C7EA4(owner->object, 1);
}
