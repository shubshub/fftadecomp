#include "ffta.h"

/* 0x0805DD0C..0x0805DD64: 88 bytes. */
struct Entry0805DD0C {
    u8 id;
    u8 unknown_01;
    u16 status;
};

struct State0805DD0C {
    u8 unknown_00[0x11AA];
    u8 count;
    u8 unknown_11AB[0x9D];
    struct Entry0805DD0C *entries[0];
};

extern struct State0805DD0C *data_0200F448;

struct Entry0805DD0C *func_0805DD0C(u16 id)
{
    int i;
    struct State0805DD0C *state;

    id -= 0x177;
    i = 0;
    state = data_0200F448;
    if (i < state->count) {
        struct Entry0805DD0C **cursor = state->entries;
        int count = state->count;

        do {
            struct Entry0805DD0C *entry = *cursor;

            if (entry->id != 0 && entry->status == 0 && entry->id == id)
                return entry;
            ++cursor;
            ++i;
        } while (i < count);
    }
    return 0;
}
