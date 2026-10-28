#include "ffta.h"

struct __attribute__((packed)) ScanlineBounds {
    u8 right;
    u8 left;
};

extern const s8 data_083A6BDC[];
extern void func_080DAC40(void *, s16, s16, u16);
extern struct ScanlineBounds *func_080DABB4(void *);

/* Target: complete [0x0811BEC0, 0x0811C018), 344 bytes, 167 instructions. */
void func_0811BEC0(void *window, u8 radius, u8 *left_phase, u8 *right_phase,
                   u8 *timer, u8 paused)
{
    struct ScanlineBounds *bounds;
    s16 row;
    s16 i;
    u8 left;
    u8 right;
    s16 step;
    const s8 *steps = data_083A6BDC;

    func_080DAC40(window, 120, 80, radius);
    if (paused)
        return;

    bounds = func_080DABB4(window);
    row = 80 - radius;
    left = *left_phase;
    right = *right_phase;
    for (i = 0; i < radius * 2; i++, row++) {
        if (row < 0)
            continue;
        if (row <= 159) {
            step = steps[(s8)left];
            if (bounds[row].left + step < 0)
                bounds[row].left = 0;
            else
                bounds[row].left += step;

            step = steps[(s8)right];
            if (bounds[row].right + step > 239)
                bounds[row].right = 240;
            else
                bounds[row].right += step;

            if (bounds[row].left > bounds[row].right)
                bounds[row].right = bounds[row].left;

            if (++left > 19)
                left = 0;
            if (++right > 19)
                right = 0;
        }
    }

    if (--*timer == 0) {
        if ((s8)--*left_phase < 0)
            *left_phase = 19;
        if (++*right_phase > 19)
            *right_phase = 0;
        *timer = 2;
    }
}
