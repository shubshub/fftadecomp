#include "ffta.h"
#include "effect_task.h"
#include "control_flags.h"

/* Target: complete [0x08119068, 0x081195F8), 1424 bytes including the
 * literal pools.  Local offset views; the original declarations are unknown.
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xE];
    u16 flag;
} Descriptor08119068;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u8 flag;
    u8 unknown_01;
    u16 counter;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_09[3];
    void *object;
    void *output;
    void *source;
    void *target;
    void *setup_child;
    void *script;
    void *tasks[2];
    void *resource_child;
    void *effect_child;
    void *transfer_child;
    void *output_child;
    InterpolationState fade;
    InterpolationState window;
    void *window_task;
    void *scanline_task;
    void *record_child;
} State08119068;

extern const u8 data_083A6274[];
extern const u8 data_083A62A4[];
extern const u8 data_083A62B8[];
extern const u8 data_083A62BC[];
extern const u8 data_083A62C0[];
extern const u8 data_083A62C8[];
extern const u8 data_083A62D0[];
extern const u8 data_083A62D8[];
extern const u8 data_083A62E0[];
extern const u8 data_088F46CC[];
extern const u8 data_088F58E0[];
extern const u8 data_0894AB00[];
extern const u8 data_0894BED8[];
extern const u8 data_0894BF00[];
extern const u8 data_0894D69C[];
extern const u8 data_0894DA50[];
extern const u8 data_0894DD18[];
extern u16 data_03003860[];
extern u8 data_06005000[];
extern u8 data_06005800[];
extern u8 data_0600F940[];

/* memcpy is the libc routine at 0x081443FC.  This source never calls it by
 * name: the compiler calls it at 0x08119476 to copy the initialiser of
 * `widths` (phase 0x107).  The parameter list is the one the compiler has
 * built in, and the compiled bytes are the same without the declaration;
 * the kit's volatile check takes a callee's argument count from its
 * prototype (fftadecomp-kit#410). */
extern void *memcpy(void *, const void *, unsigned long);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16,
                           u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(u8);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u8, u8 *, const void *, u16, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080DE10C(void *, u16);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, void *, u16);
extern s8 func_080DE4A0(void *);
extern void *func_080DC268(void *, const void *, const void *, u8, void *);
extern void func_080D72C8(const void *, u8, u8, s16, s16, u16, u8);
extern u16 func_080035D0(u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern void func_080DAC40(void *, s16, s16, u16);
extern void *func_080DBA5C(void *);
extern void *func_080D4774(void *);
extern void *func_080D9914(u8, u8, void *);
extern u16 *func_080D996C(void *);
extern u8 func_080DF8B0(void *);
extern void func_080D9B98(void *);
extern void *func_080D9B64(void *);
extern void func_080DBEB4(void *, u8);
extern void func_080DE268(void *);
extern u8 func_080DE1F0(void *);

u32 func_08119068(void *task, Descriptor08119068 *descriptor,
                  State08119068 *state)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        mode = 4;
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object, data_083A6274,
                                           mode, 7, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child)
            break;
        if (func_080D3B54(state->object)) {
            descriptor->phase = 2;
            break;
        }
        state->output_child = func_080DDF68(state->object, &state->output,
            0x54, 1, &state->ready, data_083A62B8, 2, 0, task);
        func_080DBDC8(state->output, &state->x, &state->y);
        descriptor->phase++;
        break;
    case 0x101:
        if (!state->ready)
            break;
        func_080DBC88(state->output);
        func_080D7220(data_088F58E0, 0, 2, state->x, state->y, 0);
        state->script = func_080D3E9C(data_0894D69C, task);
        state->tasks[0] = func_080D4704(data_0894BED8, task);
        state->tasks[1] = func_080D4704(data_0894BF00, task);
        state->record_child = func_080DFD8C(data_083A62C0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (!func_080D48DC(state->tasks, 2))
            break;
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080DE3BC(state->output, 0);
        func_080DBA50(state->output_child);
        state->output_child = func_080DE4F4(state->output, 1, &state->ready,
                                            data_083A62BC, 0, 0, task);
        state->target = func_080DD4A4(state->object, 0);
        state->source = func_080DD748(state->target, &state->x, &state->y, 0);
        state->record_child = func_080DFD8C(data_083A62C8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (!state->ready)
            break;
        state->resource_child = func_080D4704(data_0894AB00, task);
        state->counter = 8;
        descriptor->phase++;
        break;
    case 0x104:
        if (--state->counter)
            break;
        func_080DE10C(state->source, 8);
        func_08000B20(func_080D3AF8(), 0x63FA, data_06005800, 0x400);
        descriptor->phase++;
        break;
    case 0x105:
        if (func_080DE4A0(state->source) != 2)
            break;
        func_080DE3BC(state->source, 1);
        state->transfer_child = func_080DC268(state->source, data_0600F940,
                                              data_06005000, 0, task);
        func_080D72C8(data_088F46CC, 0, 2, 0, 0, 0, 1);
        data_03003860[0x61] = 0x65C9;
        g_control_flags_03000940.winin_lo = 0x3F;
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xFF;
        g_control_flags_03000940.display |= 0x2000;
        func_080E0608(&state->window, 0, 20, 25);
        state->window_task = func_080DAB84(0, 0, 0, task);
        func_080D9BA8(state->window_task, 1);
        state->record_child = func_080DFD8C(data_083A62D0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x106: {
        u16 *buffer;
        u16 value;
        s16 line;
        u8 i;

        func_080E064C(&state->window);
        func_080DAC40(state->window_task, state->x, state->y - 12,
                      state->window.current);
        state->transfer_child = func_080DBA5C(state->transfer_child);
        if (state->transfer_child)
            break;
        if (!func_080E0690(&state->window))
            break;
        state->resource_child = func_080D4774(state->resource_child);
        if (state->resource_child)
            break;
        state->scanline_task = func_080D9914(3, 0, task);
        buffer = func_080D996C(state->scanline_task);
        value = 16 - state->x;
        line = state->y - 48;
        for (i = 0; i <= 56; i++)
            buffer[line + i] = value;
        state->script = func_080D3E9C(data_0894DA50, task);
        func_080E0608(&state->fade, 0, 16, 30);
        state->record_child = func_080DFD8C(data_083A62D8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x107: {
        /* The initialiser is the two bytes 28 2C at 0x08149F74, copied to
         * sp+0x14 by func_081443FC at 0x08119476. */
        u8 widths[2] = { 40, 44 };
        u16 *buffer;
        s16 line;
        u8 wide;
        u8 i;

        wide = func_080DF8B0(state->source) != 0;
        func_080E064C(&state->fade);
        buffer = func_080D996C(state->scanline_task);
        line = state->y - 48;
        for (i = 0; i <= 56; i++) {
            /* The ROM keeps the flag: movs r1,#0 at 0x081194A8, movs r1,#1
             * at 0x081194B6, and cmp r1,#0 / beq at 0x081194B8. */
            u8 outside = 0;

            if (i >= widths[wide])
                outside = 1;
            if (outside)
                buffer[line + i] -= data_083A62E0[state->counter];
            else
                buffer[line + i] += data_083A62E0[state->counter];
        }
        state->counter++;
        func_080D9B98(state->scanline_task);
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        state->scanline_task = func_080D9B64(state->scanline_task);
        if (state->scanline_task)
            break;
        func_080DE3BC(state->output, 0);
        state->script = func_080D3E9C(data_0894DD18, task);
        descriptor->phase++;
        break;
    }
    case 0x108:
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        g_control_flags_03000940.display &= 0xDFFF;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->window_task = func_080D9B64(state->window_task);
        if (state->window_task)
            break;
        descriptor->phase++;
        break;
    case 0x109:
        func_080DBEB4(state->source, 1);
        func_080DE268(state->source);
        state->effect_child = func_080DCFE4(state->target, data_083A62A4,
                                            12, 0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x10A:
        if (!func_080DE1F0(state->output))
            break;
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
