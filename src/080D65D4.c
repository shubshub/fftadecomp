#include "ffta.h"

/* 0x080D65D4..0x080D663C: 104 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    u32 parameter;
    u8 unknown_08[12];
    u16 value;
} CopyCommand;

typedef struct {
    u8 unknown_00[0x80];
    u16 value;
    u16 unknown_82;
    u32 parameter;
} CopyState;

extern u32 func_080CB980(CopyState *, u16);
extern const void *func_080D3AF8(u32);
extern void func_08000A98(const void *, void *, u32, u32);

u32 func_080D65D4(void *unused, CopyCommand *command, CopyState *state)
{
    switch (command->state) {
    case 0:
        state->value = command->value;
        state->parameter = command->parameter;
        break;
    case 1:
        break;
    case 0x100: {
        u32 index = func_080CB980(state, state->value);
        const void *data = func_080D3AF8(index);

        func_08000A98(data, state, state->parameter, 0x40);
        command->state++;
        break;
    }
    case 0x101:
        command->state = 3;
        break;
    }
    return 0;
}
