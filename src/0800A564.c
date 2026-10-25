#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 position;
} ScriptContext0800A564;

typedef struct {
    u8 unknown_0000[0x3C9C];
    u16 value;
} State0800A564;

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

extern State0800A564 g_state_02000000;
extern SceneRecord *func_080C83CC(u8 category);

void func_0800A564(ScriptContext0800A564 *context, const u8 *instruction)
{
    if (func_080C83CC(13) != 0 && g_state_02000000.value == 0x140)
        context->position += instruction[1] | (instruction[2] << 8);
}
