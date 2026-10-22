/* 0x080082EC - 106 bytes */
#include "ffta.h"

typedef struct CoordinateRecord {
    signed long long coordinate;
    u8 unknown_08[72];
} CoordinateRecord;

typedef struct InterpolationState {
    u32 first;
    u32 second;
    u32 unknown_08;
    u32 unknown_0c;
    s32 count;
    s32 steps;
    double start;
    double end;
    double increment;
} InterpolationState;

void func_080082EC(const CoordinateRecord *records, InterpolationState *state,
                  u32 first, u32 second, s32 count, s32 steps)
{
    double start;
    double end;

    state->first = first;
    state->second = second;
    state->count = count;
    state->steps = steps;
    start = records[0].coordinate;
    state->start = start;
    end = records[count - 1].coordinate;
    state->end = end;
    state->increment = (end - start) / steps;
    state->unknown_0c = 0;
    state->unknown_08 = 0;
}
