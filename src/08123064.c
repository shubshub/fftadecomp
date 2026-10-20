#include "ffta.h"

typedef struct {
    u8 *data;
} ScriptObject;

void *func_081255C8(u32 selector);
void func_08124710(void *object, u32 first, u32 second);

u32 func_08123064(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);

    func_08124710(object, 1, object->data[0xF8]);
    return 0x110;
}
