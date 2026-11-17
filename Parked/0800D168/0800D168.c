#include "ffta.h"

// Complete [0x0800D168, 0x0800D23C), 212 bytes.
// Creates the affine background task for BG2 or BG3.

typedef struct {
    u16 kind;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u16 unknown_0A;
    s32 origin_x;
    s32 origin_y;
    s16 right;
    s16 bottom;
    s16 scale_x;
    s16 scale_y;
    u32 unknown_1C;
    s32 target_origin_x;
    s32 target_origin_y;
    s16 target_right;
    s16 target_bottom;
    s16 target_scale_x;
    s16 target_scale_y;
    u32 unknown_30;
    u16 center_x;
    u16 center_y;
} AffineState;

typedef struct {
    u16 *bg[2];
} AffineRegisters;

extern const AffineRegisters data_08149820;

typedef struct AffineTask AffineTask;

extern void func_0800D3BC(AffineState *state, u16 *destination);
extern AffineTask *func_0800C3CC(
    void (*callback)(AffineState *, u16 *), u32 size, u32 type,
    u16 *destination);
extern AffineState *func_0800C614(AffineTask *task);
extern void func_0800CBFC(AffineState *state);

AffineTask *func_0800D168(u8 bg, u16 x, u16 y, u16 center_x, u16 center_y,
                          u16 width, u16 height)
{
    AffineRegisters registers = data_08149820;
    AffineTask *task = func_0800C3CC(func_0800D3BC, 0x2B8, 0x10,
                                     registers.bg[bg - 2]);
    AffineState *state = func_0800C614(task);
    s32 left;
    s32 top;
    s32 span_x;
    s32 span_y;

    state->kind = 3;
    state->x = x;
    state->y = y;
    state->width = width;
    state->height = height;
    left = (s16)x;
    state->origin_x = left << 8;
    top = (s16)y;
    state->origin_y = top << 8;
    span_x = (s16)width;
    state->right = left + span_x;
    span_y = (s16)height;
    state->bottom = top + span_y;
    state->scale_x = 0x100;
    state->scale_y = 0x100;
    state->target_origin_x = left << 8;
    state->target_origin_y = top << 8;
    state->target_right = left + span_x;
    state->target_bottom = top + span_y;
    state->target_scale_x = 0x100;
    state->target_scale_y = 0x100;
    state->center_x = center_x;
    state->center_y = center_y;
    func_0800CBFC(state);
    return task;
}
