#include "ffta.h"

typedef struct EffectNode0814846C EffectNode0814846C;
struct EffectNode0814846C {
    u8 unknown_00[0x28];
    EffectNode0814846C *next;
};

typedef struct {
    void *allocator;
    EffectNode0814846C *head;
} EffectManager0814846C;

extern EffectManager0814846C data_03003C60;

/* Complete [0x0814846C, 0x08148498): 44 bytes, 19 instructions. */
u32 func_0814846C(const EffectNode0814846C *target)
{
    EffectNode0814846C *node;

    if (target == 0)
        return 0;

    for (node = data_03003C60.head; node != 0; node = node->next) {
        if (target == node)
            return 1;
    }
    return 0;
}
