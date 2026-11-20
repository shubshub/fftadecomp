#include "ffta.h"
#include "control_flags.h"

/* Target 0x0810CDDC, complete [0x0810CDDC, 0x0810D34C), 1392 bytes. */

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Command0810CDDC;

typedef struct {
    u16 timer;
    u8 count;
    u8 index;
    u8 rounds;
    u8 mode;
    u8 unknown_06[6];
    void *related;
    void *target;
    void *members[24];
    void *task;
    void *layer;
    void *panel;
    void *scene;
    void *text;
    void *opening;
    void *object;
    u8 unknown_90[4];
    void *script;
} State0810CDDC;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 index;
    u8 unknown_0C[8];
    u16 kind;
    u16 argument;
    u8 unknown_18[4];
} Descriptor0810CDDC;

extern const u8 data_083A26AC[];
extern const u8 data_088F2D18[];
extern const u8 data_0894D7E4[];
extern const u8 data_0894CCAC[];
extern const u8 data_085086D4[];
extern const u8 data_083A26D0[];
extern const u8 data_083A26D8[];
extern const u8 data_088EB938[];
extern const u8 data_083A26E0[];
extern const u8 data_0894848C[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);
extern u32 func_080EFAB0(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *object, const void *data, u8 mode, u8 kind,
                           u32 argument, void *context);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *operation);
extern void *func_080E051C(void *task);
extern void *func_080DD47C(void *object);
extern void *func_080DD4B4(void *object, u8 index);
extern u8 func_080DD494(void *object);
extern void func_080DD304(void *related);
extern void func_080D49FC(u8 first, u8 second, u16 third, s16 fourth,
                          s16 fifth);
extern void *func_080D4B64(u8 group, const void *descriptor, u16 value,
                           u8 mode);
extern void *func_080D4D2C(void *object, u8 mode);
extern u16 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080D3F08(void *scene);
extern void *func_080D4704(const void *data, void *context);
extern void *func_080D4774(void *text);
extern void *func_080D5CC0(const void *header, u16 index, s16 x, s16 y,
                           s16 height, u8 mode, u8 palette, u8 relative);
extern void *func_08011484(void *panel);
extern void func_08011428(void *panel);
extern void func_0801121C(void *panel, s16 value);
extern void *func_080DFD8C(const void *events, u8 count, u16 flags,
                           u16 delay, void *parent);
extern u8 func_080DD3C4(void **members);
extern void *func_080DD478(const void *object);
extern u8 func_080C8280(const void *object);
extern u8 func_080DC014(const void *state);
extern u8 func_080D8B4C(void);
extern void func_080DBDA0(const void *position, s16 *first_output,
                          s16 *second_output, s16 *third_output);
extern u16 func_0801BA20(s16 x, s16 y, u16 speed);
extern u8 func_0801BDB0(void);
extern void func_080D45D0(const void *rows, u8 index, u8 bank,
                          u8 first_row, u8 count);

u32 func_0810CDDC(void *context, Command0810CDDC *command, State0810CDDC *state)
{
    switch (command->state) {
    case 0: {
        u8 mode;

        state->mode = command->flag;
        state->object = command->object;
        mode = 3;
        if (state->mode)
            mode = 0;
        state->related = func_080DD47C(state->object);
        state->target = func_080DD4B4(state->object, 0);
        state->opening = func_080E03F8(state->object, data_083A26AC, mode,
                                       7, 0, context);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->opening = func_080E05DC(state->opening);
        if (state->opening != 0)
            break;
        if (!func_080DD494(state->object)) {
            func_080DD304(state->related);
            command->state = 2;
            break;
        }
        func_080D49FC(0, 2, 0, 0x78, 0x40);
        state->layer = func_080D4B64(0, data_088F2D18, 0x3DF, 7);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->scene = func_080D3E9C(data_0894D7E4, context);
        state->text = func_080D4704(data_0894CCAC, context);
        state->panel = func_080D5CC0(data_085086D4, 0, 0x78, 0x60, 0x3BF, 6,
                                     1, 0);
        state->script = func_080DFD8C(data_083A26D0, 1, 4, 0, context);
        command->state++;
        break;
    case 0x101: {
        u8 i;
        u8 j;
        u32 changed;

        state->scene = func_080D3F08(state->scene);
        if (state->scene != 0)
            break;
        state->text = func_080D4774(state->text);
        if (state->text != 0)
            break;
        state->layer = func_080D4D2C(state->layer, 0);
        if (state->layer != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->panel = func_08011484(state->panel);
        if (state->panel != 0)
            break;
        state->panel = func_080D5CC0(data_085086D4, 1, 0x78, 0x60, 0x3BF, 6,
                                     1, 0);
        func_0801121C(state->panel, -1);
        state->count = func_080DD3C4(state->members);
        for (i = 0; i < state->count; i++) {
            if (func_080C8280(func_080DD478(state->members[i]))
                && state->members[i] != state->target)
                state->members[i] = 0;
        }
        do {
            changed = 0;
            for (i = 0; i < state->count; i++) {
                if (state->members[i] == 0) {
                    for (j = i; j < state->count - 1; j++)
                        state->members[j] = state->members[j + 1];
                    state->count--;
                    changed = 1;
                    break;
                }
            }
        } while (changed);
        state->timer = 10;
        state->rounds = 1;
        command->state++;
        break;
    }
    case 0x102:
        state->timer--;
        if (state->timer != 0)
            break;
        func_080DC014(state->members[state->index]);
        command->state++;
        break;
    case 0x103:
        if (func_080D8B4C())
            break;
        state->script = func_080DFD8C(data_083A26D8, 1, 4, 0, context);
        state->timer = 20;
        state->index++;
        if (state->index == state->count) {
            state->rounds--;
            if (state->rounds == 0) {
                command->state++;
                break;
            }
            state->index = 0;
        }
        command->state = 0x102;
        break;
    case 0x104: {
        s16 x;
        s16 y;
        s16 z;

        state->timer--;
        if (state->timer != 0)
            break;
        func_080DBDA0(state->related, &x, &y, &z);
        func_0801BA20(x - 0x78, y - 0x60, 2);
        state->timer = 30;
        command->state++;
        break;
    }
    case 0x105:
        if (func_0801BDB0())
            break;
        if (state->timer != 0) {
            state->timer--;
            if (state->timer != 0)
                break;
        }
        command->state++;
        break;
    case 0x106: {
        s16 x;
        s16 y;
        s16 z;

        func_080DBDA0(state->target, &x, &y, &z);
        func_0801BA20(x - 0x78, y - 0x60, 0x10);
        state->timer = 20;
        command->state++;
        break;
    }
    case 0x107:
        if (func_0801BDB0())
            break;
        if (state->timer != 0) {
            state->timer--;
            if (state->timer != 0)
                break;
        }
        func_08011428(state->panel);
        func_080D45D0(data_088EB938, 7, 0, 0, 1);
        func_080D49FC(0, 2, 0, 0x78, 0x40);
        state->layer = func_080D4B64(0, data_088F2D18, 0x3DF, 7);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->scene = func_080D3E9C(data_0894D7E4, context);
        state->text = func_080D4704(data_0894CCAC, context);
        state->panel = func_080D5CC0(data_085086D4, 2, 0x78, 0x60, 0x3BF, 6,
                                     1, 0);
        state->script = func_080DFD8C(data_083A26E0, 1, 4, 0, context);
        command->state++;
        break;
    case 0x108: {
        Descriptor0810CDDC descriptor;

        state->scene = func_080D3F08(state->scene);
        if (state->scene != 0)
            break;
        state->text = func_080D4774(state->text);
        if (state->text != 0)
            break;
        state->layer = func_080D4D2C(state->layer, 0);
        if (state->layer != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->panel = func_08011484(state->panel);
        if (state->panel != 0)
            break;
        state->text = func_080D4704(data_0894848C, context);
        descriptor.kind = 0x128;
        descriptor.argument = 0;
        descriptor.object = state->object;
        descriptor.index = 0;
        state->task = func_08005B6C(func_080EFAB0, 0x2C, &descriptor, context);
        command->state++;
        break;
    }
    case 0x109:
        state->text = func_080D4774(state->text);
        if (state->text != 0)
            break;
        state->task = func_080E051C(state->task);
        if (state->task == 0)
            command->state = 2;
        break;
    }
    return 0;
}
