#include "ffta.h"

typedef struct Node080BCDF8 {
    u8 unknown_00[0x11];
    u8 active;
    u8 unknown_12[6];
    struct Node080BCDF8 *next;
} Node080BCDF8;

typedef struct {
    u8 unknown_00[0x1C0];
    Node080BCDF8 *head;
    u8 unknown_1C4[4];
    u8 current;
    u8 unknown_1C9;
    u8 requested;
    u8 unknown_1CB[5];
    u16 mode;
    u8 unknown_1D2[0x46];
} State080BCDF8;

typedef void (*ClearBuffer080BCDF8)(void *destination, u32 size);

extern ClearBuffer080BCDF8 const g_callbacks_0836D4B8[];
extern void func_080BCB2C(State080BCDF8 *state, u8 enabled);
extern void func_080BCC70(State080BCDF8 *state, u8 enabled);

static inline u8 allInactive(State080BCDF8 *state)
{
    Node080BCDF8 *node = state->head;
    u8 inactive = 1;

    while (node != 0) {
        if (node->active != 0)
            inactive = 0;
        node = node->next;
    }
    return inactive;
}

/* Complete [0x080BCDF8, 0x080BCED0): 216 bytes, 103 instructions. */
void func_080BCDF8(State080BCDF8 *state)
{
    switch (state->current) {
    case 0:
        {
            s32 requested = state->requested;

            if (requested == 1 || requested == 2) {
                state->current = requested;
                state->mode = requested;
            }
        }
        break;
    case 1:
        func_080BCB2C(state, state->current == state->requested);
        if (state->current != state->requested && allInactive(state)) {
            u8 requested = state->requested;

            g_callbacks_0836D4B8[0](state, sizeof(*state));
            state->requested = requested;
        }
        break;
    case 2:
        func_080BCC70(state, state->current == state->requested);
        if (state->current != state->requested && allInactive(state)) {
            u8 requested = state->requested;

            g_callbacks_0836D4B8[0](state, sizeof(*state));
            state->requested = requested;
        }
        break;
    }
}
