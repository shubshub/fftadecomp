#include "ffta.h"

typedef struct {
    u8 id;
    u8 unknown_01;
    u16 first;
    u16 last;
    u8 unknown_06[2];
} Range08019A50;

extern Range08019A50 data_0836DA1C[11];

/* Complete [0x08019A50, 0x08019A8A): 58 bytes, 26 instructions. */
void func_08019A50(u16 value, u8 *id, u16 *offset)
{
    Range08019A50 *range = data_0836DA1C;
    s32 index;

    for (index = 0; index < 11; index++, range++) {
        if (range->first <= value && value <= range->last) {
            *id = range->id;
            *offset = value - range->first;
            return;
        }
    }
}
