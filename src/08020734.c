#include "ffta.h"

typedef struct {
    u8 unknown_000[0x168];
    void *transfer;
    u8 unknown_16C[4];
    void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

extern ResourceState g_state_02007F40;
extern void *func_0801ED24(const void *source, void *relocation_base, u8 flags,
                         u32 mode, u32 x, u32 y, u32 attributes, u32 size);

/* 08020734..08020774: 64 bytes. */
void func_08020734(void)
{
    g_state_02007F40.transfer = func_0801ED24(g_state_02007F40.transfer,
        g_state_02007F40.relocation_base, g_state_02007F40.flags,
        0, 0, 0, 0, 0x800);
}
