#include "ffta.h"

typedef struct SceneRecord SceneRecord;

typedef struct {
    u32 unknown_00;
    SceneRecord *record;
} Binding;

typedef struct {
    u8 unknown_00[0x4D8];
    Binding bindings[256];
} BindingState;

extern BindingState *data_020159CC;

/* Target: [0x08121C70, 0x08121C96), 38 bytes, 16 instructions. */
Binding *func_08121C70(u8 selector)
{
    if (data_020159CC == 0)
        return 0;
    return &data_020159CC->bindings[selector];
}
