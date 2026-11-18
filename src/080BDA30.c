#include "ffta.h"

typedef struct {
    u8 first;
    u8 second;
    u8 unknown_02[2];
} Record080BDA30;

extern void *func_081443FC(void *destination, const void *source, u32 size);

/* Complete target: [0x080BDA30, 0x080BDAFA), 202 bytes.
 * Target bytes: f0b557464e464546e0b486b0019002911206100e1b061b0e03930139049100258d424ada000600160590a8000199441820780599431a002b00da5b426278039801060816101a8a46002800da40421a1a0135a846029988452bdaa146a800019d4419261c40460f1a20780599431a002b00da5b42617855462816081a002800da40421d1aaa420fda68464946042286f09dfc4846311c042286f098fc301c6946042286f093fc2a1c04340436013f002fdad1454604988542b7db06b038bc9846a146aa46f0bc01bc0047
 */
void func_080BDA30(Record080BDA30 *records, s32 count, u8 first, u8 second)
{
    s32 i;
    s32 j;
    /* The ROM computes count - 1 once, ahead of i = 0 (0x080BDA4A), and reloads
     * it from sp+0x10 for the outer bottom test (0x080BDAE4). */
    s32 last = count - 1;

    for (i = 0; i < last; i++) {
        s32 dx, dy, score;

        dx = records[i].first - (s8)first;
        if (dx < 0)
            dx = -dx;
        dy = records[i].second - (s8)second;
        if (dy < 0)
            dy = -dy;
        score = dx - dy;

        for (j = i + 1; j < count; j++) {
            s32 ndx, ndy, nscore;

            ndx = records[j].first - (s8)first;
            if (ndx < 0)
                ndx = -ndx;
            ndy = records[j].second - (s8)second;
            if (ndy < 0)
                ndy = -ndy;
            nscore = ndx - ndy;

            if (score < nscore) {
                Record080BDA30 temp;

                func_081443FC(&temp, &records[i], sizeof(temp));
                func_081443FC(&records[i], &records[j], sizeof(temp));
                func_081443FC(&records[j], &temp, sizeof(temp));
                score = nscore;
            }
        }
    }
}
