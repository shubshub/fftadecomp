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

typedef struct {
    u16 start;
    u16 end;
} Range0800F6A8;

extern u8 data_02009160;
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);

/* Target: complete [0x0800F6A8, 0x0800F770), 200 bytes.
 * SHA-256: fc223de5fa4d5443b77615f3d5b92cba8d0331bfb5e3e9f8c20b3dfacf76f7fb.
 */
void func_0800F6A8(u16 x, u16 y, u16 radius_x, u16 radius_y,
                   Range0800F6A8 *ranges, u8 enabled)
{
    LineState state;
    s32 i;

    if (radius_x == 0 || radius_y == 0)
        return;
    if (enabled == 0)
        y = radius_y;

    func_080075CC(&state, radius_x, 0, 0, radius_y);
    for (i = 0; i < radius_y; i++) {
        s16 row = (s16)((s16)y - i);

        if (row >= 0 && (enabled == 0 || row <= 159)) {
            ranges[row].start = (s16)x - state.x;
            ranges[row].end = (s16)x + state.x + data_02009160;
        }

        row = (s16)((s16)y + i);
        if (row >= 0 && (enabled == 0 || row <= 159)) {
            ranges[row].start = (s16)x - state.x;
            ranges[row].end = (s16)x + state.x + data_02009160;
        }

        func_080076A0(&state);
    }
}
