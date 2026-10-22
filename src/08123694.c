#include "script_record.h"

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ScriptStateFlags;

extern ScriptStateFlags g_state_0200F390;

void func_08121D40(u32 first, u32 second);
u16 func_0800A024(void);
u8 func_080C95A8(u16 index);
void func_081416DC(u16 value);
void func_08121D80(u8 value);
void func_08141708(void);

u32 func_08123694(void *context, const u8 *script)
{
    func_08121D40(0, 0xFF);
    if (script[1] == 0xFF) {
        const ScriptRecord *record = &g_table_0854CD54[func_0800A024()];

        if (g_state_0200F390.flags & 0x80) {
            u8 value = func_080C95A8(20);

            func_081416DC(value);
            func_08121D80(value);
        } else {
            func_08121D80(record->value26);
            func_081416DC(record->value26);
        }
    } else {
        func_08121D80(script[1]);
        func_081416DC(script[1]);
    }
    func_08141708();
    return 0x100;
}
