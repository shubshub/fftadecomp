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

struct __attribute__((packed)) ScanlineBounds {
    u16 right : 8;
    u16 left : 8;
};

extern const s8 data_083A6BDC[20];
extern void func_080DAC40(void *, s16, s16, u16);
extern struct ScanlineBounds *func_080DABB4(void *);

void func_0811BEC0(void *window, u8 radius, s8 *left_phase, s8 *right_phase,
                   u8 *timer, u8 paused)
{
    struct ScanlineBounds *bounds;
    s16 row;
    s16 i;
    s8 left;
    s8 right;
    s16 step;

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
