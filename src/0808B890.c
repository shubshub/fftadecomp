#include "ffta.h"

struct Window0808B890 {
    u8 unknown_00[0x28];
    u8 width;
    u8 unknown_29[0x23];
};

extern struct Window0808B890 data_030009E0[];

/* 0x0808B890 .. 0x0808B8E4: 84 bytes, including literal pools. */
void func_0808B890(int index, u16 *destination, u16 count, u16 flags)
{
    int stride = data_030009E0[index].width;
    int column;

    for (column = 0; column < count; column++, destination++) {
        *destination = (*destination & 0x0FFF) | flags;
        destination[stride] = (destination[stride] & 0x0FFF) | flags;
    }
}
