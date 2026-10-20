#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} CoordinateRecord;

typedef struct {
    CoordinateRecord *record;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
} CoordinateObject;

s32 func_08099C1C(void *object, s8 x, s8 y);

void func_08099E68(void *object, s8 x, s8 y)
{
    CoordinateObject *state = object;

    state->x = x * 32 + 16;
    state->y = y * 32 + 16;
    state->height = func_08099C1C(object, x, y) * 16;
    state->record->x = x;
    state->record->y = y;
}
