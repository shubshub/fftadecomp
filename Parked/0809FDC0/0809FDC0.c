#include "ffta.h"

// Complete [0x0809FDC0, 0x0809FEEE): 302 bytes.
// f0b586b0071c02ad69460a31281c7ef78ffc0021785e0222b95e0423fa5e04ac6b461233
// 009305ab0193231c7cf794fd78892188401820806088b989401860800022a15e02a80023
// c05e0e1a0220215e0222a85e0d1a3004001429040914a1f01ffd0004040e002e00da7642
// 002d00da6d42ae4200db351c201c67f711fe0004001468430612201c67f700fe00040014
// 68430512002e03d1002d1dd1002042e00823f95e301ca2f027fc002811d1301c002e00da
// 70420e217c5ea0420add311c002e00da7142301ca2f016fc061c664300e0061c002d19d0
// 0822b95e281ca2f00bfc002811d1281c002d00da68420e23fc5ea0420add291c002d00da
// 6942281ca2f0fafb051c654300e0051c02a8008880190004001402a949884919090409
// 147ef77efb012006b0f0bc02bc0847

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unknown_06;
    s16 step;
    u16 offset_x;
    u16 offset_y;
    s16 limit;
} State0809FDC0;

extern void func_0801E6F0(s16 *x, s16 *y);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x, s16 *screen_y,
                          s16 *depth);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);
extern void func_0801E5E0(s16 x, s16 y);

u32 func_0809FDC0(State0809FDC0 *state)
{
    int quotient;
    u32 angle;
    int dx;
    s16 origin[3];
    int dy;
    s16 *p = origin;
    s16 screen[3];

    func_0801E6F0(p, &origin[1]);
    func_0801C918(state->x, state->y, state->z, &screen[0], &screen[1], &screen[2]);
    screen[0] += state->offset_x;
    screen[1] += state->offset_y;
    dx = screen[0] - origin[0];
    dy = screen[1] - p[1];
    angle = func_08141860(dx, dy) >> 8;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    if (dx >= dy)
        dy = dx;
    dx = func_08007A60(angle) * dy >> 8;
    dy = (s16)func_08007A4C(angle) * dy >> 8;
    if (dx == 0 && dy == 0)
        return 0;
    if (dx != 0) {
        quotient = dx / state->step;
        if (quotient == 0) {
            if ((dx < 0 ? -dx : dx) > state->limit)
                dx = (dx / (dx < 0 ? -dx : dx)) * state->limit;
        } else {
            dx = quotient;
        }
    }
    if (dy != 0) {
        quotient = dy / state->step;
        if (quotient == 0) {
            if ((dy < 0 ? -dy : dy) > state->limit)
                dy = (dy / (dy < 0 ? -dy : dy)) * state->limit;
        } else {
            dy = quotient;
        }
    }
    func_0801E5E0(origin[0] + dx, origin[1] + dy);
    return 1;
}
