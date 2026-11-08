#include "ffta.h"

typedef struct TransferRecord {
    u8 status, kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct {
    u8 index;
    s8 selection, previous_selection;
    u8 priority;
    s16 x, y, target_x, target_y, previous_x, previous_y;
    u8 flags, buffer;
    TransferRecord transfers[2][2];
} DisplayState;

extern const u8 data_08418FCC[];
extern u8 data_06013600[], data_06013700[];
extern u8 func_0801CC18(u8, u8);
extern s32 func_081426B8(s32, s32);
extern void func_08000A98(TransferRecord *, const void *, void *, u16);
extern void func_08000B20(TransferRecord *, u16, void *, u16);
extern void func_080A8F60(DisplayState *);
extern void func_080A8FBC(DisplayState *);

/* Complete target [0x080A901C, 0x080A925C): 576 bytes including pools. */
void func_080A901C(DisplayState *state, s8 column, s8 row)
{
    s32 dx, dy, step_x, step_y;
    if (!(state->flags & 1))
        return;

    if (state->selection != column || state->previous_selection != row) {
        u8 value = func_0801CC18(column, row);
        if (value != state->index) {
            s32 tens = func_081426B8(value, 10);
            s32 ones = value - tens * 10;
            state->buffer ^= 1;
            if (tens == 0)
                func_08000B20(&state->transfers[state->buffer][0], 0, data_06013600, 128);
            else
                func_08000A98(&state->transfers[state->buffer][0], data_08418FCC + tens * 256, data_06013600, 128);
            func_08000A98(&state->transfers[state->buffer][1], data_08418FCC + ones * 256, data_06013700, 128);
        }
        state->index = value;
        state->selection = column;
        state->previous_selection = row;
    }
    dx = state->target_x - state->x;
    dy = state->target_y - state->y;
    if (dx == 0 && dy == 0) {
        if (state->flags & 2) {
            state->flags = 0;
            if (state->y == -32)
                func_080A8F60(state);
            else
                func_080A8FBC(state);
        } else if ((u16)(state->y + 31) > 190)
            state->flags = 0;
        state->flags &= ~6;
        return;
    }
    if (state->flags & 4) {
        s16 direction_x = state->target_x - state->previous_x;
        s16 direction_y = state->target_y - state->previous_y;
        if (direction_x != 0)
            direction_x = func_081426B8(direction_x, direction_x < 0 ? -direction_x : direction_x);
        if (direction_y != 0)
            direction_y = func_081426B8(direction_y, direction_y < 0 ? -direction_y : direction_y);
        dx = state->x - state->previous_x;
        dy = state->y - state->previous_y;
        if (direction_x != 0 && dx == 0)
            dx = direction_x;
        if (direction_y != 0 && dy == 0)
            dy = direction_y;
    }
    step_x = func_081426B8(dx, 3);
    if (step_x == 0 && dx != 0)
        step_x = func_081426B8(dx, dx < 0 ? -dx : dx) * 4;
    step_y = func_081426B8(dy, 3);
    if (step_y == 0 && dy != 0)
        step_y = func_081426B8(dy, dy < 0 ? -dy : dy) * 4;
    state->x += step_x;
    state->y += step_y;
    dx = state->target_x - state->x;
    dy = state->target_y - state->y;
    if ((dx > 0 && step_x < 0) || (dx < 0 && step_x > 0))
        state->x = state->target_x;
    if ((dy > 0 && step_y < 0) || (dy < 0 && step_y > 0))
        state->y = state->target_y;
}
