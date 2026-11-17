#include "ffta.h"

// Complete target: [0x080FDEE8, 0x080FDF90), 168 bytes, 71 instructions.
struct Rect080FDEE8 {
    u32 left : 16;
    u32 top : 16;
    u32 right : 16;
    u32 bottom : 16;
};

extern const s16 data_08149DA4[];
extern const s16 data_08149DAC[];
extern void func_080D8C58(void *object, u16 *x, u16 *y);
extern void func_080DBF90(void *object, void *bounds, u32 adjust, void *alternate);
extern void func_080D8604(void *bounds, void *area, u32 adjust, void *alternate);

void func_080FDEE8(void *object, void *target)
{
    u16 x, y;
    struct Rect080FDEE8 area = *(const struct Rect080FDEE8 *)data_08149DA4;
    struct Rect080FDEE8 alternate = *(const struct Rect080FDEE8 *)data_08149DAC;
    struct Rect080FDEE8 bounds;

    if (target) {
        func_080DBF90(target, &area, 1, &alternate);
        return;
    }
    func_080D8C58(object, &x, &y);
    bounds.left = x - 16;
    bounds.right = x + 16;
    bounds.top = y - 8;
    bounds.bottom = y + 8;
    func_080D8604(&bounds, &area, 1, &alternate);
}
