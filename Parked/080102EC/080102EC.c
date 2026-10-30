#include "ffta.h"

typedef struct {
    u16 start;
    u16 end;
} RenderRange080102EC;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange080102EC ranges[160];
    u16 radii[2];
} RenderState080102EC;

extern void *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
extern void func_0800F6A8(s32 x, s32 y, u16 radius_x, u16 radius_y,
                        RenderRange080102EC *ranges, u8 enabled);

/* 0x080102EC..0x08010358 - 108 bytes including literal pool. */
void func_080102EC(void *object, u16 radius_x, u16 radius_y)
{
    RenderState080102EC *state = func_0800C614(object);

    state->radii[0] = radius_x;
    state->radii[1] = radius_y;
    state = func_0800C614(object);
    func_08010058(object, 0, 160, 245, 250);
    func_0800F6A8(state->x, state->y, state->radii[0], state->radii[1],
                  state->ranges, 1);
}
