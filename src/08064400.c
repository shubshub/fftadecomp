#include "ffta.h"

typedef struct {
    ScriptState script;
    u8 unknown_68[0x884 - sizeof(ScriptState)];
    void *object;
} ExtendedScriptState;

u16 func_08011860(void);
void func_08022854(void *object);

void func_08064400(void)
{
    ExtendedScriptState *state;

    if (func_08011860() != 0) {
        if ((*(ExtendedScriptState **)0x0200F450)->object != 0) {
            func_08022854((*(ExtendedScriptState **)0x0200F450)->object);
            (*(ExtendedScriptState **)0x0200F450)->object = 0;
        }
        state = *(ExtendedScriptState **)0x0200F450;
        state->script.current = state->script.entries[--state->script.count];
    }
}
