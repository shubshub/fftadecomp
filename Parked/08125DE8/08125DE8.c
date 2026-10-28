#include "ffta.h"

/* 0x08125DE8..0x08125FA8: 448 bytes, 183 reachable instructions. */
typedef struct {
    u16 flags;
    u8 unknown_02[0x48];
    u16 display : 8;
    u8 unknown_4B[5];
} ControlState;

typedef struct {
    u8 unknown_00[0x2174];
    u16 counter;
    u8 unknown_2176[0xE4A];
    u8 unknown_2FC0 : 3;
    u8 mode : 2;
    u8 unknown_2FC0_high : 3;
} WorldState;

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} EffectOwner;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    EffectOwner *owner;
    u8 unknown_08[12];
    u16 variant;
} EffectCommand;

typedef struct {
    EffectOwner *owner;
    u8 unknown_04[4];
    void *buffer;
    u8 timer;
    u8 unknown_0D;
    u8 variant;
    u8 saved_mode;
    u8 request[0x54];
    ControlState saved_control;
} EffectState;

typedef struct {
    u8 unknown_00[0x14];
    u32 destination;
} DisplayState;

extern ControlState g_control_flags_03000940;
extern WorldState g_state_02000000;
extern DisplayState data_030008B0;
extern u8 data_03000990[];
extern void *func_08121B64(u32);
extern void func_08121B78(void *);
extern void func_081443FC(void *, const void *, u32);
extern u8 func_080C9540(u16);
extern void func_080C9574(u16, u16);
extern void func_0801174C(void *, u32, u32, void *, void *, s32, s32,
                          u32, u32, u32);
extern u16 func_08011860(void);
extern void func_08000B20(void *, u16, u32, u16);

u32 func_08125DE8(void *task, EffectCommand *command, EffectState *state)
{
    switch (command->phase) {
    case 1:
        if (state->buffer) {
            func_08121B78(state->buffer);
            state->buffer = 0;
        }
        break;
    case 0:
    {
        ControlState *control;

        state->owner = command->owner;
        state->variant = command->variant;
        control = &g_control_flags_03000940;
        func_081443FC(&state->saved_control, control, 0x50);
        control->flags |= 0xC00;
        control->display &= ~0xC;
        if (func_080C9540(0x252)) {
            state->saved_mode = g_state_02000000.mode;
            g_state_02000000.mode = 0;
        }
        break;
    }
    case 0x100:
        state->buffer = func_08121B64(0x794);
        func_0801174C(state->buffer, 5, state->variant, &data_030008B0,
                      data_03000990, -1, -1, 0, 6, 0x240);
        command->phase = 0x101;
        break;
    case 0x101:
        if (!func_08011860())
            break;
        if (func_080C9540(0x252)) {
            WorldState *world = &g_state_02000000;

            world->mode = state->saved_mode;
            func_080C9574(0x252, 0);
            world->counter = 0;
        }
        func_08000B20(state->request, 0, data_030008B0.destination, 0x280);
        state->timer = 30;
        command->phase = 0x102;
        break;
    case 0x102:
        if (state->timer && --state->timer)
            break;
        func_08121B78(state->buffer);
        state->buffer = 0;
        command->phase = 0x103;
        break;
    case 0x103:
        g_control_flags_03000940.flags = state->saved_control.flags;
        g_control_flags_03000940.display = state->saved_control.display;
        state->owner->complete = 1;
        command->phase = 3;
        break;
    }
    return 0;
}
