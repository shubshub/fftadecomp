#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    u8 unknown_44[0xA8];
    void (*callback)(u8 enabled);
} State080640D4;

extern State080640D4 *data_0200F450;
extern void func_08061F54(u8 enabled);

/* Observed function: [0x080640D4, 0x08064108), 52 bytes. */
void func_080640D4(void)
{
    State080640D4 *state;

    func_08061F54(0);
    state = data_0200F450;
    state->callback = func_08061F54;
    state->current = state->entries[--state->count];
}
