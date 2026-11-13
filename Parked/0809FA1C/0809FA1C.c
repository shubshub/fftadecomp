#include "ffta.h"

// Complete target [0x0809FA1C, 0x0809FBF2), 470 bytes.

typedef struct {
    u8 flags;
    u8 index;
    s16 value;
} CurvePoint;

static inline s32 FindRiseStep(s16 *window, s32 remaining, s32 level, s32 last)
{
    s32 j;
    s32 rise;

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

static inline s32 FindFallStep(s16 *window, s32 remaining, s16 level)
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

s32 func_0809FA1C(s16 *samples, s32 length, CurvePoint *out)
{
    s32 count;
    s32 level;
    s32 i;
    s32 j;
    s32 step;
    s32 best;
    s32 peak;
    s16 *window;
    s32 remaining;

    out[0].index = 0;
    level = samples[0];
    out[0].value = samples[0];
    out[0].flags = 1;
    count = 1;

    for (i = 1; i < length; i++) {
        window = &samples[i];
        remaining = length - i;
        best = -1;
        peak = -1;
        for (j = 0; j < remaining; j++) {
            if (window[j] >= peak) {
                best = j;
                peak = window[j];
            }
        }
        step = FindRiseStep(window, remaining, level, best);
        if (step < 0)
            break;
        i += step;
        out[count].index = i;
        out[count].value = samples[i];
        level = out[count].value;
        out[count].flags = 1;
        count++;
    }

    if (count > 0)
        out[count - 1].flags |= 2;

    for (; i < length; i++) {
        step = FindFallStep(&samples[i], length - i, level);
        if (step < 0)
            break;
        i += step;
        out[count].index = i;
        out[count].value = samples[i];
        out[count].flags = 2;
        count++;
    }

    return count;
}
