#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 field_02;
} ScriptContext;

typedef struct SceneRecord SceneRecord;

extern SceneRecord *func_080C83CC(u8 category);
extern u8 func_080C8260(const SceneRecord *record);
extern u8 func_080C8240(const SceneRecord *record);

void func_0800A3E4(ScriptContext *context, const u8 *instruction)
{
    SceneRecord *record = func_080C83CC(instruction[1]);

    if (record != 0 && !func_080C8260(record) && !func_080C8240(record))
        context->field_02 += instruction[2] | (instruction[3] << 8);
}
