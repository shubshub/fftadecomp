#include "ffta.h"
#include "control_flags.h"

/* Complete target [0x080BB7AC, 0x080BBBB0): 1028 bytes, 451 instructions,
 * plus the 13-entry jump table at 0x080BB7D4 and three literal pools.
 * One step of the ranked-object sequence: the camera visits the owner and
 * then every entry, each entry gets an effect, and on the way out every
 * entry's rank is added to its unit's counter at +0xD6 (capped at 10).
 * State 12, which func_080BB5C4 stores when it fills the list with bit 7 of
 * the global flags set, adds the ranks at once and finishes.  Returns 0 once
 * the sequence has finished. */

typedef struct Unit080BB7AC {
    u8 unknown_00[0xD6];
    u16 unknown_D6;
    u8 unknown_D8[0x20];
    u8 facing;
} Unit080BB7AC;

typedef struct Node080BB7AC {
    Unit080BB7AC *unit;
    u32 unknown_04;
    s16 x, y, z;
    u8 unknown_0E[0x11];
    s8 direction;
} Node080BB7AC;

typedef struct {
    Node080BB7AC *node;
    u8 rank;
    u8 unknown_05[3];
} Entry080BB7AC;

typedef struct {
    u8 unknown_00[0x44];
} Motion080BB7AC;

typedef struct State080BB7AC {
    Entry080BB7AC entries[13];
    Motion080BB7AC *motions;
    u8 motion_count;
    u8 selected;
    u8 count;
    u8 unknown_6F;
    s16 timer;
    u8 unknown_72[2];
    Node080BB7AC *owner;
    u16 current;
    u16 depth;
    u16 stack[34];
} State080BB7AC;

typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferFiller)(void *destination, u32 size, u32 value);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern BufferFiller const data_0836D4C0[];
extern u8 data_03003B20[];

extern void func_080A9270(void);
extern void func_080A9298(void);
extern void func_080A929C(void);
extern s32 func_080A9448(void);
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern s32 func_0809D6BC(s8 dx, s8 dz);
extern void func_0809836C(Node080BB7AC *node, u16 action, s8 direction,
                          u16 item);
extern void func_08141520(u16 sound);
extern void func_080A92E4(u16 mode, s16 x, s16 y, s16 z, u32 effect);
extern void func_080C9574(u16 bit_index, u16 enabled);
/* Both return a u8 here, where src/080BB4F8.c and src/080BB424.c return u32
 * (the same callee bytes either way).  The ROM sums into 080BB4F8's result
 * register (adds r0, r0, r1 at 0x080BB964; a u32 result gives adds r1, r1,
 * r0 and a 1024-byte function) and narrows 080BB424's result before the
 * test (lsls r0, r0, #24 at 0x080BBB8A). */
extern u8 func_080BB4F8(Node080BB7AC *source, Node080BB7AC **destination,
                        Motion080BB7AC *motion, s32 scalar);
extern u8 func_080BB424(State080BB7AC *state);

/* Saves the current state on the return stack. */
static inline void push_state(State080BB7AC *state)
{
    state->stack[state->depth++] = state->current;
}

/* Resumes the state saved by the last push_state. */
static inline void pop_state(State080BB7AC *state)
{
    state->current = state->stack[--state->depth];
}

/* Adds every entry's rank to its unit's counter, capped at 10.  The ROM
 * expands this twice (0x080BBAFE and 0x080BBB48). */
static inline void award_ranks(State080BB7AC *state)
{
    s32 i;

    func_080C9574(0x43, 1);
    for (i = 0; i < state->count; i++) {
        s32 value = state->entries[i].node->unit->unknown_D6 +
                    state->entries[i].rank;

        if (value > 10)
            value = 10;
        state->entries[i].node->unit->unknown_D6 = value;
    }
}

s32 func_080BB7AC(State080BB7AC *state)
{
    Entry080BB7AC *entry;
    Node080BB7AC *node;
    s32 i;
    s32 j;

    switch (state->current) {
    case 0:
        func_080A9270();
        state->current = 1;
        break;
    case 1:
        func_080A9298();
        /* 13 entries of 6 motions each. */
        state->motions = func_08022840(0x14B8);
        g_callbacks_0836D4B8[0](state->motions, 0x14B8);
        state->current = 2;
        break;
    case 4:
        func_08096F3C(state->entries[state->selected].node->x,
                      state->entries[state->selected].node->y,
                      state->entries[state->selected].node->z);
        state->current = 3;
        break;
    case 2:
        func_08096F3C(state->owner->x, state->owner->y, state->owner->z);
        state->current = 8;
        push_state(state);
        state->current = 3;
        break;
    case 3:
        if (!func_08096F7C())
            pop_state(state);
        break;
    case 8: {
        Node080BB7AC *owner = state->owner;
        Node080BB7AC *target = state->entries[0].node;

        func_0809836C(owner, 6,
                      func_0809D6BC((target->x >> 5) - (owner->x >> 5),
                                    (target->z >> 5) - (owner->z >> 5)),
                      0);
        g_control_flags_03000940.bldcnt_lo = 0x40;
        g_control_flags_03000940.bldcnt_hi = 0x3F;
        g_control_flags_03000940.bldalpha_lo = 10;
        g_control_flags_03000940.bldalpha_hi = 16;
        data_0836D4C0[0](data_03003B20, 0x20, 0xFF);
        for (i = 0; i < state->count; i++) {
            for (j = 0; j < 6; j++)
                state->motion_count += func_080BB4F8(
                    state->owner, &state->entries[i].node,
                    &state->motions[state->motion_count], j * 42);
        }
        state->timer = 0;
        state->current = 5;
        push_state(state);
        state->current = 4;
        push_state(state);
        state->current = 9;
        func_08141520(0x98);
        break;
    }
    case 9:
        if (++state->timer > 47) {
            func_0809836C(state->owner, 0, state->owner->direction, 0);
            state->owner->unit->facing = state->owner->direction;
            pop_state(state);
        }
        break;
    case 5:
        entry = &state->entries[state->selected];
        node = entry->node;
        func_080A92E4(0, node->x, node->y + 48, node->z,
                      (entry->rank == 1 ? 0x1A : 0x1B));
        state->timer = 0;
        state->current = 6;
        break;
    case 6:
        if (++state->timer > 89) {
            func_08141520(0x1F6);
            if (++state->selected >= state->count) {
                state->current = 10;
                push_state(state);
                state->current = 7;
            } else {
                state->current = 5;
                push_state(state);
                state->current = 4;
            }
        }
        break;
    case 7:
        if (!func_080A9448())
            pop_state(state);
        break;
    case 10:
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.bldcnt_hi = 0;
        func_080A929C();
        func_08022854(state->motions);
        state->motion_count = 0;
        award_ranks(state);
        state->current = 11;
        break;
    case 12:
        award_ranks(state);
        return 0;
    }
    if (!func_080BB424(state) && state->current == 11)
        return 0;
    return 1;
}
