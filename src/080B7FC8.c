#include "ffta.h"

/* The display records of src/080B8100.c (Display080B8100): callers pass
 * &menu->display[0..6] (0x080B844A, 0x080B84AE, 0x080B8514-0x080B8550) and
 * draw resource at +0 with ldrsh x/y at +4/+6 (0x080B8472-0x080B8486).
 */
typedef struct {
    const void *resource;
    s16 x;
    s16 y;
    u8 unknown_08[4];
    s16 target_x;
    s16 target_y;
    s16 divisor_x;
    s16 divisor_y;
    s16 min_step_x;
    s16 min_step_y;
    u16 approach;
    u8 unknown_1a[6];
} Display080B7FC8;

extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete [0x080B7FC8, 0x080B8100): 312 bytes, 151 reached instructions.
 * f0b5474680b4041ca089a188401a0004000c8046e089e188401a0004070c1021605e002809d04246100400141023e15e
 * 8af05efb0004060c00e000261221605e002808d0380400141222a15e8af050fb0004050c00e00025300401140a1c0029
 * 00da4a421423e05e824209da002903daa08a40420004060c3004002800dda68a280401140a1c002900da4a421623e05e
 * 824209da002903dae08a40420004050c2804002800dde58a208b002823d041460804021c3b04002a01d1002b36d01114
 * 002900da49421427e05f814200da160c1914002900da49421622a05e814200da1d0c30040014a388c018a08028040014
 * e788c01914e0a288101c203000040a49884213d8e188081c20300004000cdf280cd830040014101aa08028040014081a
 * e080012003e0000000002f01002008bc9846f0bc02bc0847
 */
u8 func_080B7FC8(Display080B7FC8 *display)
{
    s16 dx = display->target_x - display->x;
    s16 dy = display->target_y - display->y;
    s16 step_x;
    s16 step_y;

    if (display->divisor_x != 0)
        step_x = func_081426B8(dx, display->divisor_x);
    else
        step_x = 0;
    if (display->divisor_y != 0)
        step_y = func_081426B8(dy, display->divisor_y);
    else
        step_y = 0;

    if ((step_x < 0 ? -step_x : step_x) < display->min_step_x) {
        if (step_x < 0)
            step_x = -display->min_step_x;
        if (step_x > 0)
            step_x = display->min_step_x;
    }
    if ((step_y < 0 ? -step_y : step_y) < display->min_step_y) {
        if (step_y < 0)
            step_y = -display->min_step_y;
        if (step_y > 0)
            step_y = display->min_step_y;
    }

    if (display->approach != 0) {
        if (dx == 0 && dy == 0)
            return 0;
        if ((dx < 0 ? -dx : dx) < display->min_step_x)
            step_x = dx;
        if ((dy < 0 ? -dy : dy) < display->min_step_y)
            step_y = dy;
        display->x += step_x;
        display->y += step_y;
        return 1;
    } else {
        if ((u16)(display->x + 0x20) > 0x12F)
            return 0;
        if ((u16)(display->y + 0x20) > 0xDF)
            return 0;
        display->x -= step_x;
        display->y -= step_y;
        return 1;
    }
}
