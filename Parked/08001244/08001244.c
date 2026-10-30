#include "ffta.h"

typedef unsigned long long SpriteRecord08001244;

extern u8 data_03002F58;
extern s32 data_03002F60[2];
extern SpriteRecord08001244 data_03002F68[2][32];
extern s32 data_03003168[2];
extern SpriteRecord08001244 data_03003170[2][16];

/* Complete [0x08001244, 0x080012BC): 120 bytes, 46 instructions. */
void func_08001244(void)
{
    s32 count;
    SpriteRecord08001244 *destination;

    destination = data_03002F68[data_03002F58];
    for (count = data_03002F60[data_03002F58]; count > 0; count--) {
        *destination = 0x00F800A8;
        destination++;
    }
    destination = data_03003170[data_03002F58];
    for (count = data_03003168[data_03002F58]; count > 0; count--) {
        *destination = 0x00F800A8;
        destination++;
    }
    data_03002F60[data_03002F58] = data_03003168[data_03002F58] = 0;
}
