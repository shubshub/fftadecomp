#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit080C4A40;

typedef struct {
    Unit080C4A40 *unit;
} Record080C4A40;

typedef struct {
    Record080C4A40 *current;
    u8 unknown_04[4];
    Record080C4A40 **negative_records;
    Record080C4A40 **positive_records;
    u16 negative_count;
    u16 positive_count;
} Context080C4A40;

extern int abs(int value);
extern u8 func_080C8280(const void *object);

/* Complete target: [0x080C4A40, 0x080C4B20), 224 bytes. */
s32 func_080C4A40(Context080C4A40 *context, u8 x, u8 y)
{
    s16 score = 0;
    s32 i;

    for (i = 0; i < context->positive_count; i++) {
        Record080C4A40 *record = context->positive_records[i];
        s32 cost;

        if (record == context->current)
            continue;
        if (func_080C8280(record->unit))
            continue;
        cost = 32 + abs(record->unit->y - y);
        cost -= abs(record->unit->x - x);
        score += cost;
    }
    for (i = 0; i < context->negative_count; i++) {
        Record080C4A40 *record = context->negative_records[i];
        s32 cost;

        if (record == context->current)
            continue;
        if (func_080C8280(record->unit))
            continue;
        cost = 32 + abs(record->unit->y - y);
        cost -= abs(record->unit->x - x);
        score -= cost;
    }
    return score;
}
