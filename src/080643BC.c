#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    u8 unknown_44[0xa];
    u8 code;
    u8 unknown_4f[5];
    u32 flags;
    u8 unknown_58[0x98];
    u8 object[1];
} State080643BC;

extern State080643BC *data_0200F450;
extern void func_08061028(void *, u8);
extern void func_080133B0(u32);

/* Complete [0x080643BC, 0x08064400): 68 bytes, 30 instructions. */
void func_080643BC(void)
{
    State080643BC *state;

    func_08061028(data_0200F450->object, data_0200F450->code);
    if (data_0200F450->flags & 4)
        func_080133B0(0x1000);
    state = data_0200F450;
    state->current = state->entries[--state->count];
}
