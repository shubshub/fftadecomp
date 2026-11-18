#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    u16 first;
    u16 second;
} RenderState;

typedef struct ScanlineTask ScanlineTask;

extern void func_0800F93C(RenderState *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(
    void (*callback)(RenderState *, u16 *), u32 size, u32 type,
    u16 *destination);
extern RenderState *func_0800C614(ScanlineTask *task);
extern void func_08010058(void *object, u16 first, u8 count,
                         u8 start, u8 end);
extern void func_0800F770(s16 x, s16 y, u16 first, u16 second,
                         Scanline *ranges, u8 mode);
extern u16 data_04000040[];

static inline void render_object(ScanlineTask *task)
{
    RenderState *state = func_0800C614(task);

    func_08010058(task, 0, 160, 245, 250);
    func_0800F770(state->x, state->y, state->first, state->second,
                  state->lines, 1);
}

/* Complete [0x0800FD4C, 0x0800FDFC), 176 bytes. */
ScanlineTask *func_0800FD4C(u8 window, u16 x, u16 y, u16 value)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C, 0x298, 2,
                                    data_04000040 + window);
    RenderState *state = func_0800C614(task);

    state->x = x;
    state->y = y;
    state->type = 7;
    state->first = value;
    state->second = 0;
    render_object(task);
    return task;
}
