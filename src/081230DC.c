#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value_18;
    u16 unknown_1A;
    u16 value_1C;
} ScriptData;

typedef struct {
    ScriptData *data;
} ScriptObject;

void *func_081255C8(u32 selector);
void func_080CD884(void *data, u32 first, u32 second);

u32 func_081230DC(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);

    func_080CD884(object->data, script[2], script[3]);
    if (script[2] == 0) {
        object->data->value_18 = 0;
        object->data->value_1C = 0;
    }
    return 0x110;
}
