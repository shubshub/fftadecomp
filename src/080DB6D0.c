#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[0x0C];
    s16 timed;
    u16 duration;
    u16 layer;
} ScriptTask;

typedef struct {
    u8 layer;
    u8 unknown_01[3];
    void *object;
    void *script;
    void *effect;
} ScriptStateData;

extern const u8 data_0894DA44[];
extern u16 g_control_flags_03000940;
extern void *func_08147AD0(u32 start, u32 end, u16 duration);
extern void *func_081484CC(void *effect);
extern void *func_080D3E9C(const void *script, void *parent);
extern void func_080D3F84(void *script, u32 index, u32 value);
extern void func_080DBEB4(void *object, u8 enabled);
extern void *func_080D3F08(void *script);
extern u32 func_080035A8(u8 layer);

u32 func_080DB6D0(void *object, ScriptTask *task, ScriptStateData *state)
{
    switch (task->state) {
    case 0:
        state->object = task->object;
        state->layer = task->layer;
        if (task->timed)
            state->effect = func_08147AD0(0x90, 0x10, task->duration);
        break;
    case 1:
        break;
    case 0x100:
        state->effect = func_081484CC(state->effect);
        if (state->effect == 0) {
            state->script = func_080D3E9C(data_0894DA44, object);
            func_080D3F84(state->script, 12, 255);
            func_080DBEB4(state->object, 1);
            task->state++;
        }
        break;
    case 0x101:
        state->script = func_080D3F08(state->script);
        if (state->script == 0) {
            u32 mask = func_080035A8(state->layer);
            u16 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
            task->state = 2;
        }
        break;
    }
    return 0;
}
