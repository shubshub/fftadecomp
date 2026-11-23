#include "ffta.h"

/* Target: complete [0x0811BEC0, 0x0811C018), 344 bytes, 167 instructions:
 * f0b557464e464546e0b482b0061c924600930b9c09060d0e2406240e78215022
 * 2b1cbef7adfe002c00d08de0301cbef761fe80465020401b0004000c51460b78
 * 009a1678002401946d00a9464c455eda56e00a4a1b0618168018002141560904
 * e0134546441960780d0c09144018171c002805da6078002005e00000dc6b3a08
 * 607840196178607032061016c0190021415609046446e0134546441920780d0c
 * 09144018ef2802dd2078f02002e020784019217820706146c813454644196178
 * 2078814202d9607821782070802149045818030e132b00d90023802464041019
 * 060e132e00d90026019d29048020400209186044000c0a0c01920914494506da
 * 04042014a4460028eedb9f28a1dd0a9c2078013820700006010e002914d15546
 * 2878013828700006002801da13202870009a1078013010700006000e132800d9
 * 117002200a9c207002b038bc9846a146aa46f0bc01bc0047
 */

/* One row of the window task's scanline payload: a WIN0H/WIN1H halfword,
 * right edge (X2) in the low byte, left edge (X1) in the high byte.  It is
 * the halfword 0811435C's WindowLine describes, declared here on u16
 * storage units: with u8 ones the function compiles to 336 bytes.
 *
 * volatile: the ROM loads an edge just before each store to it and never
 * uses the value (0x0811BF34 and 0x0811BF44 before the strb of the left
 * edge at 0x0811BF46, 0x0811BF68 and 0x0811BF72 before the right edge's at
 * 0x0811BF74, 0x0811BF88 before 0x0811BF8A), and it reads an edge again
 * although the test above has just loaded it (0x0811BF40 after 0x0811BF26,
 * 0x0811BF6E after 0x0811BF5C, 0x0811BF86 after 0x0811BF7E).  Without the
 * qualifier agbcc drops the unused loads and shares the re-reads.  The rows
 * are the scanline payload func_080DABB4 returns. */
struct __attribute__((packed)) ScanlineBounds {
    volatile u16 right : 8;
    volatile u16 left : 8;
};

/* 20 steps of a sine-like wobble, -2..2 pixels. */
extern const s8 data_083A6BDC[20];
extern void func_080DAC40(void *task, u16 x, u16 y, u16 radius);
extern void *func_080DABB4(void *task);

/* A wobbling circular window: draws a circle of the given radius at the
 * screen centre into the window task's rows (func_080DAC40); unless
 * circle_only is set, it then moves each row's left and right edges by the
 * wobble table, each edge at its own phase, one table step per row, and
 * every second call steps the left phase back and the right phase forward.
 * 0811C018 calls it in three steps of its effect (0x0811C162, 0x0811C1E2,
 * 0x0811C270) with the phases and the timer kept in its own state. */
void func_0811BEC0(void *window, u8 radius, s8 *left_phase, s8 *right_phase,
                   u8 *timer, u8 circle_only)
{
    struct ScanlineBounds *bounds;
    s16 row;
    s16 i;
    s8 left;
    s8 right;
    s16 step;

    func_080DAC40(window, 120, 80, radius);
    if (circle_only)
        return;

    bounds = func_080DABB4(window);
    row = 80 - radius;
    left = *left_phase;
    right = *right_phase;
    for (i = 0; i < radius * 2; i++, row++) {
        if (row < 0)
            continue;
        if (row > 159)
            break;
        step = data_083A6BDC[left];
        if (bounds[row].left + step < 0)
            bounds[row].left = 0;
        else
            bounds[row].left += step;

        step = data_083A6BDC[right];
        if (bounds[row].right + step > 239)
            bounds[row].right = 240;
        else
            bounds[row].right += step;

        if (bounds[row].left > bounds[row].right)
            bounds[row].right = bounds[row].left;

        if (++left >= sizeof(data_083A6BDC))
            left = 0;
        if (++right >= sizeof(data_083A6BDC))
            right = 0;
    }

    if (--*timer == 0) {
        if (--*left_phase < 0)
            *left_phase = 19;
        if (++*right_phase >= sizeof(data_083A6BDC))
            *right_phase = 0;
        *timer = 2;
    }
}
