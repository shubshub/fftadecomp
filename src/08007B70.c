/* 0x08007B70 - 274 bytes: [0x08007B70, 0x08007C82), 129 instructions
 * Target: f0b557464e464546e0b489b000900c1c581c00998b600c604a60012b01dc00206fe0013b0393171c10370297c00082468018814608214942494488460830049057463819011c0839089108300590171c18370697161c0836201c18300790251c0835012101911022101902684368191c101c3bf14dfa079f0ccf07973bf162fa28606960029802684368191c101c3bf13ffa069f0ccf06973bf154fa306071605146081902684368191c101c3bf130fa089f3a687b683bf145fa059a03c205924f463a687b68191c101c3bf121fa47463a687b683bf136fa049a03c2049208277f42b844089808380890083e083d0199013901910029b6da0020009a1073039ff80009b038bc9846a146aa46f0bc02bc0847
 */
#include "ffta.h"

/* BoundaryState of src/08007C84.c (and the 16-byte prefix src/0809AEF8.c
 * declares); the caller at 0x0809AEF8 passes the same member (+0x148). */
typedef struct BoundaryState {
    double *horizontal;
    double *vertical;
    s32 count;
    u8 phase;
    s32 index;
    s32 start;
    s32 end;
    double weights[4][8];
} BoundaryState;

/* Reflects two phantom samples about each end of the sample run
 * [start, end] that func_08007C84 then interpolates (its phase 0 sets the
 * same start = 2 and end = count + 1), and returns (end - start) * 8, the
 * index of the last point it writes, 8 per segment. */
s32 func_08007B70(BoundaryState *state, double *horizontal, double *vertical, s32 count)
{
    s32 end = count + 1;
    /* A named start, not a literal: the ROM forms horizontal[start]'s
     * address in the loop from a register holding 16 (movs r2, #0x10;
     * adds r0, r2, r4 at 0x08007BD6).  A literal 2, or a const local,
     * folds into #0x10 load offsets instead (228 bytes differ). */
    s32 start = 2;
    s32 i;

    state->count = count;
    state->horizontal = horizontal;
    state->vertical = vertical;
    if (count < 2)
        return 0;
    for (i = 1; i <= 2; i++) {
        horizontal[start - i] = 2.0 * horizontal[start] - horizontal[start + i];
        vertical[start - i] = 2.0 * vertical[start] - vertical[start + i];
        horizontal[end + i] = 2.0 * horizontal[end] - horizontal[end - i];
        vertical[end + i] = 2.0 * vertical[end] - vertical[end - i];
    }
    state->phase = 0;
    return (end - start) * 8;
}
