#include "ffta.h"

/* Complete [0x0802192C, 0x08021A3C): 272 bytes, 131 instructions. */
typedef struct {
    u32 flags;
    u8 unknown_04[0x0e];
    u16 start;
    u16 current;
    u16 duration;
} Entry0802192C;

typedef struct {
    u16 time;
    u8 unknown_02[2];
    Entry0802192C **entries;
    Entry0802192C **cursor;
    int processed;
    int count;
    u8 flags;
} State0802192C;

u32 func_0802192C(State0802192C *state, int steps)
{
    Entry0802192C **scan = state->entries;
    int i;

    for (i = 0; i < state->count; i++, scan++) {
        if ((*scan)->start != (*scan)->current)
            return 1;
    }
    if (state->processed >= state->count)
        return 0;

    for (i = 0; i < steps; i++) {
        u8 flags;
        int active;
        Entry0802192C **cursor;
        u16 time;
        Entry0802192C *current;

retry_boundary:
        flags = state->flags;
        active = flags & 1;
        cursor = state->cursor;
        time = state->time;
        if (!active) {
            current = *cursor;
            if (time == current->start) {
                state->processed++;
                if (state->processed >= state->count)
                    return 0;
                state->time = current->duration + current->start;
                (*cursor)->current = (*cursor)->start;
                state->cursor++;
                goto retry_boundary;
            }
        }
        if (!active && current->start < time) {
            u16 offset = time - current->start;
            Entry0802192C **p = state->entries + (state->count - 1);
            for (; p != state->cursor; p--) {
                (*p)->current = (*p)->start + offset;
                (*p)->flags = ((*p)->flags | 0x80) & 0xfffcffff;
            }
            state->flags |= 1;
            i = steps;
        } else {
            Entry0802192C **next;
            Entry0802192C *entry;
            state->flags = flags & 0xfe;
            (*cursor)->current = time;
            next = state->cursor;
            entry = *next++;
            entry->flags = (entry->flags | 0x80) & 0xfffcffff;
            state->processed++;
            state->time += entry->duration;
            state->cursor = next;
        }
    }
    return 1;
}
