#include "ffta.h"

/* 0x0800F93C..0x0800F9C0: 132 bytes, 63 instructions:
 * f0b5051c0c1c2879092803d1281cfef729fc0ae00a2803d1281cfef787fc04e0
 * 0b2802d1281cfef781fce888012606402b1c08339f2559881a880027d85f0028
 * 01da002202e0f52800ddf52208040014002801da002102e0fa2800ddfa21002e
 * 04d0607861702078227003e0607862702078217002340433013d002ddbdaf0bc
 * 01bc0047
 */

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    u16 count;
    u16 frames[1][4];
} PositionedAnimation;

/* The window shape's state, as func_0800F9C0 (which registers this function
 * as a scanline callback) declares it. */
typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    s32 *shapes;
    PositionedAnimation *animation;
    u16 frame;
    u16 remaining;
    u16 frameCount;
} AnimatedScanlines;

/* The scanline buffer uses the WINxH byte order.
 *
 * volatile: the ROM loads each byte just before storing it and never uses
 * the value (ldrb at 0x0800F99E, 0x0800F9A2, 0x0800F9A8 and 0x0800F9AC, each
 * followed by the strb of the same byte); without the qualifier agbcc drops
 * all four.  The buffer is the bank the scanline manager 0800C4B4 passes
 * to the callback and then submits for HBlank DMA to WIN0H or WIN1H. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

extern void func_0800E1A0(AnimatedScanlines *state);
extern void func_0800E268(AnimatedScanlines *state);

/* The scanline callback of the window shapes 0800F9C0 and its siblings
 * register: types 9 to 11 first redraw the shape's rows (types 10 and 11
 * each have their own call at 0x0800F956 and 0x0800F962), then every row's
 * span is clamped to the screen (left 0..245, right 0..250) and written as
 * the WINxH halfword, its edges swapped when bit 0 of flags is set. */
void func_0800F93C(AnimatedScanlines *state, WindowLine *edges)
{
    u32 swap;
    Scanline *line;
    s32 remaining;

    if (state->type == 9)
        func_0800E1A0(state);
    else if (state->type == 10)
        func_0800E268(state);
    else if (state->type == 11)
        func_0800E268(state);

    swap = state->flags & 1;
    line = state->lines;
    for (remaining = 159; remaining >= 0; remaining--) {
        s16 right = line->right;
        s16 left = line->left;

        if (left < 0)
            left = 0;
        else if (left > 245)
            left = 245;
        if (right < 0)
            right = 0;
        else if (right > 250)
            right = 250;
        if (swap) {
            edges->left = right;
            edges->right = left;
        } else {
            edges->left = left;
            edges->right = right;
        }
        edges++;
        line++;
    }
}
