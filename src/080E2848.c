#include "control_flags.h"

typedef struct {
    u16 first;
    u16 second;
    u16 third;
    u8 level;
} TransitionParameters080E2848;

typedef struct {
    u8 active;
    u8 unknown_01[3];
    u16 first;
    u16 second;
    u16 third;
    u8 level;
    u8 unknown_0B;
    void *child;
} TransitionState080E2848;

extern void *func_08005BFC(void *task);
extern void func_080D3EFC(void *task);
extern void func_08005BA8(void *task, u16 value);

/* Complete [0x080E2848, 0x080E28A8): 96 bytes, including the literal pool. */
void func_080E2848(void *task, const TransitionParameters080E2848 *parameters)
{
    TransitionState080E2848 *state = func_08005BFC(task);

    if (state->child != 0) {
        func_080D3EFC(state->child);
        state->child = 0;
    }
    state->first = parameters->first;
    state->second = parameters->second;
    state->third = parameters->third;
    state->level = parameters->level;
    if (state->level > 16)
        state->level = 16;
    func_08005BA8(task, 0x100);
    g_control_flags_03000940.bldcnt_lo = 0;
    g_control_flags_03000940.bldy_lo = 0;
    state->active = 1;
}
