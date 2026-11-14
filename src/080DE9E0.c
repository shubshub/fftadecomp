#include "ffta.h"

// 0x080DE9E0..0x080DEBAA: 458 bytes, 229 instructions.
// Target: f0b5474680b486b0071c8846161c09888020400081424fd0814202dc00290dd0
//         cce081204000814200d1b0e0814200da9ee00130814200d1b3e0bfe01c4904a8
//         032265f0ebfc40464468206870606068b0602089b0810023202189198c460025
//         (full bytes in work/dis/080DE9E0.s)
typedef struct {
    const void *table;
    u16 index;
    u8 enabled;
    u16 unknown_08[3];
    u16 value;
    u8 mode;
    u16 unknown_12;
    u8 active;
    u16 selection;
} Slot080DE9E0;

typedef struct {
    u16 countdown;
    u16 delay;
    void *object;
    void *target;
    u16 command;
    u8 flag;
    s8 saved;
    void *outputs[3];
    void *effect;
    Slot080DE9E0 slots[3];
    void *sequence;
} State080DE9E0;

typedef struct {
    void *source;
    void *target;
    u16 command;
    u16 value;
    u8 mode;
} Params080DE9E0;

typedef struct {
    u16 state;
    u16 unknown_02;
    Params080DE9E0 *params;
    u8 unknown_08[0xC];
    u16 delay;
} Command080DE9E0;

extern const u8 data_08149B74[];
extern const u8 data_084FF71C[];
extern const u8 data_08395608[];
extern const u8 data_08395610[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern s8 func_080DBC88(void *object);
extern void func_080DE10C(void *object, u16 command);
extern u32 func_080DD71C(void *object);
extern void func_080DE278(void *object, s8 value);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode, u16 count,
                           void **outputs, const void *entries, void *parent);
extern void *func_080DFD8C(const void *events, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D6134(void *task);
extern void func_080DE390(void *object);

u32 func_080DE9E0(void *task, Command080DE9E0 *command, State080DE9E0 *state)
{
    u8 values[3];
    s16 x;
    s16 y;
    u8 i;
    u8 facing;
    Params080DE9E0 *params;

    switch (command->state) {
    case 0:
        func_081443FC(values, data_08149B74, sizeof(values));
        params = command->params;
        state->object = params->source;
        state->target = params->target;
        state->command = params->command;
        for (i = 0; i < 3; i++) {
            state->slots[i].table = data_084FF71C;
            state->slots[i].index = i;
            state->slots[i].enabled = 1;
            state->slots[i].unknown_08[0] = 0;
            state->slots[i].unknown_08[1] = 0;
            state->slots[i].unknown_08[2] = 0;
            state->slots[i].value = params->value;
            state->slots[i].mode = params->mode;
            state->slots[i].unknown_12 = 0;
            state->slots[i].active = 1;
            state->slots[i].selection = values[i];
        }
        state->countdown = command->delay + 1;
        break;
    case 1:
        break;
    case 0x100:
        if (--state->countdown == 0) {
            state->saved = func_080DBC88(state->target);
            func_080DE10C(state->object, state->command);
            facing = func_080DBC88(state->object);
            facing += 2;
            facing &= 3;
            if (func_080DD71C(state->target) & 0x40)
                state->flag = 1;
            if (state->flag == 0 && state->target != 0)
                func_080DE278(state->target, facing);
            func_080DBDC8(state->object, &x, &y);
            state->effect = func_080D6098(x, y, 0, 1, 3, state->outputs,
                                          state->slots, task);
            if (state->command == 0xA0)
                state->sequence = func_080DFD8C(data_08395608, 1, 4, 0, task);
            else
                state->sequence = func_080DFD8C(data_08395610, 1, 4, 0, task);
            command->state++;
        }
        break;
    case 0x101:
        state->effect = func_080D6134(state->effect);
        if (state->effect == 0) {
            func_080DE390(state->object);
            state->delay = 0x28;
            command->state++;
        }
        break;
    case 0x102:
        if (--state->delay == 0)
            command->state = 2;
        break;
    case 0x103:
        if (state->flag == 0 && state->target != 0)
            func_080DE278(state->target, state->saved);
        command->state = 2;
        break;
    }
    return 0;
}
