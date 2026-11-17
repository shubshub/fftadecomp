#include "ffta.h"

// Target [0x0810BB70, 0x0810BEA0), 816 bytes, 408 instructions.
// Local offset views; original declaration types and extents are unknown.

typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *start;
    s16 *end;
    u8 *flag;
    u32 unknown_10;
    u16 speed;
    u8 unknown_16;
} Descriptor0810BB70;

typedef struct {
    u16 phase;
    u8 angle;
    u8 speed;
    u8 index;
    u8 count;
    u8 unknown_06[2];
    u8 *flag;
    void *object;
    void *children[3];
    s16 x_values[40];
    s16 y_values[40];
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    void *task;
} State0810BB70;

extern const u8 data_08149F14[];
extern const u8 data_08149F17[];
extern const u8 data_08149F1A[];
extern const u8 data_08149F1D[];
extern const u8 data_084FBE7C[];
extern const u8 data_084FBA40[];
extern const u16 data_083A22E0[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern u16 func_08141898(u32 value);
extern void *func_080D5DD4(const void *header, u16 index, s16 x, s16 y,
                           u16 height, u8 mode, u8 palette);
extern void func_0801121C(void *, s16);
extern void func_0801115C(void *, u8);
extern void func_080111A8(void *, u8);
extern void func_08011198(void *);
extern void func_08011428(void *);
extern void *func_080D6334(void *, s16 *, s16 *, u16, u16, u16, s16 *, s16 *,
                           u16, u8, u8, void *);
extern u8 func_080D63C8(void *);
extern u8 func_080D6478(void *);
extern void *func_080D6530(void *);
extern u8 func_080D5F24(void **, u16);
extern void func_080D5C20(void *);

u32 func_0810BB70(void *task, Descriptor0810BB70 *descriptor,
                  State0810BB70 *state)
{
    u8 table_a[3];
    u8 table_b[3];
    u8 table_c[3];
    u8 table_d[3];
    u16 x, y, z;
    int distance;
    u16 value;
    u8 *flag;
    s16 *point;
    s16 dx, dy;

    switch (descriptor->phase) {
    case 0:
        point = descriptor->start;
        state->start_x = point[0];
        state->start_y = point[1];
        point = descriptor->end;
        state->end_x = point[0];
        state->end_y = point[1];
        flag = descriptor->flag;
        state->flag = flag;
        state->speed = descriptor->speed;
        state->count = descriptor->unknown_16 + 1;
        *flag = 0;
        break;
    case 1:
        break;
    case 0x100:
        dx = state->end_x - state->start_x;
        dy = state->end_y - state->start_y;
        state->angle = func_08141860(dx, dy) >> 12;
        state->object = func_080D5DD4(data_084FBE7C, 2, state->start_x,
                                      state->start_y, 0x3DF, 8, 0);
        func_0801121C(state->object, -1);
        func_0801115C(state->object, 0);
        descriptor->phase++;
        break;
    case 0x101:
        func_081443FC(table_a, data_08149F14, 3);
        func_081443FC(table_b, data_08149F17, 3);
        func_081443FC(table_c, data_08149F1A, 3);
        func_081443FC(table_d, data_08149F1D, 3);
        distance = func_08141898(
            ((state->end_x - state->start_x) * (state->end_x - state->start_x)
             + (state->end_y - state->start_y) * (state->end_y - state->start_y))
            << 8) >> 4;
        if (distance > table_b[state->speed])
            value = table_c[state->speed];
        else
            value = table_b[state->speed] + table_c[state->speed] - distance;
        if ((s16)value > table_d[state->speed])
            value = table_d[state->speed];
        state->task = func_080D6334(&state->object, &state->start_x,
            &state->end_x, 0, 0, 40, state->x_values, state->y_values, 0,
            table_a[state->speed], value, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (func_080D63C8(state->task)) {
            *state->flag = 1;
            descriptor->phase++;
        }
        break;
    case 0x103:
        if (*state->flag == 2) {
            if (--state->count == 0) {
                func_0801115C(state->object, 1);
                func_080D5C20(state->task);
                state->phase = 0;
                descriptor->phase++;
            }
        }
        break;
    case 0x104:
        if (state->index <= 2 && state->phase == data_083A22E0[state->index]) {
            func_08011040((Struct08011040 *)state->object, &x, &y, &z);
            state->children[state->index] = func_080D5DD4(data_084FBA40, 3, x,
                                                          y, 0x352, 8, 0);
            func_080111A8(state->children[state->index], 1);
            func_08011198(state->children[state->index]);
            state->index++;
        }
        state->phase++;
        if (func_080D6478(state->task)) {
            *state->flag = 3;
            descriptor->phase++;
        }
        break;
    case 0x105:
        state->task = func_080D6530(state->task);
        if (state->task == 0) {
            if (func_080D5F24(state->children, 3)) {
                func_08011428(state->object);
                state->object = 0;
                *state->flag = 4;
                descriptor->phase = 2;
            }
        }
        break;
    }
    return 0;
}
