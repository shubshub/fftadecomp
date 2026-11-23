/* Target: complete [0x080F5BE4, 0x080F5F7C), 920 bytes, 399 instructions
 * plus the literal pools.
 *
 * An effect task: once its setup child is done it shows BG2 over the unit
 * (func_080D7220 with data_088F5A54) through a per-scanline blend.  The
 * blend rows below the fade line take the 56-row ramp data_0839B574 and
 * then EVA 10 / EVB 16; the line sweeps up from row 96 to 0 in 20 steps,
 * then back down while the rows above it are cleared (EVA 0 / EVB 16), and
 * BG2 is hidden again. */
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080F5BE4;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

/* One BLDALPHA row of the blend display's scanline payload, as 0800DB0C
 * writes it. */
typedef struct __attribute__((packed)) {
    u8 eva : 8;
    u8 evb : 8;
} BlendRow;

typedef struct {
    u16 countdown;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *unit;
    u8 unknown_0c[4];
    void *coordinate_child;
    void *setup_child;
    void *scanline_task;
    void *object;
    void *output_child;
    void *record_child;
    InterpolationState fade;
} State080F5BE4;

extern const u8 data_0839B508[];
extern const u8 data_088F5A54[];
extern const u8 data_0839B5E4[];
extern const u8 data_0839B574[][2];
extern const u8 data_0839B544[];
extern const u8 data_0839B55C[];

extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD47C(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080DE10C(void *, u16);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D9A24(u8, u8, u8, const void *, void *);
extern void func_0801E610(u8 *, u8 *);
extern u16 func_080035F8(u8);
extern u16 func_080035A8(u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D9B08(void *);
extern void func_080D9B98(void *);
extern void *func_080D9B64(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                           void *);
extern void *func_080D6134(void *);
extern void *func_080DBB14(void *, u8, u8, u16, void *);
extern void *func_080DBA5C(void *);

u32 func_080F5BE4(void *task, Descriptor080F5BE4 *descriptor,
                  State080F5BE4 *state)
{
    /* volatile: the ROM loads each byte of a row just before storing it and
     * never uses the value (ldrb at 0x080F5D98, 0x080F5DA2, 0x080F5DC0 and
     * 0x080F5DC6 in phase 0x102, 0x080F5E9C, 0x080F5EA0, 0x080F5EC6,
     * 0x080F5ED0, 0x080F5EE4 and 0x080F5EEA in phase 0x104, each followed
     * by the strb of the same byte); without the qualifier agbcc drops all
     * ten.  The rows are the scanline payload func_080D9B08 returns. */
    volatile BlendRow *lines;
    u8 line;
    u8 row;
    u8 mode;
    u8 first;
    u8 second;

    switch (descriptor->phase) {
    case 0:
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        mode = 5;
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object, data_0839B508,
                                           mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child)
            break;
        if (!func_080D8858(state->object, 0)) {
            descriptor->phase = 2;
            break;
        }
        state->unit = func_080DD47C(state->object);
        func_080DBDC8(state->unit, &state->x, &state->y);
        func_080DE10C(state->unit, 12);
        state->countdown = 20;
        descriptor->phase++;
        break;
    case 0x101:
        state->countdown--;
        if (state->countdown)
            break;
        func_080D7220(data_088F5A54, 0, 2, state->x, state->y, 0);
        state->scanline_task = func_080D9A24(0, 16, 0, 0, task);
        func_0801E610(&first, &second);
        g_control_flags_03000940.bldcnt_lo = func_080035F8(2) | 0x40;
        g_control_flags_03000940.bldcnt_hi =
            func_080035F8(first) | func_080035F8(second) | 0x30;
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 16;
        func_080E0608(&state->fade, 96, 0, 20);
        state->record_child = func_080DFD8C(data_0839B5E4, 1, 4, 0, task);
        descriptor->phase++;
        /* Falls through: 0x080F5D66 runs into phase 0x102 at 0x080F5D68. */
    case 0x102:
        func_080E064C(&state->fade);
        lines = func_080D9B08(state->scanline_task);
        row = 0;
        for (line = state->fade.current; line < 160; line++, row++) {
            if (row < 56) {
                lines[line].eva = data_0839B574[row][0];
                lines[line].evb = data_0839B574[row][1];
            } else {
                lines[line].eva = 10;
                lines[line].evb = 16;
            }
        }
        func_080D9B98(state->scanline_task);
        if (!func_080E0690(&state->fade))
            break;
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1, 1,
            state->unknown_0c, data_0839B544, task);
        descriptor->phase++;
        break;
    case 0x103:
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1, 1,
            state->unknown_0c, data_0839B55C, task);
        func_080E0608(&state->fade, 0, 96, 20);
        descriptor->phase++;
        break;
    case 0x104:
        line = state->fade.current;
        func_080E064C(&state->fade);
        lines = func_080D9B08(state->scanline_task);
        row = 0;
        for (; line < state->fade.current; line++) {
            lines[line].eva = 0;
            lines[line].evb = 16;
        }
        for (; line < 160; line++, row++) {
            if (row < 56) {
                lines[line].eva = data_0839B574[row][0];
                lines[line].evb = data_0839B574[row][1];
            } else {
                lines[line].eva = 10;
                lines[line].evb = 16;
            }
        }
        func_080D9B98(state->scanline_task);
        if (!func_080E0690(&state->fade))
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->output_child = func_080DBB14(state->unit, 2, 12, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        state->scanline_task = func_080D9B64(state->scanline_task);
        if (state->scanline_task)
            break;
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        state->output_child = func_080DBA5C(state->output_child);
        if (state->output_child)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
