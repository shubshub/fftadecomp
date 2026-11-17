#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    s16 x;
    s16 y;
} Command080EF484;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 x;
    s16 y;
    u16 counter;
    u8 unknown_06[2];
    InterpolationState motion;
    void *effect;
    void *animation;
    void *scanline_task;
    void *controller;
} State080EF484;

extern const u8 data_088ED8CC[];
extern const u8 data_0894D804[];
extern const u8 data_08399B2C[];

extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u16 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080D3F08(void *);
extern void *func_080D9914(u8, u8, void *);
extern s16 func_080D499C(u8, u8);
extern u16 *func_080D996C(void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D9B64(void *);
extern void *func_080D4D2C(void *, u8);

/* Target: complete [0x080EF484, 0x080EF638), 436 bytes, 188 instructions. */
u32 func_080EF484(void *task, Command080EF484 *command, State080EF484 *state)
{
    switch (command->phase) {
    case 0:
        state->x = command->x;
        state->y = command->y;
        func_080D49FC(1, 3, 0, state->x, state->y);
        state->effect = func_080D4B64(1, data_088ED8CC, 0x3A2, 6);
        g_control_flags_03000940.display |= func_080035A8(3);
        state->animation = func_080D3E9C(data_0894D804, task);
        func_080E0608(&state->motion, state->y, state->y - 0x18, 0x3C);
        state->controller = func_080DFD8C(data_08399B2C, 1, 4, 0, task);
        break;
    case 1:
        /* Phase 1 has no work of its own.  The dispatch is rooted at 0x100
           (0x080EF490), the third of the six phase values; the five phases
           with code would root it at 0x101. */
        break;
    case 0x100:
        func_080E064C(&state->motion);
        func_0800BC08(1, state->x, state->motion.current);
        if (!func_080E0690(&state->motion))
            break;
        state->animation = func_080D3F08(state->animation);
        if (state->animation)
            break;
        state->counter = 0x56;
        command->phase++;
        break;
    case 0x101: {
        void *scanline_task;
        u16 value;
        u16 *buffer;
        u16 i;

        if (--state->counter)
            break;
        scanline_task = func_080D9914(3, 1, task);
        value = func_080D499C(3, 1);
        buffer = func_080D996C(scanline_task);
        for (i = 0; i < 160; i++)
            buffer[i] = value;
        func_080D9BA8(scanline_task, 1);
        state->scanline_task = scanline_task;
        state->counter = 0;
        command->phase++;
        break;
    }
    case 0x102: {
        u16 *buffer = func_080D996C(state->scanline_task);
        u16 i;

        for (i = 0; i < state->counter; i++)
            buffer[i] += 2;
        state->counter += 2;
        if (state->counter <= 0x48)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        command->phase++;
        break;
    }
    case 0x103:
        state->scanline_task = func_080D9B64(state->scanline_task);
        if (state->scanline_task)
            break;
        state->effect = func_080D4D2C(state->effect, 1);
        if (state->effect)
            break;
        command->phase = 2;
        break;
    }
    return 0;
}
