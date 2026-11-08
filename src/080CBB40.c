#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
} Selection080CBB40;

extern Selection080CBB40 g_state_02000000;
extern const u8 data_0841A760[];
extern const u8 data_0841BD40[];
extern const u8 data_0841B260[];

const u8 *func_080CBB40(void)
{
    switch (g_state_02000000.mode) {
    case 2:
        return data_0841A760;
    case 1:
        return data_0841BD40;
    default:
        return data_0841B260;
    }
}
