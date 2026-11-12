#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 position;
    u16 unknown_14;
    u16 increment;
} State;

typedef struct {
    u32 first;
    State *second;
} Pair;

typedef struct {
    u16 start;
    u16 end;
    u16 width;
    u16 flags;
} Range;

extern void func_080C7B78(const Pair *source, State **second, u32 *first);

/* Complete target: [0x08021378, 0x080213DA), 98 bytes. */
s32 func_08021378(const Pair *source, Range *range)
{
    State *state;
    u32 first;
    u16 start;
    u16 width;
    s32 end;
    func_080C7B78(source, &state, &first);
    if (range->end <= state->position)
        return 0;
    if (range->start > state->position)
        return 1;
    start = range->start;
    width = range->width;
    end = start + width;
    if (range->end < end) {
        range->flags |= 2;
        return 0;
    }
    if (start < state->position &&
        state->position - start - width >= 0) {
        range->flags |= 1;
        return 0;
    }
    range->start = state->position + state->increment;
    return 1;
}
