#include "ffta.h"

typedef struct {
    u8 unknown_000[0xbb8];
    u8 control_flags[0x50];
} State080312CC;

extern u8 g_control_flags_03000940[];
extern State080312CC *g_state_03002810;
extern void *func_081443FC(void *, const void *, u32);

/* Complete [0x080312CC, 0x080312F0): 36 bytes, 10 instructions. */
void func_080312CC(void)
{
    func_081443FC(g_control_flags_03000940,
                  g_state_03002810->control_flags, 0x50);
}
