#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01[3];
} Entry080CAA74;

typedef struct {
    u8 unknown_00[0x968];
    Entry080CAA74 entries[64];
} State080CAA74;

extern State080CAA74 g_state_020021A0;
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);

/* Complete [0x080CAA74, 0x080CAB22): 174 bytes, 73 instructions.
 * Target: f0b557464e464546e0b40a4882460a495144002080463f260878002801d001208044013e0431002ef6da4146002905d1002035e0a0210002680900000024002646452cda402081460e4f57440e4d5544287800281ed10134321949468a1a92000a480368281c391c77f0b8fb4946081b800005494018504405490a68042177f0abfb0ae06c09000068090000bcd43608b8d436080437043501364645d8db404638bc9846a146aa46f0bc02bc0847
 */
s32 func_080CAA74(void)
{
    State080CAA74 *state = &g_state_020021A0;
    Entry080CAA74 *entry = state->entries;
    s32 count = 0;
    s32 holes;
    s32 i;

    for (i = 0; i < 64; i++, entry++) {
        if (entry->active)
            count++;
    }
    if (count == 0)
        return 0;

    holes = 0;
    i = 0;
    while (i < count) {
        if (state->entries[i].active == 0) {
            s32 next_holes = holes + 1;

            data_0836D4BC(&state->entries[i], &state->entries[i + 1],
                          (64 - (i + next_holes)) * sizeof(state->entries[0]));
            g_callbacks_0836D4B8[0](&state->entries[64 - next_holes],
                                    sizeof(state->entries[0]));
            holes = next_holes;
        } else {
            i++;
        }
    }
    return count;
}
