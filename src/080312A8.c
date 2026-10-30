#include "ffta.h"

typedef struct {
    u8 unknown_000[0xBB8];
    u8 control_flags[0x50];
} State080312A8;

extern u8 g_control_flags_03000940[];
extern State080312A8 *g_state_03002810;
extern void *func_081443FC(void *destination, const void *source, u32 size);

/* 080312A8..080312CC: 36 bytes, including the state, offset, and control-flags literals. */
void func_080312A8(void)
{
    func_081443FC(g_state_03002810->control_flags,
                  g_control_flags_03000940, 0x50);
}
