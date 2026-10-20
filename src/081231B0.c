#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    s8 value_1F;
} ScriptObject;

void *func_081255C8(u32 selector);
void func_0809A09C(void *object);
void func_0809A2AC(void *object, u16 value, s32 selector, u32 option);
void func_0809A530(void *object, u32 value);
void func_0809A570(void *object, u32 clear, u32 set);

u32 func_081231B0(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);
    u32 value = script[2] | (script[3] << 8);

    func_0809A09C(object);
    func_0809A2AC(object, value * 4, object->value_1F, 0);
    func_0809A530(object, script[4]);
    func_0809A570(object, 0, 0x100);
    return 0x110;
}
