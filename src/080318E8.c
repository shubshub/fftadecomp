#include "ffta.h"

/* Complete [0x080318E8, 0x08031978): 144 bytes, 58 instructions. */

typedef struct {
    u8 unknown_00[0x88];
    u8 *field_88;
    u8 *field_8C;
    u8 *field_90;
    u8 *field_94;
    u8 *buffer;
} State080318E8;

extern u8 *data_03002740[];
extern State080318E8 *g_state_03002810;
extern u8 data_02003CB0[];

void func_080318E8(void)
{
    s32 i;

    for (i = 2; i < 14; i++)
        data_03002740[i] = 0;
    data_03002740[0] = (u8 *)0x06005000;
    data_03002740[1] = (u8 *)0x06007000;
    g_state_03002810->field_8C = (u8 *)0x06005000;
    g_state_03002810->field_88 = (u8 *)0x06006000;
    g_state_03002810->field_94 = (u8 *)0x06007000;
    g_state_03002810->field_90 = (u8 *)0x06007800;
    data_03002740[2] = g_state_03002810->buffer;
    data_03002740[3] = g_state_03002810->buffer + 0x78;
    data_03002740[4] = g_state_03002810->buffer + 0xd0;
    data_03002740[5] = g_state_03002810->buffer + 0x820;
    data_03002740[6] = g_state_03002810->buffer + 0xcf0;
    data_03002740[7] = g_state_03002810->buffer + 0x12a0;
    data_03002740[12] = data_02003CB0;
}
