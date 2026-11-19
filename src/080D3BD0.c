#include "control_flags.h"

typedef struct {
    u16 duration;
    u8 first;
    u8 second;
} __attribute__((packed)) SequenceEntry;

typedef struct {
    u16 control;
    u16 values;
    u16 count;
    SequenceEntry entries[0];
} __attribute__((packed)) Sequence;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    const Sequence *sequence;
    u8 flags;
    u8 mode;
    u8 control;
    u8 control_high;
    u8 first;
    u8 second;
    u16 delay;
    u16 index;
    u16 first_duration;
    u16 second_duration;
    u8 unknown_12[2];
    InterpolationState first_transition;
    InterpolationState second_transition;
} State;

extern void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);

/* 0x080D3BD0..0x080D3CB4, 228 bytes, 105 instructions.
 * Target:
 * f0b5061c3368114fb089800006301d182978687800020843b84219d1a8780024
 * 3072e8787072b0890130b0811a79597909020004000c11438842e5d331790120
 * 08400028e0d0b481dee70000ffff00000020f0813082a878317a88420cd0301c
 * 1430317aaa782c786b781b0223431b041b140cf0e1fc04e02978687800020843
 * f0817079012810d1e878717a88420cd0301c2030717aea782c786b781b022343
 * 1b041b140cf0c8fc04e029786878000208433082707901280ad10448327a011c
 * 4c310b780a70717a4d3004e0400900030348317a4e3002780170f0bc01bc0047
 * 40090003
 *
 * The ROM tests each record for the 0xFFFF sentinel once, at the top of
 * the loop, and jumps back to it unconditionally.  Written as a leading
 * `if (entry->duration != 0xFFFF) break;` (or as a while loop), the
 * compiler moves the test to the bottom and repeats it before the loop
 * (248 bytes).
 */
void func_080D3BD0(State *state)
{
    const SequenceEntry *entry;

    for (;;) {
        entry = &state->sequence->entries[state->index];
        if (entry->duration == 0xFFFF) {
            state->first = entry->first;
            state->second = entry->second;
            state->index++;
            if (state->index >= state->sequence->count && (state->flags & 1))
                state->index = 0;
        } else {
            break;
        }
    }

    state->first_duration = 0;
    state->second_duration = 0;
    if (entry->first != state->first)
        func_080E0608(&state->first_transition, state->first,
                      entry->first, entry->duration);
    else
        state->first_duration = entry->duration;

    if (state->mode == 1 && entry->second != state->second)
        func_080E0608(&state->second_transition, state->second,
                      entry->second, entry->duration);
    else
        state->second_duration = entry->duration;

    if (state->mode == 1) {
        g_control_flags_03000940.bldalpha_lo = state->first;
        g_control_flags_03000940.bldalpha_hi = state->second;
    } else {
        g_control_flags_03000940.bldy_lo = state->first;
    }
}
