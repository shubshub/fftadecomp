#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u16 counter;
} ScriptContext;

void func_08121D40(u32 value, u32 mode);
void func_08141570(u32 mode, u32 value);

u32 func_08123770(ScriptContext *context, const u8 *script)
{
    u32 value = script[1] | (script[2] << 8);
    u8 mode = script[3];

    if (mode == 0xFF) {
        func_08121D40(0x6400, 2);
        func_08141570(1, value);
    } else {
        switch (mode) {
        case 2:
            mode = 1;
            func_08121D40(0x6400, 2);
            break;
        case 4:
            mode = 2;
            func_08121D40(0x640000, 4);
            break;
        }
        func_08141570(mode, value);
    }
    context->counter = 0;
    return 0x114;
}
