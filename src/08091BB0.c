#include "ffta.h"
#include "control_flags.h"

// 0x08091BB0..0x08091DC0: 528 bytes, 233 instructions.
// A seven-phase state machine that slides background 2 in or out
// horizontally while fading the blend weights, with a small phase stack.

typedef struct RequestNode RequestNode;

typedef struct {
    u8 unknown_00[0x14];
    u32 destination;
} TransferState;

typedef struct {
    u8 unknown_00[4];
    u8 *buffer;
    u8 leaving;
    u8 unknown_09[0x3B];
    s16 offset;
    s16 timer;
    u8 unknown_48[4];
    u16 phase;
    u16 depth;
    u16 stack[2];
} SlideState;

extern RequestNode data_0200F47C;
extern TransferState data_030008B0;
extern void func_08022854(u8 *object);
extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);

static inline void ResetTiles(void)
{
    func_08000B20(&data_0200F47C, 0, data_030008B0.destination, 0x400);
}

u32 func_08091BB0(SlideState *state)
{
    switch (state->phase) {
    case 0:
        func_08022854(state->buffer);
        state->buffer = 0;
        state->phase = 1;
        break;
    case 1:
        g_control_flags_03000940.bg2hofs = 0xFFC0;
        state->offset = -0x40;
        state->leaving = 0;
        state->timer = 0x20;
        state->phase = 2;
        state->stack[state->depth++] = state->phase;
        state->phase = 4;
        state->stack[state->depth++] = state->phase;
        state->phase = 6;
        break;
    case 6: {
        int distance = -state->offset;
        int step = distance / 4;
        int weight;
        int other;
        u8 first;

        if (step == 0) {
            if (distance > 0) {
                step = 1;
            } else if (distance < 0) {
                step = -1;
            }
        }
        if (state->leaving) {
            step = -step;
        }
        state->offset += step;
        if (state->leaving) {
            int magnitude = state->offset;

            if (magnitude < 0) {
                magnitude = -magnitude;
            }
            if (magnitude > 0x3F) {
                state->offset = 0x40;
                state->phase = state->stack[--state->depth];
            }
        } else if (state->offset == 0) {
            state->phase = state->stack[--state->depth];
        }
        weight = state->offset;
        if (weight < 0) {
            weight = -weight;
        }
        first = (0x40 - weight) / 4;
        g_control_flags_03000940.bldalpha_lo = first;
        other = state->offset;
        if (other < 0) {
            other = -other;
        }
        g_control_flags_03000940.bldalpha_hi = 0x10 - (0x40 - other) / 4;
        g_control_flags_03000940.bg2hofs = state->offset;
        break;
    }
    case 4:
        if (state->timer == 0 || --state->timer == 0) {
            state->phase = state->stack[--state->depth];
        }
        break;
    case 2:
        state->offset++;
        state->leaving = 1;
        state->phase = 3;
        state->stack[state->depth++] = state->phase;
        state->phase = 5;
        state->stack[state->depth++] = state->phase;
        state->phase = 6;
        break;
    case 5:
        g_control_flags_03000940.bg2hofs = 0;
        ResetTiles();
        state->phase = state->stack[--state->depth];
        break;
    case 3:
        return 0;
    }
    return 1;
}
