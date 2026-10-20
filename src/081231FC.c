#include "ffta.h"

typedef struct {
    void *data;
    u8 unknown_04[0x1A];
    u8 value_1E;
} ScriptObject;

void *func_081255C8(u32 selector);
u16 func_08022238(void *data, u8 *output);

u32 func_081231FC(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);
    u8 output;

    func_08022238(object->data, &output);
    object->value_1E = output;
    return 0x110;
}
