#include "ffta.h"

struct Command0810493C {
    u16 state;
    u8 unknown_02[18];
    u16 index;
    u16 direction;
};

struct Tween0810493C {
    s16 value;
    u8 unknown_02[10];
};

struct Runtime0810493C {
    u32 unknown_00;
    u16 timer;
    s8 direction;
    u8 index;
    void *objects[2];
    struct Tween0810493C x;
    struct Tween0810493C y;
};

struct Point0810493C {
    s16 x;
    s16 y;
};

extern const u8 data_0839F75C[];
extern const struct Point0810493C data_0839F764[];
extern const struct Point0810493C data_0839F78C[];
extern const u8 data_08506E80[];
extern const u8 data_0839F7B4[];

extern void func_080E0608(struct Tween0810493C *tween, s16 start, s16 end,
                          u16 duration);
extern void *func_080D5CC0(const void *data, u8 id, s16 x, s16 y,
                          u16 resource, u16 priority, u32 first, u32 second);
extern void func_08011118(void *object, u8 enabled);
extern void func_0801121C(void *object, s16 value);
extern void func_08011058(void *object, u8 enabled);
extern void func_080E064C(struct Tween0810493C *tween);
extern void func_080107D4(void *object, s16 x, s16 y, u16 value);
extern u8 func_080E0690(struct Tween0810493C *tween);
extern void func_080D5F74(void **objects, u16 count);

/* Complete [0x0810493C, 0x08104AEC): 432 bytes, 187 instructions. */
u32 func_0810493C(void *context, struct Command0810493C *command,
                  struct Runtime0810493C *runtime)
{
    switch (command->state) {
    case 0:
        runtime->index = command->index;
        runtime->direction = command->direction;
        runtime->timer = data_0839F75C[runtime->index] + 1;
        break;
    case 0x100:
        runtime->timer--;
        if (runtime->timer != 0)
            break;
        func_080E0608(&runtime->x,
            data_0839F764[runtime->direction * 5 + runtime->index].x,
            data_0839F78C[runtime->direction * 5 + runtime->index].x, 90);
        func_080E0608(&runtime->y,
            data_0839F764[runtime->direction * 5 + runtime->index].y,
            data_0839F78C[runtime->direction * 5 + runtime->index].y, 90);
        runtime->objects[0] = func_080D5CC0(data_08506E80, 0, runtime->x.value,
            runtime->y.value, 0x3A0, 6, 0, 0);
        runtime->objects[1] = func_080D5CC0(data_08506E80, 1, runtime->x.value,
            runtime->y.value, 0x3A0, 6, 0, 0);
        if (runtime->direction) {
            func_08011118(runtime->objects[0], 1);
            func_08011118(runtime->objects[1], 1);
        }
        func_0801121C(runtime->objects[0], -1);
        func_0801121C(runtime->objects[1], -1);
        func_08011058(runtime->objects[0], data_0839F7B4[runtime->index]);
        func_08011058(runtime->objects[1], data_0839F7B4[runtime->index]);
        command->state++;
        break;
    case 0x101:
        func_080E064C(&runtime->x);
        func_080E064C(&runtime->y);
        func_080107D4(runtime->objects[0], runtime->x.value, runtime->y.value, 0);
        func_080107D4(runtime->objects[1], runtime->x.value, runtime->y.value, 0);
        if (func_080E0690(&runtime->x)) {
            func_080D5F74(runtime->objects, 2);
            command->state++;
        }
        break;
    case 0x102:
        command->state = 2;
        break;
    }
    return 0;
}
