#include "ffta.h"

/* Complete [0x080632A8, 0x08063314): 108 bytes, 51 instructions. */
typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 mode;
    u8 unknown_4e[6];
    u32 flags;
    s32 selection;
} CommandState;

extern CommandState *data_0200F450;
extern void func_0802A2C0(s32, s32, s32, s32);

void func_080632A8(void)
{
    switch (data_0200F450->selection) {
    case 1:
        data_0200F450->mode = 4;
        break;
    case 2:
        data_0200F450->mode = 5;
        break;
    case 3:
        data_0200F450->mode = 6;
        break;
    }
    data_0200F450->flags &= ~2;
    func_0802A2C0(0, 0, 0, 0);
    data_0200F450->current = 0x18;
    data_0200F450->entries[data_0200F450->count++] = 0x18;
    data_0200F450->current = 0x31;
}
