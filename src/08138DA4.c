#include "ffta.h"

/* Complete [0x08138DA4, 0x08138E80): 220 bytes, 85 instructions. */
typedef struct {
    u8 unknown_000[0x105];
    u8 first;
    u8 second;
} State08138DA4;

extern u32 func_0808B8E4(u32, u32, u32, u32);
extern void func_0808B7C0(u32, u32, u32, u32, u32);

void func_08138DA4(State08138DA4 *state, u32 mode)
{
    u32 id = 4;
    u32 tile;

    if (mode == 1) {
        tile = 0x209;
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, 3), tile, 11, 0xb000);
    } else if (mode == 2) {
        tile = 0x269;
        func_0808B7C0(5, func_0808B8E4(5, 1, 1, 3), tile, 11, 0xb000);
    } else {
        if (state->second) {
            tile = 0x269;
            id = 5;
        } else
            tile = 0x209;
        func_0808B7C0(id, func_0808B8E4(id, 1, 1, 3), tile, 11, 0xc000);
        if (state->first) {
            tile = 0x269;
            id = 5;
        } else {
            tile = 0x209;
            id = 4;
        }
        func_0808B7C0(id, func_0808B8E4(id, 1, 1, 3), tile, 11, 0xb000);
    }
}
