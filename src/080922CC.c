#include "ffta.h"

/* Target: [0x080922CC, 0x0809238E), 194 bytes.
 * f0b585b0071c081c111c1a1c0a9c0b9d240424142d042d14000400140904091412041214
 * 6e460a36009603ab019302ab8af70cfb02a80021405e0019000238600022b05e40190002
 * 7860b869002802d180204000b86104ac6d461235201c291c8cf7e0f92088b8832888f883
 * 1c20395e0902b9601e22b85e0302fb600c9838620d9878613868421a002a00da52427868
 * c11a002900da49428a4201dd7a6200e079621002001409020914aff073fa0004000e3861
 * 80204000b86105b0f0bc01bc0047
 */

/* The camera motion that func_08092390 (src/08092390.c) steps; the names
 * follow that updater and the motion stepper func_08007AD0. */
typedef struct Motion080922CC {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
    s16 start_x;
    s16 start_y;
    s32 divisor;
    s32 span;
} Motion080922CC;

extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                          s16 *screen_y, s16 *depth);
extern void func_0801E6F0(s16 *x, s16 *y);
extern u16 func_08141860(s16 horizontal, s16 vertical);

void func_080922CC(Motion080922CC *state, s16 x, s16 y, s16 z,
                   s32 offset_x, s32 offset_y, s32 divisor, s32 turn_percent)
{
    /* func_0801C918's three outputs, an array as its other callers keep them
     * (src/080DC014.c, 080DC058.c, 080DC0BC.c, 080DC12C.c): the ROM passes
     * sp+8, sp+0xA and sp+0xC (0x080922F0-0x080922FA) and leaves sp+0xE
     * unused below the camera pair at sp+0x10/0x12 (0x08092322-0x08092326). */
    s16 projected[3];
    s16 *screen;
    s16 camera_x, camera_y;
    s32 add_x, add_y;
    s32 dx, dy;

    /* Both stack arguments are narrowed to 16 bits at entry (ldr, then
     * lsls/asrs #16 at 0x080922D8-0x080922E2), before the projection call;
     * the caller src/08096F3C.c passes them as s32. */
    add_x = (s16)offset_x;
    add_y = (s16)offset_y;
    func_0801C918(x, y, z, &projected[0], &projected[1], &projected[2]);
    /* The outputs are read in order through a cursor.  The ROM reads the
     * second through the register that carried its address into the call
     * (r6 = sp+0xA at 0x080922F0, passed at 0x080922F4, ldrsh r0, [r6, r2]
     * at 0x0809230E); the first is re-derived from sp (0x08092300). */
    screen = projected;
    state->target_x = (*screen++ + add_x) << 8;
    state->target_y = (*screen + add_y) << 8;
    if (state->speed == 0)
        state->speed = 256;
    func_0801E6F0(&camera_x, &camera_y);
    state->start_x = camera_x;
    state->start_y = camera_y;
    state->current_x = state->start_x << 8;
    state->current_y = state->start_y << 8;
    state->divisor = divisor;
    state->turn_percent = turn_percent;
    dx = state->target_x - state->current_x;
    if (dx < 0)
        dx = -dx;
    dy = state->target_y - state->current_y;
    if (dy < 0)
        dy = -dy;
    if (dx > dy)
        state->span = dx;
    else
        state->span = dy;
    /* BUG: the initial heading is taken from |dx| and |dy| (0x08092352-0x08092376),
     * so it always points into the first quadrant. func_08007AD0 turns by
     * turn_percent of the error on every step, so only turn_percent 100, which
     * every known caller passes, corrects it on the first step. With a smaller
     * value, a target left of or above the camera starts off course. */
#ifdef BUGFIX
    state->angle = func_08141860((s16)((state->target_x - state->current_x) >> 8),
                                 (s16)((state->target_y - state->current_y) >> 8)) >> 8;
#else
    state->angle = func_08141860((s16)(dx >> 8), (s16)(dy >> 8)) >> 8;
#endif
    state->speed = 256;
}
