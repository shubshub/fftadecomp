#include "ffta.h"

/* The unit's record, as src/080BAEE8.c declares it: the tile at 0xF6. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 tile_x;
    u8 tile_z;
    s8 direction;
} Unit080BBE00;

/* The unit on the map, as src/080BAEE8.c's Subject and src/080BB7AC.c's
 * Node: y is the height. */
typedef struct {
    Unit080BBE00 *unit;
    u32 unknown_04;
    s16 x, y, z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u8 unknown_34[0x20];
    void *animation;
} Subject080BBE00;

typedef struct {
    Subject080BBE00 *subject;
    u8 tile_x;
    u8 tile_z;
    u8 unknown_06[2];
} Entry080BBE00;

/* src/080BBD34.c */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s8 count;
    u8 unknown07;
} Countdown080BBE00;

/* The state stack, as src/08092784.c declares it. */
typedef struct {
    u16 current, depth, stack[34];
} Phase080BBE00;

/* 0x1C8 bytes, allocated by func_080BC950. */
typedef struct {
    void *context;
    Subject080BBE00 *unit;
    Entry080BBE00 entries[13];
    Countdown080BBE00 countdowns[32];
    u8 index;
    u8 count;
    u8 flag;
    u8 unknown_173;
    s16 timer;
    u8 unknown_176[2];
    void *task;
    void *list;
    Phase080BBE00 phase;
} State080BBE00;

/* The state stack's push and pop, as src/080BB7AC.c and src/0809EA60.c
 * write them. */
static inline void push_state(Phase080BBE00 *phase)
{
    phase->stack[phase->depth++] = phase->current;
}

static inline void pop_state(Phase080BBE00 *phase)
{
    phase->current = phase->stack[--phase->depth];
}

extern s32 func_080BBD34(Countdown080BBE00 *entries, s32 count, void *context);
extern void *func_080BDD08(void *context);
extern u8 func_080BDD40(void *list);
extern u8 func_080BDD5C(void *list);
extern void func_080BDD50(void *list);
extern Subject080BBE00 *func_080BDD70(void *list, u8 *tile_x, u8 *tile_z);
extern void func_080D376C(void);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern void *func_080D3508(u16 id, void *object, u32 arg);
extern u8 func_080E2BDC(void *task);
extern void func_080D3864(void *task);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);
extern void func_0809A298(Subject080BBE00 *subject, u16 value, s8 adjustment);
extern void func_08141520(u16 sound);
extern void func_0809836C(Subject080BBE00 *subject, u16 action, s8 direction,
                          u16 option);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern s32 func_08099C1C(Subject080BBE00 *subject, s8 tile_x, s8 tile_z);
extern void (*data_0839403C)(void *);

/* Finds an idle countdown in the (entries, count) array that func_080BBD34
 * (src/080BBD34.c) steps.  The bound is the count argument: the loop test is
 * `cmp r2, #0x20; blt` at 0x080BC298, where a literal `i < 32` folds to
 * `i <= 31`.  Returns 0 when all are busy; case 7 does not check, but each
 * of the at most 13 entries starts only two 16-frame countdowns, so one of
 * the 32 is always idle. */
static inline Countdown080BBE00 *free_countdown(Countdown080BBE00 *entries,
                                                 s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, entries++) {
        if (entries->count == 0)
            return entries;
    }
    return 0;
}

/* Complete [0x080BBE00, 0x080BC3AE): 1454 bytes, 646 instructions. */
u32 func_080BBE00(State080BBE00 *state)
{
    u8 busy = func_080BBD34(state->countdowns, 32, state->task);

    switch (state->phase.current) {
    case 0:
        state->list = func_080BDD08(state->context);
        state->phase.current = 1;
        break;
    case 1:
        if (func_080BDD40(state->list))
            break;
        if (!func_080BDD5C(state->list)) {
            func_080BDD50(state->list);
            if (state->count == 0) {
                state->phase.current = 17;
                break;
            }
            state->phase.current = 6;
            push_state(&state->phase);
            state->phase.current = 15;
            push_state(&state->phase);
            state->phase.current = 3;
            push_state(&state->phase);
            state->phase.current = 2;
            push_state(&state->phase);
            state->phase.current = 5;
            break;
        }
        state->entries[state->count].subject =
            func_080BDD70(state->list, &state->entries[state->count].tile_x,
                          &state->entries[state->count].tile_z);
        state->entries[state->count].subject->unit->tile_x =
            state->entries[state->count].tile_x;
        state->entries[state->count].subject->unit->tile_z =
            state->entries[state->count].tile_z;
        state->count++;
        func_080BDD50(state->list);
        state->list = 0;
        state->phase.current = 0;
        break;
    case 5:
        if (!state->flag)
            break;
        func_080D376C();
        pop_state(&state->phase);
        break;
    case 2:
        if (!func_080D37F8())
            break;
        if (!func_080D39B0())
            break;
        pop_state(&state->phase);
        break;
    case 3:
        state->task = func_080D3508(0x15B, 0, 0);
        state->phase.current = 4;
        break;
    case 4:
        if (!func_080E2BDC(state->task))
            break;
        pop_state(&state->phase);
        break;
    case 15:
        if (state->unit) {
            func_0809A298(state->unit, 0x3C, 0);
            data_0839403C(state->unit->animation);
            func_08141520(0x87);
            state->phase.current = 16;
            state->timer = 0;
            break;
        }
        pop_state(&state->phase);
        break;
    case 16:
        if (++state->timer <= 63)
            break;
        func_0809836C(state->unit, 0, state->unit->unit->direction, 0);
        data_0839403C(state->unit->animation);
        state->timer = 0;
        pop_state(&state->phase);
        break;
    case 6:
        if (state->index >= state->count) {
            state->phase.current = 17;
            push_state(&state->phase);
            state->phase.current = 13;
            push_state(&state->phase);
            state->phase.current = 12;
            if (state->unit) {
                func_08096F3C(state->unit->x, state->unit->y, state->unit->z);
                push_state(&state->phase);
                state->phase.current = 15;
                push_state(&state->phase);
                state->phase.current = 9;
            }
            break;
        }
        push_state(&state->phase);
        state->phase.current = 11;
        push_state(&state->phase);
        state->phase.current = 7;
        push_state(&state->phase);
        state->phase.current = 8;
        push_state(&state->phase);
        state->phase.current = 10;
        push_state(&state->phase);
        state->phase.current = 7;
        push_state(&state->phase);
        state->phase.current = 8;
        break;
    case 11:
        state->entries[state->index].subject->flags &= ~0x20001;
        state->index++;
        pop_state(&state->phase);
        break;
    case 10:
        state->entries[state->index].subject->x =
            (s8)state->entries[state->index].tile_x * 32 + 16;
        state->entries[state->index].subject->z =
            (s8)state->entries[state->index].tile_z * 32 + 16;
        state->entries[state->index].subject->y =
            func_08099C1C(state->entries[state->index].subject,
                          state->entries[state->index].subject->unit->tile_x,
                          state->entries[state->index].subject->unit->tile_z) << 4;
        state->entries[state->index].subject->flags |= 1;
        func_0809836C(state->entries[state->index].subject, 0,
                      state->entries[state->index].subject->direction, 0);
        pop_state(&state->phase);
        break;
    case 7: {
        Countdown080BBE00 *slot = free_countdown(state->countdowns, 32);

        slot->x = state->entries[state->index].subject->x;
        slot->y = state->entries[state->index].subject->y;
        slot->z = state->entries[state->index].subject->z;
        state->entries[state->index].subject->flags |= 0x20000;
        state->entries[state->index].subject->flags &= ~1;
        func_08141520(0xDD);
        slot->count = 16;
        pop_state(&state->phase);
        break;
    }
    case 8:
        func_08096F3C(state->entries[state->index].subject->x,
                      state->entries[state->index].subject->y,
                      state->entries[state->index].subject->z);
        state->phase.current = 9;
        break;
    case 9:
        if (func_08096F7C())
            break;
        pop_state(&state->phase);
        break;
    case 12:
        if (busy)
            break;
        func_080D3864(state->task);
        pop_state(&state->phase);
        break;
    case 13:
        func_080D37AC();
        state->phase.current = 14;
        break;
    case 14:
        if (!func_080D37C4())
            break;
        pop_state(&state->phase);
        break;
    case 17:
        return 0;
    }
    return 1;
}
