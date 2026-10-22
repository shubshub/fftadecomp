#include "ffta.h"

void func_08006D38(void *owner);

void func_08006DA0(u8 *owner, u8 *block)
{
    u16 previous_offset = block[8] | (block[9] << 8);
    u8 *previous = previous_offset ? owner + 4 * previous_offset : 0;
    u16 next_offset = block[10] | (block[11] << 8);
    u8 *next = next_offset ? owner + 4 * next_offset : 0;
    u16 count;

    if (previous) {
        u16 offset = block[10] | (block[11] << 8);

        previous[10] = offset;
        previous[11] = offset >> 8;
    } else {
        u16 offset = block[10] | (block[11] << 8);

        owner[0] = offset;
        owner[1] = offset >> 8;
    }
    if (next) {
        u16 offset = block[8] | (block[9] << 8);

        next[8] = offset;
        next[9] = offset >> 8;
    }
    block[10] = 0;
    block[11] = 0;
    block[8] = 0;
    block[9] = 0;
    count = owner[4] | (owner[5] << 8);
    count--;
    owner[4] = count;
    owner[5] = count >> 8;
    func_08006D38(owner);
}
