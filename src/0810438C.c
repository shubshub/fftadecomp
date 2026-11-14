#include "ffta.h"

// Complete [0x0810438C, 0x0810457C): 496 bytes, 248 instructions.

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xE];
    u16 mode;
} Command0810438C;

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

typedef struct {
    u8 mode;
    u8 count;
    s16 x;
    s16 y;
    u16 timer;
    u32 unknown_08;
    void *object;
    void *opening;
    void *handles[3];
    struct InterpolationState interpolation;
    void *task;
    void *script;
} Runtime0810438C;

typedef struct {
    u32 unknown_00;
    void *object;
    u32 unknown_08;
    u32 enabled;
    u8 unknown_10[4];
    u16 kind;
    u16 mode;
    u32 unknown_18;
} Descriptor0810438C;

extern const u8 data_0839F488[];
extern const u8 data_0839F4B8[];
extern const u8 data_08506BA8[];

extern void *func_080E03F8(void *object, const void *data, u32 mode,
                          u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080D8924(void *object, u8 index, u16 value, void *context);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void func_080D8C58(void *object, s16 *x, s16 *y);
extern void *func_080D5CC0(const void *data, u16 index, s16 x, s16 y,
                          u16 value, u8 priority, u8 first, u8 second);
extern void func_080E0608(struct InterpolationState *state, s16 start,
                          s16 end, s16 duration);
extern u8 func_081042C8(void **handles, struct InterpolationState *state,
                        s16 x, s16 y);
extern u32 func_080E8B24(void *task, void *control, void *state);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *),
                          u32 size, void *descriptor, void *parent);
extern void *func_080E051C(void *task);

u32 func_0810438C(void *context, Command0810438C *command,
                  Runtime0810438C *runtime)
{
    Descriptor0810438C descriptor;

    switch (command->state) {
    case 0: {
        u32 mode;

        runtime->mode = command->mode;
        runtime->object = command->object;
        mode = 4;
        if (runtime->mode)
            mode = 0;
        runtime->opening = func_080E03F8(runtime->object, data_0839F488,
                                        mode, 1, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 lane;

        runtime->opening = func_080E05DC(runtime->opening);
        if (runtime->opening != 0)
            break;
        runtime->count = func_080D8924(runtime->object, 0, 60, context);
        if (runtime->mode) {
            if (!runtime->count)
                command->state = 0x103;
            else
                command->state = 0x102;
            break;
        }
        runtime->script = func_080DFD8C(data_0839F4B8, 1, 4, 0, context);
        if (!runtime->count) {
            command->state = 0x103;
            break;
        }
        func_080D8C58(runtime->object, &runtime->x, &runtime->y);
        for (lane = 0; lane < 3; lane++)
            runtime->handles[lane] = func_080D5CC0(data_08506BA8, lane, 0, 0,
                                                   0x3E5, 7, 0, 0);
        func_080E0608(&runtime->interpolation,
                      60, 0x13C, 0xA4);
        func_081042C8(runtime->handles,
                      &runtime->interpolation,
                      runtime->x, runtime->y);
        runtime->timer = 90;
        command->state++;
        break;
    }
    case 0x101:
        func_081042C8(runtime->handles,
                      &runtime->interpolation,
                      runtime->x, runtime->y);
        if (--runtime->timer == 0)
            command->state++;
        break;
    case 0x102:
        descriptor.kind = 0xDF;
        descriptor.mode = runtime->mode;
        descriptor.object = runtime->object;
        descriptor.unknown_08 = 0;
        descriptor.enabled = 1;
        runtime->task = func_08005B6C(func_080E8B24, 0x30, &descriptor,
                                      context);
        func_081042C8(runtime->handles,
                      &runtime->interpolation,
                      runtime->x, runtime->y);
        command->state++;
        break;
    case 0x103:
        if (func_081042C8(runtime->handles,
                          &runtime->interpolation,
                          runtime->x, runtime->y)) {
            runtime->task = func_080E051C(runtime->task);
            if (runtime->task == 0)
                command->state = 2;
        }
        break;
    }
    return 0;
}
