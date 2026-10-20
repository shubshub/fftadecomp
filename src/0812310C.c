#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 value_08;
    u16 value_0A;
    u16 value_0C;
} ScriptObject;

void *func_081255C8(u32 selector);

u32 func_0812310C(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);

    object->value_08 += script[2] | (script[3] << 8);
    object->value_0C += script[4] | (script[5] << 8);
    object->value_0A += script[6] | (script[7] << 8);
    return 0x110;
}
