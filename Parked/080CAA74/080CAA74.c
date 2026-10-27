#include "ffta.h"

typedef struct Record080CAA74 {
    u8 occupied;
    u8 unknown_01[3];
} Record080CAA74;

typedef struct State080CAA74 {
    u8 unknown_00[0x968];
    Record080CAA74 records[64];
} State080CAA74;

typedef void (*RecordCopy080CAA74)(void *destination, const void *source,
                                  u32 size);
typedef void (*RecordClear080CAA74)(void *destination, u32 size);

extern State080CAA74 g_state_020021A0;
extern RecordCopy080CAA74 data_0836D4BC;
extern RecordClear080CAA74 g_callbacks_0836D4B8[];

static inline s32 remove_empty_record(State080CAA74 *state, s32 index,
                                     s32 holes)
{
    holes++;
    data_0836D4BC(&state->records[index], &state->records[index + 1],
                 (64 - (index + holes)) * sizeof(state->records[0]));
    g_callbacks_0836D4B8[0](&state->records[64 - holes],
                            sizeof(state->records[0]));
    return holes;
}

/* Complete [0x080CAA74, 0x080CAB22): 174 bytes, 73 instructions. */
s32 func_080CAA74(void)
{
    State080CAA74 *state = &g_state_020021A0;
    Record080CAA74 *record = state->records;
    s32 count = 0;
    s32 remaining;
    s32 holes;
    s32 index;

    for (remaining = 63; remaining >= 0; remaining--, record++) {
        if (record->occupied)
            count++;
    }
    if (count == 0)
        return 0;

    holes = 0;
    index = 0;
    while (index < count) {
        if (state->records[index].occupied == 0) {
            holes = remove_empty_record(state, index, holes);
        } else {
            index++;
        }
    }
    return count;
}
