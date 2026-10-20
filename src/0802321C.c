#include "ffta.h"

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ScriptControl;

extern ScriptControl g_state_0200F390;

void *func_08096D7C(void);
void func_0809A3F4(void *context);
u8 func_080C9540(u16 flag);
void func_08070C94(u8 index, u8 *flag);
void func_08070604(u8 index, u8 *flag);

void func_0802321C(u8 index, u8 *flag)
{
    if (!(g_state_0200F390.flags & 2) && func_08096D7C() != 0)
        func_0809A3F4(func_08096D7C());

    if (func_080C9540(0x4A))
        func_08070C94(index, flag);
    else
        func_08070604(index, flag);
}
