#include "ffta.h"

struct Owner080DD708 {
    const void *object;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

u16 func_080DD708(const struct Owner080DD708 *owner)
{
    return func_080C7EA4(owner->object, 4);
}
