#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[0xC];
    u32 flags;
    u8 unknown_58[8];
    u32 field_60;
    u16 field_64;
    u16 field_66;
} State0806406C;

extern State0806406C *data_0200F450;
extern void func_08066028(void *task);

/* Observed function: [0x0806406C, 0x080640D4), 104 bytes. */
void func_0806406C(void)
{
    State0806406C *head = data_0200F450;
    State0806406C *state;

    head->field_64 = 0x9004;
    head->field_66 = 0x1237;
    head->field_60 = 0;
    func_08066028(head->task);

    state = data_0200F450;
    state->current = 0x30;
    state->entries[state->count++] = state->current;
    state->current = 0x39;
    state->entries[state->count++] = state->current;
    state->current = 0x32;
    state->flags &= ~0x40;
}
