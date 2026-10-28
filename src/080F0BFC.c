#include "ffta.h"

/* 0x080F0BFC..0x080F0D58: 348 bytes. */
typedef struct SpriteObject SpriteObject;

typedef struct {
    s16 value;
    u8 unknown_02[10];
} SpriteTransition;

typedef struct {
    u16 state;
    u16 unknown_02;
    SpriteObject **main_output;
    u8 unknown_08[12];
    u16 selector;
} SpriteSequenceCommand;

typedef struct {
    u8 selector;
    u8 unknown_01[3];
    SpriteObject **main_output;
    SpriteObject *sprites[4];
    SpriteTransition first;
    SpriteTransition second;
    u32 effect;
} SpriteSequenceState;

extern const void *const data_0839A3C0[];
extern const u8 data_0839A4D4[];
extern SpriteObject *func_080D5CC0(const void *resource, u32 first,
    s16 x, s16 y, u16 tile, u8 palette, u32 flags, u32 last);
extern void func_080111A8(SpriteObject *sprite, u8 enabled);
extern void func_0801121C(SpriteObject *sprite, s16 value);
extern void func_0801115C(SpriteObject *sprite, u8 enabled);
extern void func_080E0608(SpriteTransition *transition, s16 from,
                         s16 to, u16 duration);
extern u8 func_080F0AC0(SpriteSequenceState *state);
extern u32 func_080DFD8C(const void *resource, u8 parameter, u32 type,
                         u32 flags, void *context);
extern void func_080D5F74(SpriteObject **sprites, u16 count);

u32 func_080F0BFC(void *context, SpriteSequenceCommand *command,
                  SpriteSequenceState *state)
{
    switch (command->state) {
    case 0:
        state->selector = command->selector;
        state->main_output = command->main_output;
        break;
    case 0x100: {
        u8 i;

        for (i = 0; i < 4; i++) {
            state->sprites[i] = func_080D5CC0(data_0839A3C0[state->selector],
                0, 0, 0, 640, 6, 0, 0);
            func_080111A8(state->sprites[i], 1);
            func_0801121C(state->sprites[i], -1);
        }
        *state->main_output = func_080D5CC0(data_0839A3C0[state->selector],
            0, 120, 56, 640, 6, 0, 0);
        func_0801121C(*state->main_output, -1);
        func_0801115C(*state->main_output, 0);
        func_080E0608(&state->first, 60, 0, 40);
        func_080E0608(&state->second, 224, 384, 40);
        func_080F0AC0(state);
        state->effect = func_080DFD8C(data_0839A4D4, 1, 4, 0, context);
        command->state++;
        break;
    }
    case 0x101:
        if (func_080F0AC0(state))
            command->state++;
        break;
    case 0x102:
        func_0801115C(*state->main_output, 1);
        func_080D5F74(state->sprites, 4);
        command->state = 2;
        break;
    }
    return 0;
}
