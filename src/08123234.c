#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    u32 unknown_00;
    SceneRecord *record;
} Binding;

typedef struct {
    u8 unknown_00[0xA8];
    u8 values[3];
} SelectionState;

extern SelectionState g_state_020020D0;

Binding *func_08121C70(u8 selector);

u32 func_08123234(void *context, const u8 *script)
{
    u8 index = 0;
    Binding *binding;

    switch (script[1]) {
    case 0:
        index = g_state_020020D0.values[0] - 1;
        break;
    case 1:
        index = g_state_020020D0.values[1] - 1;
        break;
    case 2:
        index = g_state_020020D0.values[2] - 1;
        break;
    }
    binding = func_08121C70(script[2]);
    binding->record = &((SceneRecord *)0x02002FC4)[index];
    return 0x110;
}
