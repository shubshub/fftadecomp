#include "ffta.h"

typedef u8 (*TimedCallback08141318)(void *, u32);

typedef struct {
    TimedCallback08141318 callback;
    s16 delay;
    u8 flags;
    u8 unknown_07;
} Callback08141318;

typedef struct {
    s32 elapsed;
    u8 data[0x6BC];
    u8 flags;
    u8 unknown_6C1[3];
} Task08141318;

typedef struct {
    /* The known 081413F8 constructor places metadata after one task and
     * sets count to 1; valid larger counts have not been established. */
    Task08141318 tasks[1];
    Callback08141318 *callbacks;
    u16 count;
    u8 flags;
} State08141318;

/* Target: 0x08141318..0x081413F8 (224 bytes). */
/* active remains 0..255; the existing 0814143C wrapper narrows it to u8.
 * This matching int return does not uniquely establish the original prototype. */
int func_08141318(State08141318 *state)
{
    int active = 0;
    int i;

    for (i = 0; i < state->count; i++) {
        if ((state->callbacks[i].flags & 1) && active)
            continue;
        if (!(state->tasks[i].flags & 2) && (state->flags & 1))
            continue;
        if (state->tasks[i].elapsed < state->callbacks[i].delay) {
            active = 1;
            state->tasks[i].elapsed++;
        } else if (!(state->tasks[i].flags & 1)) {
            u8 result = state->callbacks[i].callback(state->tasks[i].data, state->flags & 1);
            active |= result;
            state->tasks[i].flags |= 2;
            if (!result) {
                state->tasks[i].flags &= ~2;
                state->tasks[i].flags |= 1;
            }
        }
    }
    return active;
}
