#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
} MovingEntity;

typedef struct {
    MovingEntity *entity;
    u8 unknown_04[0xc];
    s16 end_x;
    s16 end_height;
    s16 end_y;
    u8 unknown_16[4];
    s16 index;
    s16 step;
    u8 unknown_1e[9];
    s8 direction;
} Path0809B6D0;

/* The text of set_direction in src/0809B544.c, which expands it at
 * 0x0809B584; this function expands it at 0x0809B6DE.  func_0809D66C
 * (src/0809D66C.c) is an out-of-line function with the same body, but its
 * `s8 direction` parameter does not reproduce either expansion. */
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

/* Expanded twice, at 0x0809B744 for x and at 0x0809B774 for y: the same
 * twelve instructions.  The ROM has no out-of-line copy. */
static inline s32 step_toward(s32 current, s32 target, s32 step)
{
    s32 next = current + step;

    if (target < current && target < next)
        return next;
    if (target > current && target > next)
        return next;
    return target;
}

/* Complete target [0x0809B6D0, 0x0809B7BE): 238 bytes, 119 instructions.
 * 30b581b0041c273000780006001669466d4601352a1c01280dd0012802dc002805d018e002280ad003280fd013e008700120287012e001225242101c07e00020087001235b42181c287007e0012008700020287002e000200870107020680821435e1020225e1c20215e6846007800060016484318189a4202da011c8a4205db111c994202dd814200dd011c2068018120680c21435e1420225e1c20215e00202856484318189a4202da011c8a4205db111c994202dd814200dd011c2068818122680823d15e1023e05e81420ad10c20115e1422a05e814204d1608b01306083002000e0012001b030bc02bc0847
 */
u32 func_0809B6D0(Path0809B6D0 *path)
{
    s8 dx, dy;

    set_direction(path->direction, &dx, &dy);
    path->entity->x = step_toward(path->entity->x, path->end_x,
                                  path->step * dx);
    path->entity->y = step_toward(path->entity->y, path->end_y,
                                  path->step * dy);

    if (path->entity->x == path->end_x &&
        path->entity->y == path->end_y) {
        path->index++;
        return 0;
    }
    return 1;
}
