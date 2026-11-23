#include "ffta.h"
#include "control_flags.h"

// Complete [0x080A1E2C, 0x080A215A): 814 bytes, 357 instructions.
//
// Swaps the map positions of up to six pairs of units behind an alpha fade,
// one step per call: the pairs are faded out (EVB up, then EVA down), each
// first unit takes its partner's position and each partner the tile the
// first unit stood on, and the pairs are faded back in.  Phase 0 pushes
// phases 7, 6, 5, 4, 1 and 3 and starts phase 2; each later phase pops the
// next when it is done.  Returns 0 once finished.  func_080A5B98 calls it
// (0x080A5F8A) and tests the result as a u8 (lsls #24 at 0x080A5F8E).

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[0x46];
    void *child;
} Unit080A1E2C;

typedef struct {
    Unit080A1E2C *first[6];
    Unit080A1E2C *second[6];
    u16 count;
    u8 unknown_32[2];
    u16 phase;
    u16 depth;
    u16 stack[8];
} State080A1E2C;

typedef void (*ChildCallback080A1E2C)(void *child, u8 value, u32 first,
                                      u32 second, u32 third, u32 fourth);

/* Not const: the ROM loads the entry again for every call (ldr r4, [r1] at
 * 0x080A1EC6 and 0x080A1EE2); as a const table it is loaded once before
 * each loop and kept in a register (800 bytes). */
extern ChildCallback080A1E2C data_08394034[];
extern void func_08141520(u16 sound);
extern void func_0809993C(void *object, u8 enabled);
extern s32 func_08099C1C(Unit080A1E2C *unit, s8 x, s8 y);
extern void func_08099E68(Unit080A1E2C *unit, s8 x, s8 y);

u8 func_080A1E2C(State080A1E2C *state, void *object, u8 display_only)
{
    s32 i;
    s32 j;
    s32 k;

    switch (state->phase) {
    case 0:
        g_control_flags_03000940.bldcnt_lo = 0x40;
        g_control_flags_03000940.bldcnt_hi = 0x3F;
        g_control_flags_03000940.bldalpha_lo = 0x10;
        g_control_flags_03000940.bldalpha_hi = 0;
        for (i = 0; i < state->count; i++) {
            data_08394034[0](state->first[i]->child, 1, 0, 0, 0, 0);
            data_08394034[0](state->second[i]->child, 1, 0, 0, 0, 0);
        }
        state->phase = 7;
        state->stack[state->depth++] = state->phase;
        state->phase = 6;
        state->stack[state->depth++] = state->phase;
        state->phase = 5;
        state->stack[state->depth++] = state->phase;
        state->phase = 4;
        state->stack[state->depth++] = state->phase;
        state->phase = 1;
        state->stack[state->depth++] = state->phase;
        state->phase = 3;
        state->stack[state->depth++] = state->phase;
        state->phase = 2;
        break;
    case 2:
        func_08141520(0x90);
        if (g_control_flags_03000940.bldalpha_hi <= 15) {
            g_control_flags_03000940.bldalpha_hi++;
            break;
        }
        state->phase = state->stack[--state->depth];
        break;
    case 5:
        if (g_control_flags_03000940.bldalpha_hi != 0) {
            g_control_flags_03000940.bldalpha_hi--;
            break;
        }
        state->phase = state->stack[--state->depth];
        break;
    case 3:
        if (g_control_flags_03000940.bldalpha_lo != 0) {
            g_control_flags_03000940.bldalpha_lo--;
            break;
        }
        state->phase = state->stack[--state->depth];
        break;
    case 4:
        if (g_control_flags_03000940.bldalpha_lo <= 15) {
            g_control_flags_03000940.bldalpha_lo++;
            break;
        }
        state->phase = state->stack[--state->depth];
        break;
    case 1:
        func_0809993C(object, 0);
        for (j = 0; j < state->count; j++) {
            s16 ax = state->first[j]->x;
            s16 ay = state->first[j]->y;

            state->first[j]->x = state->second[j]->x;
            state->first[j]->y = state->second[j]->y;
            state->second[j]->x = ((s8)(ax >> 5)) * 32 + 16;
            state->second[j]->y = ((s8)(ay >> 5)) * 32 + 16;
            state->first[j]->height = func_08099C1C(
                state->first[j], (s8)(state->first[j]->x >> 5),
                (s8)(state->first[j]->y >> 5)) << 4;
            state->second[j]->height = func_08099C1C(
                state->second[j], (s8)(state->second[j]->x >> 5),
                (s8)(state->second[j]->y >> 5)) << 4;
            /* func_08099E68 also moves the units' map records. */
            if (display_only == 0) {
                func_08099E68(state->first[j], (s8)(state->first[j]->x >> 5),
                              (s8)(state->first[j]->y >> 5));
                func_08099E68(state->second[j], (s8)(state->second[j]->x >> 5),
                              (s8)(state->second[j]->y >> 5));
            }
        }
        state->phase = state->stack[--state->depth];
        break;
    case 6:
        func_0809993C(object, 1);
        for (k = 0; k < state->count; k++) {
            data_08394034[0](state->first[k]->child, 0, 0, 0, 0, 0);
            data_08394034[0](state->second[k]->child, 0, 0, 0, 0, 0);
        }
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldalpha_lo = 0x10;
        g_control_flags_03000940.bldalpha_hi = 0;
        state->phase = state->stack[--state->depth];
        break;
    case 7:
        return 0;
    }
    return 1;
}
