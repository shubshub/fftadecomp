#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 sort_key;
} Item;

/* Complete target: [0x08061C24, 0x08061C30), 12 bytes, 6 instructions. */
s32 func_08061C24(const void *left, const void *right)
{
    const Item *a = *(const Item *const *)left;
    const Item *b = *(const Item *const *)right;

    return a->sort_key - b->sort_key;
}
