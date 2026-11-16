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
    u8 mode;
    u8 unknown_1C9;
    u8 requested;
    u8 unknown_1CB[5];
    u16 unknown_1D0;
    u8 unknown_1D2[0x46];
} State080BCDF8;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_080BCB2C(State080BCDF8 *state, u8 enabled);
extern void func_080BCC70(State080BCDF8 *state, u8 enabled);

/* Whether no node of the list is active; the walk visits every node
 * (0x080BCE60..0x080BCE6C clears the flag and keeps going). */
static inline u8 allInactive(Node080BCDF8 *head)
{
    u8 inactive = 1;
    Node080BCDF8 *node;

    for (node = head; node != 0; node = node->next) {
        if (node->active != 0)
            inactive = 0;
    }
    return inactive;
}

/* Clears the whole 0x218-byte state (the size func_080BD02C allocates and
 * clears) and keeps the requested mode. */
static inline void resetState(State080BCDF8 *state)
{
    u8 requested = state->requested;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->requested = requested;
}

/* Complete [0x080BCDF8, 0x080BCED0): 216 bytes, 103 instructions. */
void func_080BCDF8(State080BCDF8 *state)
{
    switch (state->mode) {
    case 0:
        switch (state->requested) {
        case 1:
            state->mode = 1;
            state->unknown_1D0 = 1;
            break;
        case 2:
            state->mode = 2;
            state->unknown_1D0 = 2;
            break;
        }
        break;
    case 1:
        func_080BCB2C(state, state->mode == state->requested);
        if (state->mode != state->requested && allInactive(state->head))
            resetState(state);
        break;
    case 2:
        func_080BCC70(state, state->mode == state->requested);
        if (state->mode != state->requested && allInactive(state->head))
            resetState(state);
        break;
    }
}
