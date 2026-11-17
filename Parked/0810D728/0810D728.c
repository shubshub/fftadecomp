#include "ffta.h"

// 0x0810D728..0x0810DA58: 816 bytes, 408 instructions.
// Target: f0b557464e464546e0b48fb00e908946171c09880648814276d081420fdc0129
//         00d17ce1012905dc00291bd077e100000101000080204000814232d06fe10848
//         (first 64 of the 816 bytes)
typedef struct {
    u16 x;
    u16 y;
} Point0810D728;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Point0810D728 *start;
    Point0810D728 *end;
    u8 *flag;
    u32 unknown_10;
    u16 value;
    u8 count;
} Command0810D728;

typedef struct {
    u16 timer;
    u8 direction;
    u8 value;
    u8 step;
    u8 remaining;
    u8 unknown_06[2];
    u8 *flag;
    void *sprite;
    void *rings[3];
    s16 x_values[40];
    s16 y_values[40];
    Point0810D728 start;
    Point0810D728 end;
    void *task;
} State0810D728;

extern const u8 data_08149F24[];
extern const u8 data_08149F27[];
extern const u8 data_08149F2A[];
extern const u8 data_08149F2D[];
extern const u8 data_0850873C[];
extern const u16 data_083A2920[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern u16 func_08141898(u32 value);
extern u32 func_080D5DD4(const void *header, u16 index, s16 x, s16 y,
                         u16 height, u8 mode, u8 palette);
extern void func_0801121C(void *object, s16 value);
extern void func_0801115C(void *object, u8 enabled);
extern void *func_080D6334(void *object_reference, const Point0810D728 *start,
                           const Point0810D728 *end, u16 value_0C,
                           u16 value_0E, u16 count, const s16 *x_values,
                           const s16 *y_values, u16 value_14, u8 option_01,
                           u8 option_00, void *parent);
extern u8 func_080D63C8(void *task);
extern void func_080D5C20(void *task);
extern void func_080111A8(void *object, u8 enabled);
extern void func_08011198(void *object);
extern u8 func_080D6478(void *task);
extern void *func_080D6530(void *task);
extern u8 func_080D5F24(void **objects, u16 count);
extern void func_08011428(void *object);

u32 func_0810D728(void *task, Command0810D728 *command, State0810D728 *state)
{
    u8 a[3];
    u8 b[3];
    u8 c[3];
    u8 d[3];
    s16 x;
    s16 y;
    s16 z;
    s32 distance;
    u16 dx;
    u16 dy;
    s16 length;
    void *next;
    Point0810D728 *point;
    u8 *flag;

    switch (command->phase) {
    case 0:
        point = command->start;
        state->start.x = point->x;
        state->start.y = point->y;
        point = command->end;
        state->end.x = point->x;
        state->end.y = point->y;
        flag = command->flag;
        state->flag = flag;
        state->value = command->value;
        state->remaining = command->count + 1;
        *flag = 0;
        break;
    case 1:
        break;
    case 0x100:
        dx = state->end.x - state->start.x;
        dy = state->end.y - state->start.y;
        state->direction = func_08141860(dx, dy) >> 12;
        state->sprite = (void *)func_080D5DD4(data_0850873C, 0, state->start.x,
                                              state->start.y, 0x3FD, 6, 0);
        func_0801121C(state->sprite, -1);
        func_0801115C(state->sprite, 0);
        command->phase++;
        break;
    case 0x101:
        func_081443FC(a, data_08149F24, 3);
        func_081443FC(b, data_08149F27, 3);
        func_081443FC(c, data_08149F2A, 3);
        func_081443FC(d, data_08149F2D, 3);
        distance = func_08141898((((s16)state->end.x - (s16)state->start.x)
                                  * ((s16)state->end.x - (s16)state->start.x)
                                  + ((s16)state->end.y - (s16)state->start.y)
                                  * ((s16)state->end.y - (s16)state->start.y)) << 8) >> 4;
        if (distance > b[state->value])
            length = c[state->value];
        else
            length = b[state->value] + c[state->value] - distance;
        if (length > d[state->value])
            length = d[state->value];
        state->task = func_080D6334(&state->sprite, &state->start, &state->end,
                                    0, 0, 40, state->x_values, state->y_values,
                                    0, a[state->value], length, task);
        command->phase++;
        break;
    case 0x102:
        if (func_080D63C8(state->task)) {
            *state->flag = 1;
            command->phase++;
        }
        break;
    case 0x103:
        if (*state->flag == 2) {
            if (--state->remaining == 0) {
                func_0801115C(state->sprite, 1);
                func_080D5C20(state->task);
                state->timer = 0;
                command->phase++;
            }
        }
        break;
    case 0x104:
        if (state->step <= 2 && state->timer == data_083A2920[state->step]) {
            func_08011040((Struct08011040 *)state->sprite, (u16 *)&x, (u16 *)&y, (u16 *)&z);
            state->rings[state->step] = (void *)func_080D5DD4(
                data_0850873C, 0, x, y, 0x3FD, 6, 0);
            func_080111A8(state->rings[state->step], 1);
            func_08011198(state->rings[state->step]);
            state->step++;
        }
        state->timer++;
        if (func_080D6478(state->task)) {
            *state->flag = 3;
            command->phase++;
        }
        break;
    case 0x105:
        next = func_080D6530(state->task);
        state->task = next;
        if (next == 0) {
            if (func_080D5F24(state->rings, 3)) {
                func_08011428(state->sprite);
                state->sprite = next;
                *state->flag = 4;
                command->phase = 2;
            }
        }
        break;
    }
    return 0;
}
