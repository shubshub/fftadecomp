#include "ffta.h"

/* 0x080EF484..0x080EF638: 436 bytes, 188 instructions. */
typedef struct {
    u16 state;
    u8 unknown_02[18];
    s16 x;
    s16 y;
} EffectCommand;

typedef struct {
    s16 value;
    u8 unknown_02[10];
} Motion;

typedef struct {
    s16 x;
    s16 y;
    u16 counter;
    u8 unknown_06[2];
    Motion motion;
    void *effect;
    void *animation;
    void *scanline;
    void *controller;
} EffectState;

extern const u8 data_088ED8CC[];
extern const u8 data_0894D804[];
extern const u8 data_08399B2C[];
extern u16 g_control_flags_03000940;

extern void func_080D49FC(u32 index, u32 mode, u32 value, s16 x, s16 y);
extern void *func_080D4B64(u32 index, const void *asset, u32 id, u32 priority);
extern u32 func_080035A8(u32 index);
extern void *func_080D3E9C(const void *descriptor, void *parent);
extern void func_080E0608(Motion *motion, s16 start, s16 end, u32 duration);
extern void *func_080DFD8C(const void *descriptor, u32 mode, u32 priority,
                         u32 flags, void *parent);
extern void func_080E064C(Motion *motion);
extern u8 func_080E0690(Motion *motion);
extern void *func_080D3F08(void *animation);
extern void *func_080D9914(u32 index, u32 mode, void *parent);
extern u16 func_080D499C(u32 index, u32 mode);
extern u16 *func_080D996C(void *scanline);
extern void func_080D9BA8(void *scanline, u32 mode);
extern void *func_080D9B64(void *scanline);
extern void *func_080D4D2C(void *effect, u32 mode);

u32 func_080EF484(void *task, EffectCommand *command, EffectState *state)
{
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->state) {
    case 0:
        state->x = command->x;
        state->y = command->y;
        func_080D49FC(1, 3, 0, state->x, state->y);
        state->effect = func_080D4B64(1, data_088ED8CC, 0x3A2, 6);
        mask = func_080035A8(3);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        state->animation = func_080D3E9C(data_0894D804, task);
        func_080E0608(&state->motion, state->y, (s16)(state->y - 0x18), 0x3C);
        state->controller = func_080DFD8C(data_08399B2C, 1, 4, 0, task);
        break;
    case 0x100:
    {
        Motion *motion = &state->motion;
        func_080E064C(motion);
        func_0800BC08(1, state->x, state->motion.value);
        if (!func_080E0690(motion)) {
            break;
        }
        state->animation = func_080D3F08(state->animation);
        if (state->animation) {
            break;
        }
        state->counter = 0x56;
        command->state++;
        break;
    }
    case 0x101:
    {
        void *scanline;
        u16 value;
        u16 *buffer;
        u16 i;

        if (--state->counter) {
            break;
        }
        scanline = func_080D9914(3, 1, task);
        value = func_080D499C(3, 1);
        buffer = func_080D996C(scanline);
        for (i = 0; i < 160; i++) {
            buffer[i] = value;
        }
        func_080D9BA8(scanline, 1);
        state->scanline = scanline;
        state->counter = 0;
        command->state++;
        break;
    }
    case 0x102:
    {
        u16 *buffer = func_080D996C(state->scanline);
        u16 i;
        for (i = 0; i < state->counter; i++) {
            buffer[i] += 2;
        }
        state->counter += 2;
        if (state->counter <= 0x48) {
            break;
        }
        mask = func_080035A8(3);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        command->state++;
        break;
    }
    case 0x103:
        state->scanline = func_080D9B64(state->scanline);
        if (state->scanline) {
            break;
        }
        state->effect = func_080D4D2C(state->effect, 1);
        if (state->effect) {
            break;
        }
        command->state = 2;
        break;
    }
    return 0;
}
