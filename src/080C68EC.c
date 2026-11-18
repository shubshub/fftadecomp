#include "ffta.h"

typedef struct ListSource ListSource;

typedef struct {
    void *record;
} ListEntry;

typedef struct InitializerState {
    u8 unknown_00[0x60];
    ListSource *source;
    void *records[2];
    u8 unknown_6C[0xD];
    u8 record_count;
    u8 unknown_7A[2];
    u16 current;
    u16 depth;
    u16 history[4];
    u8 unknown_88[0x3C];
} InitializerState;

extern void (*const g_callbacks_0836D4B8[])(void *, u32);
extern u32 func_08099CDC(ListSource *source, void **entries);
extern u8 func_08133BC4(void *record);

/* The same state/depth/history push occurs in func_080C62CC. */
static inline void push_state(InitializerState *state)
{
    state->history[state->depth++] = state->current;
}

/* Complete target [0x080C68EC, 0x080C69C8), 220 bytes. */
void func_080C68EC(InitializerState *state, ListSource *source)
{
    void *entries[13];
    s32 count;
    s32 i;
    void **cursor;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->source = source;
    count = func_08099CDC(source, entries);
    for (i = 0; i < count; i++) {
        cursor = &entries[i];
        if (func_08133BC4(((ListEntry *)*cursor)->record)) {
            state->records[state->record_count] = ((ListEntry *)*cursor)->record;
            state->record_count++;
            if (state->record_count > 1)
                break;
        }
    }
    state->current = 0x12;
    push_state(state);
    state->current = 5;
    push_state(state);
    state->current = 8;
    push_state(state);
    state->current = 2;
    push_state(state);
    state->current = 0;
}
