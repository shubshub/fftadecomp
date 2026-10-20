#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x3C24];
    u32 flags;
} ScriptStateFlags;

extern ScriptStateFlags g_state_02000000;

void func_080247FC(void *state);
void func_08096CB8(void);
void func_08022DD0(void);
void func_0800543C(void *destination, const void *source);
void func_08141868(const void *source, void *destination, u32 control);
u8 func_080C9540(u16 flag);
void func_08096DE4(u32 mode);
void func_08022A9C(void);
void func_080891BC(void);
void func_08121BF4(void);

u32 func_081235E4(void *context, const u8 *script)
{
    if (script[1]) {
        void *buffer;

        func_080247FC((void *)0x0200F3AC);
        func_08096CB8();
        func_08022DD0();
        buffer = (void *)0x02003CB0;
        func_0800543C(buffer, (const void *)0x083BBC7C);
        func_08141868(buffer, (void *)0x06012500, 0x440);
        if (func_080C9540(0x40)) {
            func_08096DE4(0);
            func_08022A9C();
        }
        if (g_state_02000000.flags & 8) {
            func_080891BC();
            g_state_02000000.flags &= ~8;
        }
    } else {
        func_08121BF4();
    }
    return 0x110;
}
