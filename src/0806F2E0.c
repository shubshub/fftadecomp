#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 tiles[42];
} State0806F2E0;

extern const u16 data_083AF6CC[33];

/* Complete [0x0806F2E0, 0x0806F33C): 92 bytes, 43 instructions. */
void func_0806F2E0(State0806F2E0 *state)
{
    const u16 *table = data_083AF6CC;
    u16 index = 0;
    u16 row;

    for (row = 0; row < 3; row++) {
        u16 offset = row * 14;
        u16 column;

        for (column = 0; column < 14; column++) {
            if (column < 11) {
                state->tiles[column + offset] = table[index] + 0xc0;
                index++;
            } else {
                state->tiles[column + offset] = 0;
            }
        }
    }
}
