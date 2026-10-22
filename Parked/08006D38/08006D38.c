#include "08006D38.h"

void func_08006D38(void *owner)
{
    u8 *data = owner;
    u8 *node = decode_owner_link(data, data);
    u32 count;
    s32 remaining;
    u16 selected_offset;

    if (node == 0) {
        data[2] = 0;
        data[3] = 0;
        return;
    }

    count = data[4] | (data[5] << 8);
    remaining = count >> 1;
    while (--remaining > 0) {
        node = decode_owner_link(data, node + 0x0A);
    }

    selected_offset = node != 0 ? (node - data) >> 2 : 0;
    data[2] = selected_offset;
    data[3] = selected_offset >> 8;
}
