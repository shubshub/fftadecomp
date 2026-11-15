#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u8 *buffer;
} ResourceContext08074848;

extern ResourceContext08074848 *data_03002818;
extern u8 *data_03002740[];

/* Complete target [0x08074848, 0x080748A8): 96 bytes, 35 instructions. */
void func_08074848(void)
{
    s32 i;
    u8 *buffer;

    for (i = 2; i < 14; i++)
        data_03002740[i] = 0;
    /* Fixed GBA VRAM tile-storage areas for the two resource planes. */
    data_03002740[0] = (u8 *)0x06007000;
    data_03002740[1] = (u8 *)0x06005800;
    data_03002818->large_first = (u16 *)0x06007000;
    data_03002818->large_second = (u16 *)0x06006000;
    data_03002818->small_first = (u16 *)0x06005800;
    data_03002818->small_second = (u16 *)0x06005000;
    buffer = data_03002818->buffer;
    data_03002740[2] = buffer;
    data_03002740[3] = buffer + 0x1f8;
    data_03002740[4] = buffer + 0x318;
}
