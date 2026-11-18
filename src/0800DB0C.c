#include "ffta.h"

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct __attribute__((packed)) {
    u8 eva : 8;
    u8 evb : 8;
} BlendRow;

typedef struct {
    BlendRow lines[160];
} BlendTable;

struct Object0800C614;
extern void *func_0800C614(const struct Object0800C614 *object);
extern void func_0800C64C(void *object);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);

void func_0800DB0C(void *object, s16 first_row, u8 count, u8 start_a, u8 start_b,
                   u8 end_a, u8 end_b)
{
    LineState a;
    LineState b;
    volatile BlendTable *table;
    int row;
    int i;

    if (first_row > 159)
        return;
    table = func_0800C614(object);
    row = first_row;
    if (row >= 0) {
        table->lines[row].eva = start_a;
        table->lines[row].evb = start_b;
    }
    row++;
    func_080075CC(&a, start_a, 0, end_a, count - 1);
    func_080075CC(&b, start_b, 0, end_b, count - 1);
    for (i = 1; i < count && row < 160; i++, row++) {
        func_080076A0(&a);
        func_080076A0(&b);
        if (row >= 0) {
            table->lines[row].eva = a.x;
            table->lines[row].evb = b.x;
        }
    }
    func_0800C64C(object);
}
