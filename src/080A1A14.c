#include "ffta.h"

// Complete [0x080A1A14, 0x080A1B56): 322 bytes, 161 instructions.

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} Object080A1A14;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Position080A1A14;

typedef struct {
    Object080A1A14 *object;
    Position080A1A14 position;
    s32 offscreen;
    u16 animation;
    u8 unknown_12[2];
    u16 phase;
} State080A1A14;

typedef struct {
    Position080A1A14 position;
    u16 value_08;
    u16 value_0A;
    u16 value_0C;
    u16 value_0E;
} RequestState;

extern RequestState data_0200F898;
extern u32 func_0809FDC0(RequestState *state);
extern s32 func_0809D6BC(s8 dx, s8 dy);
extern void func_0809A68C(Object080A1A14 *object, u32 value);
extern void func_0809836C(Object080A1A14 *object, u16 action, s8 direction,
                          u16 option);
extern s32 func_08099C34(Object080A1A14 *object);
extern void func_08141520(u16 sound);
extern void func_0801E6F0(s16 *x, s16 *y);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x, s16 *screen_y,
                          s16 *screen_z);

/* An inlined copy of func_080A83A4 (src/080A83A4.c). */
static inline u32 Request080A1A14(const Position080A1A14 *source, u32 value_08,
                                  u32 value_0E, u32 value_0A, u32 value_0C)
{
    if (source != 0)
        data_0200F898.position = *source;
    data_0200F898.value_0A = value_0A;
    data_0200F898.value_0C = value_0C;
    if (value_08 != 0)
        data_0200F898.value_08 = value_08;
    if (value_0E != 0)
        data_0200F898.value_0E = value_0E;
    return func_0809FDC0(&data_0200F898);
}

u32 func_080A1A14(State080A1A14 *state)
{
    switch (state->phase) {
    case 0: {
        s32 direction;
        Object080A1A14 *object;
        s16 object_row;
        s32 dy;
        s32 distance;
        s32 action;

        direction = func_0809D6BC(
            (s8)((state->position.x >> 5) - (state->object->x >> 5)),
            (s8)((state->position.z >> 5) - (state->object->z >> 5)));
        func_0809A68C(state->object, 1);
        object = state->object;
        object_row = (s8)(object->y >> 5);
        dy = (s8)(state->position.y >> 5) - object_row;
        distance = dy;
        if (dy < 0)
            distance = -dy;
        action = 7;
        if (distance > 1) {
            action = 8;
            if (dy > 0)
                action = 6;
        }
        func_0809836C(object, action, (s8)direction, state->animation);
        state->phase = 1;
        break;
    }
    case 1: {
        Position080A1A14 *position;
        Position080A1A14 camera;
        Position080A1A14 screen;
        s32 left;
        s32 right;
        s32 top;
        s32 bottom;
        s32 offscreen;

        if (func_08099C34(state->object) != 0)
            break;
        func_08141520(0x80);
        position = &state->position;
        func_0801E6F0(&camera.x, &camera.y);
        func_0801C918(position->x, position->y, position->z,
                      &screen.x, &screen.y, &screen.z);
        left = camera.x + 0x18;
        right = camera.x + 0xD8;
        top = camera.y + 0x24;
        bottom = camera.y + 0x88;
        if (screen.x <= left || screen.x >= right
            || screen.y <= top || screen.y >= bottom)
            offscreen = 1;
        else
            offscreen = 0;
        state->offscreen = offscreen;
        state->phase = 2;
        break;
    }
    case 2:
        if (state->offscreen != 0)
            Request080A1A14(&state->position, 8, 1, -0x78, -0x56);
        return 0;
    }
    return 1;
}
