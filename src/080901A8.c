#include "ffta.h"

typedef struct {
    u8 *values;
    s16 center;
    s16 limit;
    s16 position;
} Animation080901A8;

/* An inlined copy of func_08092084 (src/08092084.c). */
static inline void inlined_08092084(u8 *base, s16 index, u8 lo, u8 hi) {
    u32 off = index * 2;
    base[off] = lo;
    base++;
    base[off] = hi;
}

/* Complete target: [0x080901A8, 0x08090214), 108 bytes.
 * Writes one byte pair per line into the table at animation->values, for the
 * lines center + offset and center - offset, offset counting down from limit
 * to zero. */
void func_080901A8(Animation080901A8 *animation)
{
    s32 offset;

    for (offset = animation->limit; offset >= 0; offset--) {
        u32 distance = animation->position - offset;
        u16 first;
        u16 second;
        s16 line;
        u8 lo;
        u8 hi;

        if (offset >= animation->position) {
            first = 0;
            second = 16;
        } else if (distance <= 8) {
            first = 16;
            second = 16 - distance;
        } else {
            first = 16;
            second = 9;
        }

        line = animation->center + offset;
        lo = first;
        hi = second;
        inlined_08092084(animation->values, line, lo, hi);
        line = animation->center - offset;
        inlined_08092084(animation->values, line, lo, hi);
    }
}
