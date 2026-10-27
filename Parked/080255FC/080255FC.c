#include "ffta.h"

/* 0x080255FC..0x08025688: 140 bytes. */
typedef struct {
    u16 first;
    u16 second;
} MenuPair;

typedef struct {
    u8 unknown_00[0x18];
    void *selected;
    u8 unknown_1C[0x424];
    MenuPair entries[16];
} MenuState;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} ControlState;

extern MenuState *data_0200F438;
extern ControlState g_state_0200F390;

static inline void clear_entries(int first, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        MenuPair *entry = &data_0200F438->entries[first + i];

        entry->first = 0;
        entry->second = 0;
    }
}

void func_080255FC(u8 index)
{
    if (index <= 15) {
        MenuPair *entry = &data_0200F438->entries[index];

        entry->first = 0;
        entry->second = 0;
        if (index == 4) {
            ControlState *state;

            entry = &data_0200F438->entries[5];
            entry->first = 0;
            entry->second = 0;
            state = &g_state_0200F390;
            clear_entries(6, 3);
            clear_entries(13, 3);
            state->flags &= ~0x20;
        } else if (index == 2) {
            data_0200F438->selected = 0;
        }
    }
}
