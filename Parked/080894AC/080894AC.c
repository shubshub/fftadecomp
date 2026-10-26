#include "ffta.h"

/* Complete [0x080894AC, 0x0808953E): 146 bytes, 63 instructions. */
typedef struct {
    u8 unknown_00[0x18];
    u16 *first;
    u16 *second;
    u8 unknown_20[0x2c];
} TileBuffers;

extern TileBuffers data_030009E0[];

void func_080894AC(s32 index, s32 second, s32 count)
{
    u16 *dest;
    s32 i;
    if (second == 0)
        dest = data_030009E0[index].first;
    else
        dest = data_030009E0[index].second;
    for (i = 0; i < count << 10; i++) {
        s32 tile;
        u16 output;
        if (i & 2) {
            tile = (i & 1) ? 0xa43c : 0xa43d;
            output = (i & 0x20) ? tile | 0x800 : tile;
        } else {
            tile = (i & 1) ? 0xa03d : 0xa03c;
            output = (i & 0x20) ? tile | 0x800 : tile;
        }
        *dest++ = output;
    }
}
