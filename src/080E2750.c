#include "ffta.h"
#include "control_flags.h"

// 0x080E2750..0x080E2848: 248 bytes, 113 instructions.

typedef struct {
    u16 state;
} Command080E2750;

typedef struct {
    u16 id;
    u16 value;
    u16 count;
    u16 delay;
    u8 mode;
} Fade080E2750;

typedef struct {
    u8 active;
    u16 timer;
    u16 fade_in;
    s16 hold;
    u16 fade_out;
    u8 level;
    void *fade;
    Fade080E2750 descriptor;
} State080E2750;

extern void *func_080D3E9C(const Fade080E2750 *descriptor, void *parent);
extern void *func_080D3F08(void *fade);

u32 func_080E2750(void *task, Command080E2750 *command, State080E2750 *state)
{
    void *fade;

    switch (command->state) {
    case 0:
    case 1:
        break;
    case 0x100:
        if (!state->active) {
            command->state = 2;
            break;
        }
        state->descriptor.id = 0xBF;
        state->descriptor.value = 0;
        state->descriptor.count = 1;
        state->descriptor.delay = state->fade_in;
        state->descriptor.mode = state->level;
        state->fade = func_080D3E9C(&state->descriptor, task);
        command->state++;
        break;
    case 0x101:
        state->fade = func_080D3F08(state->fade);
        if (state->fade) {
            break;
        }
        if (state->hold == 0) {
            state->descriptor.value = state->level;
            state->descriptor.count = 1;
            state->descriptor.delay = state->fade_out;
            state->descriptor.mode = 0;
            state->fade = func_080D3E9C(&state->descriptor, task);
            command->state = 0x103;
        } else {
            state->timer = state->hold;
            command->state++;
        }
        break;
    case 0x102:
        if (--state->timer) {
            break;
        }
        state->descriptor.value = state->level;
        state->descriptor.count = 1;
        state->descriptor.delay = state->fade_out;
        state->descriptor.mode = 0;
        state->fade = func_080D3E9C(&state->descriptor, task);
        command->state++;
        break;
    case 0x103:
        fade = func_080D3F08(state->fade);
        state->fade = fade;
        if (fade) {
            break;
        }
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.bldy_lo = 0;
        state->active = 0;
        command->state = 2;
        break;
    }
    return 0;
}
