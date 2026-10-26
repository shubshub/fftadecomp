#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2FC2];
    u8 mode : 2;
    u8 unknown_2FC2 : 6;
} ResourceState;

extern ResourceState g_state_02000000;
extern const u8 data_0841B060[][32];
extern const u8 data_0841BB40[][32];
extern const u8 data_0841A560[][32];

const u8 *func_080CBB7C(u8 index)
{
    switch (g_state_02000000.mode) {
    case 2:
        return data_0841B060[index];
    case 1:
        return data_0841BB40[index];
    default:
        return data_0841A560[index];
    }
}
