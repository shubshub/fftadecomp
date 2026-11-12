#include "ffta.h"

extern void func_0801E6F0(s16 *x, s16 *y);
extern void func_0801BB94(s16 x, s16 y, int mode, int effect, int option);

/* Complete target: [0x080D8604, 0x080D8708), 260 bytes. */
int func_080D8604(s16 *bounds, s16 *area, u8 adjust, s16 *alternate)
{
    int contained = 1;
    s16 x, y;
    s16 *reference;

    if (area[0] > bounds[0])
        contained = 0;
    else if (area[2] < bounds[2])
        contained = 0;
    if (area[1] > bounds[1])
        contained = 0;
    else if (area[3] < bounds[3])
        contained = 0;
    if (!contained && adjust) {
        func_0801E6F0(&x, &y);
        reference = area;
        if (alternate)
            reference = alternate;
        if (reference[0] > bounds[0])
            x -= reference[0] - bounds[0];
        else if (reference[2] < bounds[2])
            x += bounds[2] - reference[2];
        if (reference[1] > bounds[1])
            y -= reference[1] - bounds[1];
        else if (reference[3] < bounds[3])
            y += bounds[3] - reference[3];
        func_0801BB94(x, y, 4, 0x10, 4);
    }
    return contained;
}
