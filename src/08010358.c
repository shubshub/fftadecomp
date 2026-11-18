#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct RenderState {
    s16 x;
    s16 y;
    u8 unknown_04[4];
    Scanline ranges[160];
    u16 first;
    u16 second;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u32 first, u32 count,
                         u16 start, u16 end);
extern void func_0800F770(s16 x, s16 y, u16 first, u16 second,
                         Scanline *ranges, u8 mode);

static inline void render_object(void *object)
{
    RenderState *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800F770(state->x, state->y, state->first, state->second,
                  state->ranges, 1);
}

/* 08010358..080103B0: 88 bytes, 40 instructions. */
void func_08010358(void *object, u16 value)
{
    func_0800C614(object)->first = value;
    render_object(object);
}
