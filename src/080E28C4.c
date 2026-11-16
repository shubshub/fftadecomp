#include "ffta.h"

/* 0x080E28C4..0x080E29C4: 256 bytes, 122 instructions, including the
 * literal pool word at 0x080E2914. */

typedef struct {
    u16 state;
} Command080E28C4;

typedef struct {
    u8 unknown_00[2];
    u8 unknown_02;
    u8 unknown_03;
    s16 values[8];
    void *objects[8];
    void *child;
} State080E28C4;

extern const u8 data_08395C7C[];

extern void *func_080D7A70(const void *records, u8 count, void *parent);
extern void *func_080D7ABC(void *child);
extern void func_08011058(void *object, s16 value);
extern void *func_08011484(void *object);

u32 func_080E28C4(void *task, Command080E28C4 *command, State080E28C4 *state)
{
    u8 all_done;
    u8 completed;
    u8 index;

    switch (command->state) {
    case 0:
        state->unknown_02 = 6;
        break;
    case 1:
        break;
    case 0x100:
        state->child = func_080D7A70(data_08395C7C, 6, task);
        command->state++;
        break;
    case 0x101:
        state->child = func_080D7ABC(state->child);
        if (state->child == 0)
            command->state++;
        break;
    case 0x102:
        all_done = 1;
        completed = 0;
        for (index = 0; index < 8; index++) {
            if (state->objects[index] != 0) {
                func_08011058(state->objects[index], -state->values[index]);
                state->objects[index] = func_08011484(state->objects[index]);
                if (state->objects[index] != 0)
                    all_done = 0;
                else
                    completed++;
            }
        }
        for (index = 0; index < 8; index++) {
            state->values[index] -= completed;
            if (state->values[index] < 0)
                state->values[index] = 0;
        }
        if (all_done)
            command->state++;
        break;
    case 0x103:
        command->state = 2;
        break;
    }
    return 0;
}
