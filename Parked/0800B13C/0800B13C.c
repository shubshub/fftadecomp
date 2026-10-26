#include "ffta.h"

/* Complete [0x0800B13C, 0x0800B2A4): 360 bytes, 175 instructions. */
typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u8 unknown_04[6];
    u16 first;
    s16 last;
    u8 unknown_0e[10];
    u8 *data;
} Table0800B13C;

typedef struct __attribute__((packed)) {
    s16 value;
} Value0800B13C;

u16 func_0800B13C(Table0800B13C *table)
{
    s16 total = 0;
    u16 first;
    s16 last;
    u16 flags = table->flags;

    first = flags & 0x100 ? table->first : 0;
    last = table->last;
    if (flags & 8) {
        if (flags & 0x8000) {
            s16 i;
            u8 *data = table->data;
            for (i = first; i <= last; i++)
                total += (data + 3)[i * 6];
        } else {
            s16 i;
            u8 *data = table->data;
            for (i = first; i <= last &&
                 ((Value0800B13C *)(data + i * 8 + 4))->value != 999; i++)
                total += ((Value0800B13C *)(data + i * 8 + 4))->value;
        }
    } else {
        if (flags & 0x8000) {
            s16 i;
            u8 *data = table->data;
            for (i = first; i <= last; i++)
                total += (data + 3)[i * 2];
        } else {
            s16 i;
            u8 *data = table->data;
            for (i = first; i <= last &&
                 ((Value0800B13C *)(data + i * 4 + 4))->value != 999; i++)
                total += ((Value0800B13C *)(data + i * 4 + 4))->value;
        }
    }
    return total;
}
