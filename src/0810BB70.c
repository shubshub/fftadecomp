#include "ffta.h"

/* Complete [0x0810BB70, 0x0810BEA0), 816 bytes.
 * The child callback that func_0810BEA0 starts three times, once per slot
 * (0, 1, 2): it moves an object from start to end and leaves up to three
 * more objects at its position on the frames data_083A22E0 lists
 * (10, 20 and 30).
 * func_0810D728 is the same callback with other tables and graphics.
 * The four 3-byte tables are indexed by the slot. */

typedef struct {
    s16 x;
    s16 y;
} Point;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Point *start;
    Point *end;
    u8 *status;
    u32 unknown_10;
    u16 slot;
    u8 delay;
} ChildDescriptor;

typedef struct {
    u16 timer;
    u8 direction;
    u8 slot;
    u8 trail_count;
    u8 delay;
    u8 unknown_06[2];
    u8 *status;
    void *object;
    void *trails[3];
    s16 x_values[40];
    s16 y_values[40];
    Point start;
    Point end;
    void *motion;
} ChildState;

extern const u8 data_08149F14[3];
extern const u8 data_08149F17[3];
extern const u8 data_08149F1A[3];
extern const u8 data_08149F1D[3];
extern const u8 data_084FBE7C[];
extern const u8 data_084FBA40[];
extern const u16 data_083A22E0[3];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern u16 func_08141898(u32 value);
extern void *func_080D5DD4(const void *header, u16 index, s16 x, s16 y,
                           u16 height, u8 mode, u8 palette);
extern void func_0801121C(void *object, s16 value);
extern void func_0801115C(void *object, u8 enabled);
extern void func_080111A8(void *object, u8 enabled);
extern void func_08011198(void *object);
extern void func_08011428(void *object);
extern void *func_080D6334(void *object_reference, const Point *start,
                           const Point *end, u16 value_0C, u16 value_0E,
                           u16 count, const s16 *x_values,
                           const s16 *y_values, u16 value_14, u8 option_01,
                           u8 option_00, void *parent);
extern u8 func_080D63C8(void *task);
extern u8 func_080D6478(void *task);
extern void *func_080D6530(void *task);
extern u8 func_080D5F24(void **objects, u16 count);
extern u32 func_080D5C20(void *task);

u32 func_0810BB70(void *task, ChildDescriptor *descriptor, ChildState *state)
{
    u8 option[3];
    u8 range[3];
    u8 minimum[3];
    u8 maximum[3];
    u16 x, y, z;
    s32 distance;
    s16 value;
    u8 *status;
    Point *point;
    s16 dx, dy;

    switch (descriptor->phase) {
    case 0:
        point = descriptor->start;
        state->start.x = point->x;
        state->start.y = point->y;
        point = descriptor->end;
        state->end.x = point->x;
        state->end.y = point->y;
        status = descriptor->status;
        state->status = status;
        state->slot = descriptor->slot;
        state->delay = descriptor->delay + 1;
        *status = 0;
        break;
    case 1:
        break;
    case 0x100:
        dx = state->end.x - state->start.x;
        dy = state->end.y - state->start.y;
        state->direction = func_08141860(dx, dy) >> 12;
        state->object = func_080D5DD4(data_084FBE7C, 2, state->start.x,
                                      state->start.y, 0x3DF, 8, 0);
        func_0801121C(state->object, -1);
        func_0801115C(state->object, 0);
        descriptor->phase++;
        break;
    case 0x101:
        func_081443FC(option, data_08149F14, 3);
        func_081443FC(range, data_08149F17, 3);
        func_081443FC(minimum, data_08149F1A, 3);
        func_081443FC(maximum, data_08149F1D, 3);
        distance = func_08141898(
            ((state->end.x - state->start.x) * (state->end.x - state->start.x)
             + (state->end.y - state->start.y) * (state->end.y - state->start.y))
            << 8) >> 4;
        if (distance > range[state->slot])
            value = minimum[state->slot];
        else
            value = range[state->slot] + minimum[state->slot] - distance;
        if (value > maximum[state->slot])
            value = maximum[state->slot];
        state->motion = func_080D6334(&state->object, &state->start,
            &state->end, 0, 0, 40, state->x_values, state->y_values, 0,
            option[state->slot], value, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (func_080D63C8(state->motion)) {
            *state->status = 1;
            descriptor->phase++;
        }
        break;
    case 0x103:
        if (*state->status == 2) {
            if (--state->delay == 0) {
                func_0801115C(state->object, 1);
                func_080D5C20(state->motion);
                state->timer = 0;
                descriptor->phase++;
            }
        }
        break;
    case 0x104:
        if (state->trail_count <= 2
            && state->timer == data_083A22E0[state->trail_count]) {
            func_08011040((Struct08011040 *)state->object, &x, &y, &z);
            state->trails[state->trail_count] =
                func_080D5DD4(data_084FBA40, 3, x, y, 0x352, 8, 0);
            func_080111A8(state->trails[state->trail_count], 1);
            func_08011198(state->trails[state->trail_count]);
            state->trail_count++;
        }
        state->timer++;
        if (func_080D6478(state->motion)) {
            *state->status = 3;
            descriptor->phase++;
        }
        break;
    case 0x105:
        state->motion = func_080D6530(state->motion);
        if (state->motion == 0) {
            if (func_080D5F24(state->trails, 3)) {
                func_08011428(state->object);
                state->object = 0;
                *state->status = 4;
                descriptor->phase = 2;
            }
        }
        break;
    }
    return 0;
}
