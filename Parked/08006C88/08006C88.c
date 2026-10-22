#include "08006C88.h"

void func_08006C88(void *owner, u16 count, u8 **before, u8 **selected)
{
    u8 *base = owner;
    u8 *lower;
    u8 *upper;

    *selected = 0;
    *before = 0;
    lower = decode_block_offset(base, read_block_field(base + 2));
    if (lower != 0) {
        if (count <= read_block_field(lower + 6)) {
            do {
                upper = lower;
                lower = decode_block_offset(base, read_block_field(upper + 8));
            } while (lower != 0 &&
                     (count <= read_block_field(lower + 6) ||
                      count > read_block_field(upper + 6)));
        } else {
            upper = decode_block_offset(base, read_block_field(lower + 10));
            while (upper != 0 &&
                   (count <= read_block_field(lower + 6) ||
                    count > read_block_field(upper + 6))) {
                lower = upper;
                upper = decode_block_offset(base, read_block_field(lower + 10));
            }
        }
        *before = lower;
        *selected = upper;
    }
}
