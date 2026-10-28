#include "ffta.h"

/* 0x0802058C..0x080205C8: 60 bytes. */
typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
    const u8 *current;
} ResourceState;

extern ResourceState g_state_02007F40;

static inline u32 transfer_idle(void)
{
    return g_state_02007F40.transfer == 0;
}

static inline u32 loader_idle(void)
{
    return g_state_02007F40.current == 0;
}

u32 func_0802058C(void)
{
    u32 ready = 0;

    if (transfer_idle() && loader_idle()) {
        ready = 1;
    }
    return ready;
}
