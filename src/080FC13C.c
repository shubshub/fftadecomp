#include "ffta.h"
#include "control_flags.h"

// Target 0x080FC13C, complete [0x080FC13C, 0x080FC442), 774 bytes, 387 instructions.

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Command080FC13C;

typedef struct {
    s16 x;
    s16 y;
    u8 mode;
    u8 ready;
    u8 unknown_06;
    s8 count;
    u8 timer;
    u8 unknown_09;
    u16 index;
    u32 parameters[3];
    void *movement;
    u32 second_parameters[2];
    void *second_movement;
    void *layer;
    void *scene;
    void *first_text;
    void *second_text;
    u32 unknown_38;
    void *tasks[4];
    void *related;
    void *object;
    void *opening;
    void *initiator;
    void *script;
} State080FC13C;

typedef struct {
    u32 unknown_00;
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u8 unknown_16[6];
} Descriptor080FC13C;

extern const u8 data_0839D1C8[];
extern const u8 data_0839D2CC[];
extern const u8 data_088EDB7C[];
extern const u8 data_0894D7BC[];
extern const u8 data_08949554[];
extern const u8 data_08949564[];
extern const u8 data_0839D210[];
extern const u8 data_0839D2D0[];
extern const u8 data_0839D258[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);
extern u32 func_080FC058(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *object, const void *data, u32 mode,
                           u32 first, u32 second, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern u8 func_080DD494(void *object);
extern void *func_080DDF68(void *object, void **related, u32 flags, u32 mode,
                           u8 *ready, const void *data, u32 count, u32 value,
                           void *context);
extern void func_080DBDC8(void *related, s16 *x, s16 *y);
extern void func_080D49FC(u32 a, u32 b, u32 c, s16 x, s16 y);
extern void *func_080D4B64(u32 a, const void *data, u32 size, u32 mode);
extern void func_0800BDA4(void *layer, u32 value);
extern void func_0800BE10(void *layer, u32 value);
extern u16 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080D3F08(void *scene);
extern void *func_080D4704(const void *data, void *context);
extern void func_080D47A0(void *text, u32 value);
extern void func_080D4938(void *text, u32 value);
extern void func_080D4D14(void *layer, u32 value);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second, u32 count,
                           void *parameters, const void *data, void *context);
extern void *func_080D6134(void *operation);
extern void func_080D6194(void *operation, u8 enabled);
extern s8 func_080DBC88(void *object);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                           u32 third, void *context);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern u8 func_080DE1F0(void *object);
extern u8 func_080E0570(void *tasks, u32 count);

u32 func_080FC13C(void *context, Command080FC13C *command, State080FC13C *state)
{
    switch (command->state) {
    case 0: {
        u32 mode;

        state->mode = command->flag;
        state->object = command->object;
        mode = 6;
        if (state->mode)
            mode = 0;
        state->opening = func_080E03F8(state->object, data_0839D1C8, mode,
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
        if (state->mode) {
            state->count = func_080DD494(state->object);
            state->timer = 1;
            command->state = 0x104;
            break;
        }
        state->initiator = func_080DDF68(state->object, &state->related, 0x94,
            1, &state->ready, data_0839D2CC, 0, 0, context);
        func_080DBDC8(state->related, &state->x, &state->y);
        command->state++;
        break;
    case 0x101:
        if (!state->ready)
            break;
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->layer = func_080D4B64(0, data_088EDB7C, 0x3C6, 6);
        func_0800BDA4(state->layer, 1);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->scene = func_080D3E9C(data_0894D7BC, context);
        state->first_text = func_080D4704(data_08949554, context);
        state->second_text = func_080D4704(data_08949564, context);
        func_080D47A0(state->first_text, 1);
        func_080D47A0(state->second_text, 1);
        state->movement = func_080D6098(state->x, state->y, 0, 1, 3,
            state->parameters, data_0839D210, context);
        if (func_080DBC88(state->related) > 1) {
            func_0800BE10(state->layer, 1);
            func_080D6194(state->movement, 1);
        }
        state->script = func_080DFD8C(data_0839D2D0, 2, 4, 0, context);
        state->index = 30;
        command->state++;
        break;
    case 0x102:
        state->index--;
        if (state->index != 0)
            break;
        state->second_movement = func_080D6098(state->x, state->y, 0, 1, 2,
            state->second_parameters, data_0839D258, context);
        command->state++;
        break;
    case 0x103: {
        u8 had_scene = state->scene != 0;

        state->scene = func_080D3F08(state->scene);
        if (state->scene == 0) {
            if (had_scene) {
                func_080D4938(&state->first_text, 2);
                func_080D4D14(state->layer, 0);
                state->layer = 0;
                g_control_flags_03000940.display &= ~func_080035A8(2);
            }
            state->movement = func_080D6134(state->movement);
            if (state->movement == 0) {
                state->second_movement = func_080D6134(state->second_movement);
                if (state->second_movement == 0) {
                    state->count = func_080D8858(state->object, 0);
                    if (state->count <= 0) {
                        command->state = 0x105;
                    } else {
                        state->timer = 1;
                        command->state++;
                    }
                }
            }
        }
        break;
    }
    case 0x104: {
        Descriptor080FC13C descriptor;

        func_080E0570(state->tasks, 4);
        state->timer--;
        if (state->timer != 0)
            break;
        descriptor.selector = state->index;
        descriptor.object = func_080DD4A4(state->object, (u8)state->index);
        state->tasks[state->index] = func_08005B6C((TaskCallback)func_080FC058,
            0x24, &descriptor, context);
        state->timer = 30;
        state->index++;
        if (state->index == state->count)
            command->state++;
        break;
    }
    case 0x105:
        if (func_080DE1F0(state->related) && func_080E0570(state->tasks, 4))
            command->state = 2;
        break;
    }
    return 0;
}
