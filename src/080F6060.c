#include "ffta.h"
#include "effect_task.h"
#include "control_flags.h"

/* Target 0x080F6060, complete [0x080F6060, 0x080F648E), 1070 bytes, 435 reachable instructions. */

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Command080F6060;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 mode;
    u8 ready;
    u8 unknown_07;
    s8 count;
    u8 timer;
    u16 index;
    u32 parameters[3];
    void *movement;
    void *layer;
    void *scene;
    void *tasks[4];
    void *related;
    void *text;
    void *object;
    void *opening;
    void *initiator;
    void *action;
    void *script;
} State080F6060;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 flags;
    u8 unknown_16[6];
} Descriptor080F6060;

extern const u8 data_0839B664[];
extern const u8 data_088EF398[];
extern const u8 data_0894D90C[];
extern const u8 data_0839B6C4[];
extern const u8 data_0839B798[];
extern const u8 data_0839B794[];
extern const u8 data_0839B6DC[];
extern const u8 data_088EF44C[];
extern const u8 data_0894D91C[];
extern const u8 data_089484DC[];
extern const u8 data_0839B7A0[];
extern const u8 data_0839B754[];
extern const u8 data_0839B7A8[];
extern const u8 data_0839B780[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);
extern u32 func_080F5F7C(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *object, const void *data, u32 mode,
                           u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern void *func_080DD47C(void *object);
extern u8 func_080DD494(void *object);
extern void *func_080DDF68(void *object, void **related, u32 flags, u32 mode,
                           u8 *ready, const void *data, u32 count, u32 value,
                           void *context);
extern void func_080DBDC8(void *related, s16 *x, s16 *y);
extern void func_080DE10C(void *related, u32 mode);
extern void func_080D49FC(u32 a, u32 b, u32 c, s16 x, s16 y);
extern void *func_080D4B64(u32 a, const void *data, u32 size, u32 mode);
extern void *func_080D4D2C(void *layer, u32 value);
extern u16 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080D3F08(void *scene);
extern void func_080D3F84(void *scene, u32 first, u32 second);
extern void *func_080D4724(const void *data, void *context, u32 delay);
extern void *func_080D4774(void *text);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second, u32 count,
                           void *parameters, const void *data, void *context);
extern void *func_080D6134(void *operation);
extern void func_080D6194(void *operation, u8 enabled);
extern s8 func_080DBC88(void *object);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                           u32 third, void *context);
extern u8 func_080D8924(void *object, u32 index, u32 flags, void *context);
extern void *func_080DD4A4(void *object, u8 index);

extern void *func_080DBA5C(void *operation);
extern u8 func_080DE1F0(void *object);
extern u8 func_080E0570(void *tasks, u32 count);

u32 func_080F6060(void *context, Command080F6060 *command, State080F6060 *state)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        state->mode = command->flag;
        state->object = command->object;
        mode = 8;
        if (state->mode)
            mode = 0;
        state->opening = func_080E03F8(state->object, data_0839B664, mode,
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
        func_080DBDC8(state->related, &state->x, &state->y);
        if (state->mode) {
            state->count = func_080DD494(state->object) - 1;
            state->timer = 1;
            command->state = 0x105;
            break;
        }
        func_080DE10C(state->related, 0x24);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->layer = func_080D4B64(0, data_088EF398, 0x3BF, 6);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->scene = func_080D3E9C(data_0894D90C, context);
        state->movement = func_080D6098(state->x, state->y, 0, 1, 1,
            state->parameters, data_0839B6C4, context);
        state->script = func_080DFD8C(data_0839B798, 1, 4, 0, context);
        command->state++;
        break;
    case 0x101:
        state->layer = func_080D4D2C(state->layer, 0);
        if (state->layer != 0)
            break;
        state->scene = func_080D3F08(state->scene);
        if (state->scene != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->initiator = func_080DDF68(state->object, &state->related, 0x94,
            1, &state->ready, data_0839B794, 0, 0, context);
        command->state++;
        break;
    case 0x102:
        if (!state->ready)
            break;
        state->movement = func_080D6098(state->x, state->y, 0, 1, 3,
            state->parameters, data_0839B6DC, context);
        if (func_080DBC88(state->related) > 1)
            func_080D6194(state->movement, 1);
        state->index = 4;
        command->state++;
        break;
    case 0x103:
        state->index--;
        if (state->index != 0)
            break;
        func_080D49FC(1, 3, 0, state->x, state->y);
        state->layer = func_080D4B64(1, data_088EF44C, 0x35D, 7);
        g_control_flags_03000940.display |= func_080035A8(3);
        state->scene = func_080D3E9C(data_0894D91C, context);
        func_080D3F84(state->scene, 8, 0xFF);
        state->text = func_080D4724(data_089484DC, context, 30);
        state->script = func_080DFD8C(data_0839B7A0, 1, 4, 0, context);
        command->state++;
        break;
    case 0x104:
        state->movement = func_080D6134(state->movement);
        if (state->movement != 0)
            break;
        state->layer = func_080D4D2C(state->layer, 1);
        if (state->layer != 0)
            break;
        state->scene = func_080D3F08(state->scene);
        if (state->scene != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        state->text = func_080D4774(state->text);
        if (state->text != 0)
            break;
        if (!func_080DE1F0(state->related))
            break;
        state->count = func_080D8924(state->object, 0, 0x38, context) - 1;
        if (state->count <= 0) {
            command->state = 0x106;
            break;
        }
        state->timer = 1;
        command->state++;
        break;
    case 0x105: {
        Descriptor080F6060 descriptor;

        func_080E0570(state->tasks, 4);
        state->timer--;
        if (state->timer != 0)
            break;
        descriptor.flags = state->index;
        descriptor.object = func_080DD4A4(state->object, state->index);
        state->tasks[state->index] = func_08005B6C(func_080F5F7C,
            0x24, &descriptor, context);
        state->timer = 30;
        state->index++;
        if (state->index == state->count)
            command->state++;
        break;
    }
    case 0x106:
        if (func_080E0570(state->tasks, 4))
            command->state++;
        break;
    case 0x107:
        state->movement = func_080D6098(state->x, state->y, 0, 1, 1,
            state->parameters, data_0839B754, context);
        state->script = func_080DFD8C(data_0839B7A8, 1, 4, 0, context);
        state->action = func_080DCFE4(func_080DD4A4(state->object, state->count),
            data_0839B780, 12, 0x28, 0x10, context, 0x28);
        command->state++;
        break;
    case 0x108:
        state->movement = func_080D6134(state->movement);
        if (state->movement != 0)
            break;
        state->action = func_080DBA5C(state->action);
        if (state->action == 0)
            command->state = 2;
        break;
    }
    return 0;
}
