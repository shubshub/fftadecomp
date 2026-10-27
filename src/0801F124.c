#include "ffta.h"

typedef struct {
    u8 unknown_00[0x168];
    const void *transfer;
    u8 unknown_16C[4];
    const void *relocation_base;
    u8 unknown_174[12];
    u8 flags;
} ResourceState;

extern ResourceState g_state_02007F40;

/* 0801F124..0801F1A8: 132 bytes, 62 instructions. */
void func_0801F124(const u32 *resource)
{
    u32 header;

    g_state_02007F40.flags = 0;
    header = *resource;
    if (header & 0x80000000) {
        g_state_02007F40.transfer = resource + 1;
        g_state_02007F40.relocation_base = (const u8 *)resource +
                                 (header & 0x0FFFFFFF);
        g_state_02007F40.flags = 1;
    } else {
        g_state_02007F40.transfer = resource + 1;
        g_state_02007F40.relocation_base = 0;
    }
    if (*resource & 0x40000000)
        g_state_02007F40.flags |= 2;
    g_state_02007F40.flags |= 4;
}
