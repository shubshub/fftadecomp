#include "ffta.h"

/* Complete [0x080078A8, 0x08007A4C): 420 bytes, 210 instructions.
 * f0b557464e464546e0b486b00004060c0904090c8c4612041b041b0c140c121403923004
 * 824600140490121a9046002a01da5242904619040a1491466346180402144d46af1a0b1c
 * 051c002f00da7f42381c474500da4046013002905046000c0090290c0191012040428246
 * 04990398814203da4a4501da01218a46b84543dd310420040c14021c91420add160c2004
 * 040c9d4201dd012292461b0c9c46220431044346d80f404444101314914270dc009d2804
 * 00148146019a100406141d1c09146346180403144846421a002a00da5242f01a002800da
 * 4042904200da101c80000e9a801801804380e41b002c05da4444524698180004000c8446
 * 481c01040814a842dcdd44e028149d420ddd1b0c9c460004030c30042104884201dd0124
 * a2460e0c1b0460460504f80f38184410291c1a1499422cdc009b180400148446019d2804
 * 001481460592300402140b146046811a002900da49424d46e81a002800da4042884200da
 * 081c80000e994018028043804546641b002c04dae419514650180004060c581c01040814
 * 059a9042dbdd029806b038bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    s16 x;
    s16 y;
} LinePoint;

/* Stores (x, y) at index max(|ox - x|, |oy - y|).  The ROM has this block
 * once in each loop: 0x08007968-0x08007990 and 0x080079F2-0x08007A1A. */
static inline void set_point(LinePoint *points, s32 ox, s32 oy, s32 x, s32 y)
{
    s32 hx;
    s32 hy;
    s32 index;

    hx = ox - x;
    if (hx < 0)
        hx = -hx;
    hy = oy - y;
    if (hy < 0)
        hy = -hy;
    index = hx > hy ? hx : hy;
    points[index].x = x;
    points[index].y = y;
}

/* Rasterizes the line (x0, y0)-(x1, y1) into points[], indexed by each
 * point's Chebyshev distance from (x0, y0), and returns the point count. */
s32 func_080078A8(s16 x0, s16 y0, s16 x1, s16 y1, LinePoint *points)
{
    s16 ox;
    s16 oy;
    s32 dx;
    s32 dy;
    s32 length;
    s32 direction;
    /* Wider than the coordinates: the ROM sign-extends the swapped value
     * (0x0800792C, 0x080079B0) and narrows it back (0x08007936, 0x080079BA). */
    s32 temp;
    s32 error;

    dx = x1 - x0;
    if (dx < 0)
        dx = -dx;
    dy = y1 - y0;
    if (dy < 0)
        dy = -dy;
    length = (dx > dy ? dx : dy) + 1;
    ox = x0;
    oy = y0;
    direction = -1;
    if (x0 < x1 && y0 < y1)
        direction = 1;

    if (dx > dy) {
        if (x0 > x1) {
            temp = x0;
            x0 = x1;
            x1 = temp;
            if (y0 > y1)
                direction = 1;
            y0 = y1;
        }
        error = dx / 2;
        for (; x0 <= x1; x0++) {
            set_point(points, ox, oy, x0, y0);
            error -= dy;
            if (error < 0) {
                error += dx;
                y0 += direction;
            }
        }
    } else {
        if (y0 > y1) {
            temp = y0;
            y0 = y1;
            y1 = temp;
            if (x0 > x1)
                direction = 1;
            x0 = x1;
        }
        error = dy / 2;
        for (; y0 <= y1; y0++) {
            set_point(points, ox, oy, x0, y0);
            error -= dx;
            if (error < 0) {
                error += dy;
                x0 += direction;
            }
        }
    }
    return length;
}
