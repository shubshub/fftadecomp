#include "ffta.h"

/* 0x08125FA8..0x08126118: 368 bytes, 153 reachable instructions. */
typedef struct {
    u16 flags;
    u8 unknown_02[0x48];
    u16 display : 8;
    u8 unknown_4B[5];
} ControlState;

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} EffectOwner;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    EffectOwner *owner;
    u8 unknown_08[0xC];
    u16 kind;
    u16 variant;
} EffectCommand;

typedef struct {
    EffectOwner *owner;
    u8 unknown_04[4];
    void *buffer;
    u8 timer;
    u8 kind;
    u8 variant;
    u8 unknown_0F[0x55];
    ControlState saved_control;
} EffectState;

extern ControlState g_control_flags_03000940;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void *func_08121B64(u32);
extern void func_08121B78(void *);
extern void func_081443FC(void *, const void *, u32);
extern void func_0801174C(void *, u32, u32, void *, void *, u32, u32,
                          u32, u32, u32);
extern void func_0801339C(u16);
extern u16 func_08011860(void);

u32 func_08125FA8(void *task, EffectCommand *command, EffectState *state)
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
        state->kind = command->kind;
        state->variant = command->variant;
        state->timer = 0;
        control = &g_control_flags_03000940;
        func_081443FC(&state->saved_control, control, 0x50);
        control->flags |= 0xC00;
        control->display &= ~0x1C;
        break;
    }
    case 0x100:
    {
        void *buffer = func_08121B64(0xA04);

        state->buffer = buffer;
        switch (state->kind) {
        case 1:
            func_0801174C(buffer, 1, state->variant, data_030008B0,
                          data_03000990, 2, 2, 24, 4, 0x3A0);
            func_0801339C(2);
            break;
        case 2:
            func_0801174C(buffer, 2, state->variant, data_030008B0,
                          data_03000990, 2, 2, 24, 0, 0x3A0);
            func_0801339C(2);
            break;
        }
        command->phase = 0x101;
        break;
    }
    case 0x101:
        if (func_08011860())
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
