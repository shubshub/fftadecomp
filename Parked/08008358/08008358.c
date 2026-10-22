/* 0x08008358 - 296 bytes */
#include "ffta.h"

typedef struct CubicRecord {
    signed long long coordinate;
    signed long long constant;
    signed long long linear;
    signed long long quadratic;
    signed long long cubic;
    u8 unknown_28[40];
} CubicRecord;

typedef struct InterpolationState {
    double *horizontal;
    double *vertical;
    s32 position;
    s32 segment;
    s32 count;
    s32 steps;
    double start;
    double end;
    double increment;
} InterpolationState;

s32 func_08008358(const CubicRecord *records, InterpolationState *state)
{
    const CubicRecord *record;
    signed long long coordinate;
    signed long long delta;
    signed long long value;

    if (state->position >= state->steps) {
        return 0;
    }
    coordinate = state->start + state->increment * state->position;
    state->horizontal[state->position] = coordinate >> 16;
    if (coordinate >= records[state->segment + 1].coordinate) {
        state->segment++;
    }
    record = &records[state->segment];
    delta = coordinate - record->coordinate;
    value = ((record->cubic * delta) >> 16) + record->quadratic;
    value = ((value * delta) >> 16) + record->linear;
    value = ((value * delta) >> 16) + record->constant;
    state->vertical[state->position] = value >> 16;
    state->position++;
    return state->position < state->steps;
}
