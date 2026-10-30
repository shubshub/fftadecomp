#include "ffta.h"

typedef struct {
    void *data;
    u8 unknown_04[0x1A];
    u8 value_1E;
    u8 unknown_1F[0x11];
    u32 flags_30;
    u16 value_34;
} ScriptObject;

extern u16 func_08022268(void *object, u8 *output);

/* 0x0809A36C..0x0809A398: 44 complete bytes.
 * Target: 10b581b0041c2068694687f777ffa086206b20210840002801d0e620a08668460078a07701b010bc01bc0047.
 */
void func_0809A36C(ScriptObject *object)
{
    u8 output;

    object->value_34 = func_08022268(object->data, &output);
    if (object->flags_30 & 0x20)
        object->value_34 = 0xE6;
    object->value_1E = output;
}
