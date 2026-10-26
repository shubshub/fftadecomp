#include "ffta.h"

typedef struct {
    u16 control;
    u16 values[0];
} __attribute__((packed)) PackedSequence;

static inline u16 read_packed(const u16 **cursor, u16 *index)
{
    const PackedSequence *sequence = (const PackedSequence *)*cursor;
    u16 control = sequence->control;
    u16 count = control & 0x3FFF;
    u8 mode = 0;
    u16 value;

    if (control & 0x8000) {
        mode = 1;
        value = sequence->values[0] + *index;
    } else if (control & 0x4000) {
        mode = 2;
        value = sequence->values[0];
    } else {
        value = sequence->values[*index];
    }

    (*index)++;
    if (*index == count) {
        if (mode)
            *cursor = sequence->values + 1;
        else
            *cursor = sequence->values + count;
        *index = 0;
    }
    return value;
}

u16 func_080D663C(const u16 **cursor, u16 *index, u8 compressed)
{
    u16 value;

    if (compressed) {
        value = read_packed(cursor, index);
    } else {
        const u16 *values = *cursor;
        value = values[*index];
        (*index)++;
    }
    return value;
}
