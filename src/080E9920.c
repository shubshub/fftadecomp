// Target 0x080E9920, complete [0x080E9920, 0x080E9BDC), 700 bytes.

#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u32 unknown_08;
    u8 unknown_0c[8];
    s16 selector;
    u16 flag;
    u8 unknown_18[4];
} Command080E9920;

typedef struct {
    u8 kind;
    u8 count;
    u8 index;
    u8 timer;
    u8 mode;
    u8 hidden;
    u8 unknown_06[2];
    void *tasks[2];
    void *effect_a;
    void *effect_b;
    void *effect_c;
    void *effect_d;
    void *effect_e;
    void *load;
    void *object;
    void *record;
    void *wrapper;
    u16 wrapper_count;
    u8 unknown_36[2];
} State080E9920;

typedef struct {
    u32 unknown_00;
    void *object;
    u8 unknown_08[12];
    u16 index;
    u16 mode;
    u8 unknown_18[4];
} Descriptor080E9920;

extern const void *const data_083986C0[];
extern const u8 data_083986C8[];
extern const u8 data_08398710[];
extern const u8 data_088F4F6C[];
extern const u8 data_08949224[];
extern const u8 data_0894923C[];
extern const u8 data_08949268[];
extern const u8 data_0894AC90[];
extern const u8 data_0894D754[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080E97F4(void *task, void *command, void *state);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                    void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8924(void *, u8, u16, void *);
extern void func_080D7220(const void *, int, int, int, int, int);
extern u16 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, int);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern u8 func_080E0570(void **, int);
extern void *func_080DD4A4(void *, int);
extern u8 func_080DD580(void *);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void **, int);
extern void *func_080D4774(void *);

u32 func_080E9920(void *task, Command080E9920 *command, State080E9920 *state)
{
    switch (command->phase) {
    case 0: {
        const u8 *table;
        u8 t;

        state->kind = 0;
        if (command->selector == 0x199) {
            state->kind = 1;
            state->mode = 1;
            state->wrapper = command->object;
            state->wrapper_count = command->unknown_08;
        } else {
            if (command->selector == 0x139)
                state->kind = 1;
            state->hidden = command->flag;
            state->object = command->object;
        }
        t = data_083986C8[state->kind];
        if (state->hidden)
            t = 0;
        if (state->mode == 0)
            state->load = func_080E03F8(state->object,
                data_083986C0[state->kind], t, 1, 0, task);
        else
            state->load = func_080E03F8(state->object,
                data_083986C0[state->kind], t, 7, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->load = func_080E05DC(state->load);
        if (state->load)
            break;
        if (state->hidden) {
            state->timer = 1;
            state->count = func_080D8924(state->object, 0, 0xAA, task);
            if (state->count == 0)
                command->phase = 0x103;
            else
                command->phase = 0x102;
        } else {
            command->phase++;
        }
        break;
    case 0x101:
        func_080D7220(data_088F4F6C, 0, 2, 0x78, 0x60, 0);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->effect_a = func_080D4704(data_08949224, task);
        state->effect_b = func_080D4704(data_0894923C, task);
        state->effect_c = func_080D4704(data_08949268, task);
        state->effect_d = func_080D4724(data_0894AC90, task, 0x87);
        state->effect_e = func_080D3E9C(data_0894D754, task);
        state->timer = 0x96;
        if (state->mode)
            state->count = state->wrapper_count;
        else
            state->count = func_080D8924(state->object, 0, 0xAA, task);
        state->record = func_080DFD8C(data_08398710, 1, 4, 0, task);
        if (state->count == 0)
            command->phase = 0x103;
        else
            command->phase++;
        break;
    case 0x102:
        func_080E0570(state->tasks, 2);
        state->timer--;
        if (state->timer == 0) {
            Descriptor080E9920 descriptor;
            u8 slot = state->tasks[0] != 0;

            descriptor.index = state->index;
            descriptor.mode = state->mode;
            if (state->mode)
                descriptor.object = ((void **)state->wrapper)[state->index];
            else
                descriptor.object = func_080DD4A4(state->object, state->index);
            state->tasks[slot] = func_08005B6C(
                (TaskCallback)func_080E97F4, 0x24, &descriptor, task);
            state->timer = 0x32;
            if (state->mode == 0 && func_080DD580(descriptor.object) == 0)
                state->timer -= 10;
            state->index++;
            if (state->index == state->count)
                command->phase++;
        }
        break;
    case 0x103:
        state->effect_e = func_080D3F08(state->effect_e);
        if (state->effect_e)
            break;
        if (func_080D48DC(&state->effect_a, 3)) {
            state->effect_d = func_080D4774(state->effect_d);
            if (state->effect_d)
                break;
            g_control_flags_03000940.display &= ~func_080035A8(2);
            if (func_080E0570(state->tasks, 2)) {
                g_control_flags_03000940.display &= ~func_080035A8(2);
                command->phase = 2;
            }
        }
        break;
    }
    return 0;
}
