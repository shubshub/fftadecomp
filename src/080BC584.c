#include "ffta.h"

typedef struct {
    void *data;
    u8 unknown_04[0x24];
    u16 flags;
} Record080BC584;

typedef struct {
    Record080BC584 *record;
    u32 unknown_04;
    s16 x, y, z;
    u8 unknown_0E[0x22];
    u32 flags;
} Entry080BC584;

typedef struct {
    void *context;
    Entry080BC584 *entries[13];
    u8 index;
    u8 count;
    s16 timer;
    void *workspace;
    u16 current;
    u16 history_count;
    u16 history[34];
} State080BC584;

extern void func_08099BAC(Entry080BC584 *entry);
extern u32 func_080995C0(Entry080BC584 *entry);
extern void func_080BC3B0(void *workspace, u32 value);
extern u32 func_080BC40C(void *workspace);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern void func_08025688(u16 identifier, u16 parameter, const void *argument);
extern s32 func_08025464(void);
extern void func_08029514(void);

/* Complete [0x080BC584, 0x080BC77E), 506 bytes including the switch table. */
u32 func_080BC584(State080BC584 *state, u16 buttons)
{
    switch (state->current) {
    case 0:
        if (state->index >= state->count)
            goto advance;
        state->history[state->history_count++] = state->current;
        state->current = 8;
        state->history[state->history_count++] = state->current;
        state->current = 5;
        state->history[state->history_count++] = state->current;
        state->current = 3;
        state->history[state->history_count++] = state->current;
        state->current = 1;
        break;
    case 8:
        func_08099BAC(state->entries[state->index]);
        func_080995C0(state->entries[state->index]);
        ++state->index;
        goto advance;
    case 3: {
        /* 0x080BC666-0x080BC670 forms the slot before loading workspace and entry. */
        u32 offset = state->index * sizeof(*state->entries);
        u8 *entries = (u8 *)state->entries;
        Entry080BC584 **slot = (Entry080BC584 **)(entries + offset);
        func_080BC3B0(state->workspace, (u32)*slot);
        state->current = 4;
        break;
    }
    case 4:
        if ((u8)func_080BC40C(state->workspace))
            break;
        state->entries[state->index]->record->flags |= 0x100;
        state->entries[state->index]->flags |= 5;
        goto advance;
    case 1: {
        Entry080BC584 *entry = state->entries[state->index];
        func_08096F3C(entry->x, entry->y, entry->z);
        state->current = 2;
        break;
    }
    case 2:
        if (func_08096F7C())
            break;
        goto advance;
    case 5:
        func_08025688(0x2f, 0, state->entries[state->index]->record->data);
        state->timer = 0;
        state->current = 6;
        break;
    case 6:
        ++state->timer;
        if ((buttons & 3) && state->timer > 15)
            state->timer = 120;
        func_08025464();
        if (state->timer <= 119)
            break;
        state->timer = 0;
        func_08029514();
        state->current = 7;
        break;
    case 7:
        if (!(u16)func_08025464())
            break;
    advance:
        state->current = state->history[--state->history_count];
        break;
    case 9:
        return 0;
    }
    return 1;
}
