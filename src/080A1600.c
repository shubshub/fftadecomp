#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} Object080A1600;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Position080A1600;

typedef struct {
    u8 unknown_00[0x38];
    Position080A1600 current;
    u8 unknown_40[0x140];
} Motion080A1600;

/* One six-byte OAM entry (attributes 0 to 2).  The frame is initialised from
 * data_083943B4 (src/080A0FF0.c), whose bytes are 01 00 | F8 00 F8 41 00 00:
 * one entry, 16x16.  The entry is unaligned: the ROM inserts the ten tile
 * bits a byte at a time (0x080A1914, 0x080A191C-0x080A1924). */
typedef struct __attribute__((packed)) {
    u16 attr0;
    u16 attr1;
    u16 tile : 10;
    u16 priority : 2;
    u16 palette : 4;
} Oam080A1600;

typedef struct {
    u16 count;
    Oam080A1600 entries[1];
} Frame080A1600;

typedef struct {
    u8 unknown_00[0x14];
    void *menu;
    void *attachment;
    void *sprite;
    u8 unknown_20[0x1C];
    void *graphics;
    Frame080A1600 frame;
    u8 unknown_48[2];
    s8 level;
    u8 unknown_4B;
    Motion080A1600 motion;
    Object080A1600 *object;
    Position080A1600 target;
    u16 animation;
    s16 count;
    s16 index;
    s16 curve;
    s16 value;
    s16 mode;
    Position080A1600 points[0x100];
    s32 offscreen;
    u32 argument_a;
    u32 argument_b;
    u16 phase;
} State080A1600;

typedef struct {
    Position080A1600 position;
    u16 value_08;
    u16 value_0A;
    u16 value_0C;
    u16 value_0E;
} RequestState;

extern RequestState data_0200F898;
extern u32 func_0809FDC0(RequestState *state);
extern void func_08022854(void *graphics);
extern void func_080A0BB8(Motion080A1600 *motion, s16 start_x, s16 start_y,
                          s16 start_z, s16 end_x, s16 end_y, s16 end_z,
                          s16 value, s16 mode, u32 argument_a,
                          u32 argument_b);
extern s32 func_080A0D04(Motion080A1600 *motion, s32 index, s32 progress,
                         Position080A1600 *out);
extern s32 func_0809D6BC(s8 dx, s8 dy);
extern void func_0809A68C(Object080A1600 *object, u8 value);
extern void func_0809836C(Object080A1600 *object, u16 action, s8 direction,
                          u16 option);
extern s32 func_08099C34(Object080A1600 *object);
extern void func_08141520(u16 sound);
extern void func_0801E6F0(s16 *x, s16 *y);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x, s16 *screen_y,
                          s16 *screen_z);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern void func_0808EFCC(void *object, s16 x, s16 y, s16 z);
extern void func_0808F7CC(void *object);
extern void func_08021BD4(void *menu, void *attachment);
extern void func_08021B54(void *menu);

/* An inlined copy of func_080A83A4 (src/080A83A4.c), as in src/080A1A14.c.
 * The ROM keeps its null test of `source` (0x080A198A). */
static inline u32 inlined_080A83A4(const Position080A1600 *source,
                                   u32 value_08, u32 value_0E, u32 value_0A,
                                   u32 value_0C)
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

/* An inlined copy of func_080A8430 (src/080A8430.c). */
static inline s32 inlined_080A8430(const Position080A1600 *first,
                                   const Position080A1600 *second)
{
    s32 dx = first->x - second->x;
    s32 dz;
    s32 first_y;
    s32 second_y;
    s32 angle;

    if (dx < 0) {
        dx = -dx;
    }
    dz = first->z - second->z;
    if (dz < 0) {
        dz = -dz;
    }
    second_y = second->y;
    first_y = first->y;
    angle = func_08141860(dx + dz, second_y - first_y) >> 8;
    angle -= 0x40;
    angle = (0xFF & ~angle) - 0x0F;
    if (angle < 0) {
        angle = 0;
    }
    if (angle >= 0x7F) {
        angle = 0x7F;
    }
    return angle / 16;
}

/* Raises state->level one step towards the level func_080A8430 gives for the
 * slope from `current` to `next`.  The ROM builds `next` as
 * (index * 8 + state) + 0x1E4 (0x080A1882-0x080A188A), the form of an inline
 * function's argument, and keeps both pointers for the height test after
 * the slope call (0x080A18EA-0x080A18F0). */
static inline void raise_level(State080A1600 *state,
                               const Position080A1600 *current,
                               const Position080A1600 *next)
{
    s32 limit = inlined_080A8430(current, next);

    if (current->y != next->y && state->level < limit)
        state->level++;
}

/* Complete target [0x080A1600, 0x080A1A14), 1044 bytes. */
u32 func_080A1600(State080A1600 *state)
{
    switch (state->phase) {
    case 0:
        func_08022854(state->graphics);
        state->graphics = 0;
        state->phase = 1;
        break;
    case 1:
        func_080A0BB8(&state->motion, state->object->x, state->object->y,
                      state->object->z, state->target.x, state->target.y,
                      state->target.z, state->value, state->mode,
                      state->argument_a, state->argument_b);
        state->phase = 2;
        break;
    case 2: {
        s32 i;

        for (i = 0; i < state->count; i++)
            func_080A0D04(&state->motion, state->curve, i, &state->points[i]);
        state->motion.current = state->points[0];
        state->index++;
        state->phase = 3;
        break;
    }
    case 3: {
        s32 direction;
        Object080A1600 *object;
        s16 object_row;
        s32 dy;
        s32 distance;
        s32 action;

        direction = func_0809D6BC(
            (s8)((state->target.x >> 5) - (state->object->x >> 5)),
            (s8)((state->target.z >> 5) - (state->object->z >> 5)));
        func_0809A68C(state->object, 1);
        object = state->object;
        object_row = (s8)(object->y >> 5);
        dy = (s8)(state->target.y >> 5) - object_row;
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
        state->phase = 4;
        break;
    }
    case 4: {
        Position080A1600 *position;
        Position080A1600 camera;
        Position080A1600 screen;
        s32 left;
        s32 right;
        s32 top;
        s32 bottom;
        s32 offscreen;

        if (func_08099C34(state->object) != 0)
            break;
        func_08141520(0x7F);
        state->phase = 5;
        position = state->points + state->count - 1;
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
        break;
    }
    case 5:
        if (state->count - 2 >= state->index) {
            raise_level(state, &state->motion.current,
                        &state->points[state->index]);
            state->frame.entries->tile = state->level << 2;
            func_0808EFCC(state->sprite, state->motion.current.x,
                          state->motion.current.y, state->motion.current.z);
            state->motion.current = state->points[state->index];
        } else {
            func_0808EFCC(state->sprite, state->motion.current.x,
                          state->motion.current.y, state->motion.current.z);
        }
        if (state->offscreen != 0)
            inlined_080A83A4(&state->motion.current, 8, 1, -0x78, -0x56);
        state->index++;
        if (state->count < state->index)
            state->phase = 6;
        break;
    case 6:
        if (state->graphics != 0) {
            func_08022854(state->graphics);
            state->graphics = 0;
        }
        func_0808F7CC(state->sprite);
        func_08021BD4(state->menu, state->attachment);
        func_08021B54(state->menu);
        state->menu = 0;
        state->attachment = 0;
        return 0;
    }
    return 1;
}
