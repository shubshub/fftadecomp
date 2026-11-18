#include "ffta.h"

typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

extern void func_080DAC80(void *task, s16 x, s16 y, u16 width, u16 height);
extern void *func_080DABB4(void *task);
extern void func_080E0608(struct InterpolationState *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(struct InterpolationState *state);

void func_0811435C(void *task, s16 x, s16 y, u16 width, u16 height, u16 shift)
{
    struct InterpolationState motion;
    WindowLine *lines;
    s16 row, value;

    func_080DAC80(task, x, y, width, height);
    func_080E0608(&motion, shift, 0, height);
    lines = func_080DABB4(task);
    for (row = height - 1; row >= 0; row--) {
        func_080E064C(&motion);
        if (y - row >= 0) {
            value = lines[y - row].left + motion.current;
            if (value > 240)
                value = 240;
            lines[y - row].left = value;
            value = lines[y - row].right + motion.current;
            if (value > 240)
                value = 240;
            lines[y - row].right = value;
        }
        if (y + row < 160) {
            value = lines[y + row].left - motion.current;
            if (value < 0)
                value = 0;
            lines[y + row].left = value;
            value = lines[y + row].right - motion.current;
            if (value < 0)
                value = 0;
            lines[y + row].right = value;
        }
    }
}
