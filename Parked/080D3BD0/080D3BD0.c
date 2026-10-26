typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    u16 duration;
    u8 first;
    u8 second;
} __attribute__((packed)) Entry;

typedef struct {
    u8 unknown_00[4];
    u16 count;
    Entry entries[0];
} __attribute__((packed)) Sequence;

typedef struct {
    int unknown_00[3];
} Transition;

typedef struct {
    const Sequence *sequence;
    u8 flags;
    u8 mode;
    u8 unknown_06[2];
    u8 first;
    u8 second;
    u8 unknown_0A[2];
    u16 index;
    u16 first_duration;
    u16 second_duration;
    u8 unknown_12[2];
    Transition first_transition;
    Transition second_transition;
} State;

typedef struct {
    u8 unknown_00[0x4C];
    u8 first;
    u8 second;
    u8 third;
} Control;

extern Control g_control_flags_03000940;
extern void func_080E0608(Transition *transition, int start, int end, int duration);

void func_080D3BD0(State *state)
{
    const Sequence *sequence = state->sequence;
    const Entry *entry;

    for (;;) {
        entry = &sequence->entries[state->index];
        if (entry->duration != 0xFFFF)
            break;
        state->first = entry->first;
        state->second = entry->second;
        state->index++;
        if (state->index >= sequence->count && (state->flags & 1))
            state->index = 0;
    }

    state->first_duration = 0;
    state->second_duration = 0;
    if (entry->first != state->first)
        func_080E0608(&state->first_transition, state->first,
                      entry->first, (s16)entry->duration);
    else
        state->first_duration = entry->duration;

    if (state->mode == 1 && entry->second != state->second)
        func_080E0608(&state->second_transition, state->second,
                      entry->second, (s16)entry->duration);
    else
        state->second_duration = entry->duration;

    if (state->mode == 1) {
        g_control_flags_03000940.first = state->first;
        g_control_flags_03000940.second = state->second;
    } else {
        g_control_flags_03000940.third = state->first;
    }
}
