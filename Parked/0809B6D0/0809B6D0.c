#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
} Actor0809B6D0;

typedef struct {
    Actor0809B6D0 *actor;
    u8 unknown_04[0xc];
    s16 target_x;
    s16 target_height;
    s16 target_y;
    u8 unknown_16[4];
    u16 field_1a;
    s16 field_1c;
    u8 unknown_1e[9];
    u8 direction;
} Movement0809B6D0;

static inline void set_direction(s32 direction, s8 *dx, s8 *dy)
{
    switch (direction) {
    case 0:
        *dx = 0;
        *dy = 1;
        break;
    case 1:
        *dx = -1;
        *dy = 0;
        break;
    case 2:
        *dx = 0;
        *dy = -1;
        break;
    case 3:
        *dx = 1;
        *dy = 0;
        break;
    default:
        *dx = 0;
        *dy = 0;
        break;
    }
}

static inline s32 clamp_movement(s32 current, s32 target, s32 next)
{
    if (target < current)
        return target < next ? next : target;
    return target > current && target > next ? next : target;
}

/* Complete target [0x0809B6D0, 0x0809B7BE): 238 bytes, 119 instructions.
 * 30b581b0041c273000780006001669466d4601352a1c01280dd0012802dc002805d018e002280ad003280fd013e008700120287012e001225242101c07e00020087001235b42181c287007e0012008700020287002e000200870107020680821435e1020225e1c20215e6846007800060016484318189a4202da011c8a4205db111c994202dd814200dd011c2068018120680c21435e1420225e1c20215e00202856484318189a4202da011c8a4205db111c994202dd814200dd011c2068818122680823d15e1023e05e81420ad10c20115e1422a05e814204d1608b01306083002000e0012001b030bc02bc0847
 */
u32 func_0809B6D0(Movement0809B6D0 *state)
{
    s8 dx, dy;
    s32 current, target, next;

    set_direction((s8)state->direction, &dx, &dy);

    current = state->actor->x;
    target = state->target_x;
    next = current + state->field_1c * dx;
    state->actor->x = clamp_movement(current, target, next);

    current = state->actor->y;
    target = state->target_y;
    next = current + state->field_1c * dy;
    state->actor->y = clamp_movement(current, target, next);

    if (state->actor->x == state->target_x &&
        state->actor->y == state->target_y) {
        state->field_1a++;
        return 0;
    }
    return 1;
}
