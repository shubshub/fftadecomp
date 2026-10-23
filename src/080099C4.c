#include "ffta.h"

extern u8 g_state_02000000[];
extern const u32 g_table_085516D0[];
extern const u32 g_table_08565F14[];

u16 func_08018C24(u8 *destination, const u8 *source);

void func_080099C4(void)
{
    u8 *state = g_state_02000000;

    state[0x2190] = 1;
    state[0x2191] = 1;
    func_08018C24(state + 0x1F1C, (const u8 *)g_table_085516D0[2]);
    func_08018C24(state + 0x21A0, (const u8 *)g_table_08565F14[0]);
}
