#include "ffta.h"
#include "control_flags.h"

/* Target 0x080F6520, complete [0x080F6520, 0x080F695A), 1082 bytes, 456 reachable instructions. */

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[4];
    u32 options;
    u8 unknown_10[4];
    s16 kind;
    u16 flag;
} Command080F6520;

typedef struct {
    s16 x;
    s16 y;
    u8 variant;
    u8 variant_flag;
    u8 mode;
    s8 count;
    u8 timer;
    u8 unknown_09;
    u16 index;
    u8 ready;
    u8 unknown_0D[3];
    u32 parameters;
    void *movement;
    u32 second_parameters[3];
    void *second_movement;
    void *layer;
    void *scene;
    void *tasks[4];
    void *related;
    void *texts[2];
    void *follower;
    void *object;
    void *opening;
    void *initiator;
    void *script;
} State080F6520;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 flags;
    u8 unknown_16[6];
} Descriptor080F6520;

extern const u8 data_0839B800[];
extern const u8 data_0839B8BC[];
extern const u8 data_088F58EC[];
extern const u8 data_0894A07C[];
extern const u8 data_0894A0B0[];
extern const u8 data_0894D69C[];
extern const u8 data_0839B8C4[];
extern const u8 data_088EF6CC[];
extern const u8 data_0894A0E8[];
extern const u8 data_0894AAB0[];
extern const u8 data_0839B848[];
extern const u8 data_0839B8CC[];
extern const u8 data_0839B860[];
extern const u8 data_0839B8D4[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);
extern u32 func_080F6490(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *object, const void *data, u32 mode,
                           u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern void *func_080DD47C(void *object);
extern u8 func_080DD494(void *object);
extern void func_080DE10C(void *related, u32 mode);
extern void *func_080DE4B0(void *object, u8 *result, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *parent);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                           u32 third, void *context);
extern void func_080DBDC8(void *related, s16 *x, s16 *y);
extern void func_080D7220(const void *resource, u8 bank, u8 channel,
                          s16 x, s16 y, u16 value);
extern void *func_080D4704(const void *data, void *context);
extern void *func_080D3E9C(const void *data, void *context);
extern u8 func_080D48DC(void **tasks, u16 count);
extern u16 func_080035A8(u8 layer);
extern void func_080D49FC(u32 a, u32 b, u32 c, s16 x, s16 y);
extern void *func_080D4B64(u32 a, const void *data, u32 size, u32 mode);
extern void *func_080D4724(const void *data, void *context, u16 delay);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second, u32 count,
                           void *parameters, const void *data, void *context);
extern void func_080DE3BC(void *object, u8 mode);
extern void *func_080D4D2C(void *layer, u32 value);
extern void *func_080D3F08(void *scene);
extern void *func_080DF8E8(void *value, u8 second, u32 first, void *parent);
extern void *func_080D6134(void *operation);
extern u8 func_080D8924(void *object, u32 index, u32 flags, void *context);
extern u8 func_080E0570(void **tasks, u16 count);
extern void *func_080DD4A4(void *object, u8 index);
extern void *func_080DBA5C(void *operation);
extern void func_080DD720(void *object, u32 mask);

u32 func_080F6520(void *context, Command080F6520 *command, State080F6520 *state)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        state->mode = command->flag;
        state->object = command->object;
        state->variant = 0;
        state->variant_flag = 0;
        if (command->kind == 0x10A) {
            state->variant = 1;
            if (command->options & 2)
                state->variant_flag = 1;
        }
        mode = 6;
        if (state->mode)
            mode = 0;
        state->opening = func_080E03F8(state->object, data_0839B800, mode,
                                       0, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->opening = func_080E05DC(state->opening);
        if (state->opening != 0)
            break;
        state->related = func_080DD47C(state->object);
        if (!state->variant) {
            func_080DE10C(state->related, 0x24);
            command->state = 0x102;
            break;
        }
        if (state->variant_flag) {
            func_080DE10C(state->related, 0x24);
            state->index = 60;
        } else {
            func_080DE10C(state->related, 0x54);
            state->initiator = func_080DE4B0(state->related, &state->ready,
                                             2, 2, 0, 0, 0, context);
        }
        state->script = func_080DFD8C(data_0839B8BC, 1, 4, 0, context);
        command->state++;
        break;
    case 0x101:
        if (state->index != 0) {
            state->index--;
            if (state->index != 0)
                break;
        }
        if (state->initiator != 0 && !state->ready)
            break;
        command->state++;
        break;
    case 0x102:
        func_080DBDC8(state->related, &state->x, &state->y);
        if (state->mode) {
            state->count = func_080DD494(state->object) - 1;
            state->timer = 1;
            command->state = 0x106;
            break;
        }
        func_080D7220(data_088F58EC, 0, 2, state->x, state->y, 0);
        state->texts[0] = func_080D4704(data_0894A07C, context);
        state->texts[1] = func_080D4704(data_0894A0B0, context);
        state->scene = func_080D3E9C(data_0894D69C, context);
        state->script = func_080DFD8C(data_0839B8C4, 1, 4, 0, context);
        command->state++;
        break;
    case 0x103:
        if (!func_080D48DC(state->texts, 2))
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->layer = func_080D4B64(0, data_088EF6CC, 0x2AC, 7);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->texts[0] = func_080D4704(data_0894A0E8, context);
        state->texts[1] = func_080D4724(data_0894AAB0, context, 26);
        state->movement = func_080D6098(state->x, state->y, 0, 1, 1,
            &state->parameters, data_0839B848, context);
        state->script = func_080DFD8C(data_0839B8CC, 1, 4, 0, context);
        if (state->variant == 1 && state->variant_flag == 0)
            state->index = 16;
        command->state++;
        break;
    case 0x104:
        if (state->index != 0) {
            state->index--;
            if (state->index == 0) {
                func_080DE3BC(state->related, 0);
                state->initiator = func_080DE4B0(state->related, &state->ready,
                                                 2, 3, 0, 0, 0, context);
            }
        }
        state->layer = func_080D4D2C(state->layer, 0);
        if (state->layer != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->scene = func_080D3F08(state->scene);
        if (state->scene != 0)
            break;
        if (!func_080D48DC(state->texts, 2))
            break;
        state->second_movement = func_080D6098(state->x, state->y, 0, 1, 3,
            state->second_parameters, data_0839B860, context);
        state->script = func_080DFD8C(data_0839B8D4, 1, 4, 0, context);
        state->follower = func_080DF8E8(state->related, 1, 30, context);
        command->state++;
        break;
    case 0x105:
        state->movement = func_080D6134(state->movement);
        if (state->movement != 0)
            break;
        state->second_movement = func_080D6134(state->second_movement);
        if (state->second_movement != 0)
            break;
        state->count = func_080D8924(state->object, 0, 0x38, context) - 1;
        if (state->count <= 0) {
            command->state = 0x107;
            break;
        }
        state->timer = 1;
        command->state++;
        break;
    case 0x106: {
        Descriptor080F6520 descriptor;

        func_080E0570(state->tasks, 4);
        state->timer--;
        if (state->timer != 0)
            break;
        descriptor.flags = state->index;
        descriptor.object = func_080DD4A4(state->object, state->index);
        state->tasks[state->index] = func_08005B6C(func_080F6490,
            0x14, &descriptor, context);
        state->timer = 30;
        state->index++;
        if (state->index == state->count)
            command->state++;
        break;
    }
    case 0x107:
        state->follower = func_080DBA5C(state->follower);
        if (state->follower != 0)
            break;
        if (func_080E0570(state->tasks, 4)) {
            func_080DD720(state->related, 0x10);
            command->state = 2;
        }
        break;
    }
    return 0;
}
