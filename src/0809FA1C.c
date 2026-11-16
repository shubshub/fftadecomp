#include "ffta.h"

/* 0x0809FA1C .. 0x0809FBF2: 470 bytes. */
typedef struct {
    u8 flags;
    s8 x;
    s16 y;
} PathPoint;

/* Index of the last highest sample in window[0 .. remaining). */
static inline s32 FindPeak(s16 *window, s32 remaining)
{
    s32 j;
    s32 best;
    s32 peak;

    best = -1;
    peak = -1;
    for (j = 0; j < remaining; j++, window++) {
        if (*window >= peak) {
            best = j;
            peak = *window;
        }
    }
    return best;
}

/* Offset of the first sample that rises above the line from level to the
   peak, or of the peak itself; -1 when nothing ahead is higher than level.
   level is s16 as in FindFallStep, whose argument the ROM narrows with
   lsls/asrs #16 (0x0809FB3A-0x0809FB3E, 0x0809FB76-0x0809FB78).  Here the
   ROM holds the parameter as its own copy of the caller's level, in ip from
   0x0809FA5E and in r6 from 0x0809FAAE. */
static inline s32 FindRiseStep(s16 *window, s16 level, s32 remaining)
{
    s32 j;
    s32 rise;
    s32 last;

    last = FindPeak(window, remaining);
    if (level >= window[last])
        return -1;
    rise = window[last] - level;
    last++;
    for (j = 0; j < remaining; j++, window++) {
        if (*window > level && rise * (j + 1) / last + level < *window)
            return j;
    }
    return last - 1;
}

/* Offset of the first sample at or below level that lies above the line from
   level to the last sample, or of the last sample; -1 when that is higher. */
static inline s32 FindFallStep(s16 *window, s16 level, s32 remaining)
{
    s32 j;
    s32 fall;
    s32 last;

    last = remaining - 1;
    if (level < window[last])
        return -1;
    fall = window[last] - level;
    last++;
    for (j = 0; j < remaining; j++, window++) {
        if (*window <= level && fall * (j + 1) / last + level < *window)
            return j;
    }
    return last - 1;
}

s32 func_0809FA1C(s16 *samples, s32 length, PathPoint *path)
{
    s32 count;
    s32 level;
    s32 i;
    s32 step;

    /* count starts at 0: the ROM sets that 0 at 0x0809FA2E, ahead of the
       samples[0] load, and stores it as x at 0x0809FA3A. */
    count = 0;
    level = samples[0];
    path[count].x = 0;
    path[count].y = samples[0];
    path[count].flags = 1;
    count++;

    for (i = 1; i < length; i++) {
        step = FindRiseStep(&samples[i], level, length - i);
        if (step < 0)
            break;
        i += step;
        path[count].x = i;
        path[count].y = samples[i];
        level = path[count].y;
        path[count].flags = 1;
        count++;
    }

    if (count > 0)
        path[count - 1].flags |= 2;

    for (; i < length; i++) {
        step = FindFallStep(&samples[i], level, length - i);
        if (step < 0)
            break;
        i += step;
        path[count].x = i;
        path[count].y = samples[i];
        path[count].flags = 2;
        count++;
    }

    return count;
}
