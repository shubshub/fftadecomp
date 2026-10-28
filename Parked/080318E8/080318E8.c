#include "ffta.h"

typedef struct {
    u8 *first;
    u8 *second;
    u8 *slots[12];
} Resources080318E8;

typedef struct {
    u8 unknown_00[0x88];
    u8 *field_88;
    u8 *field_8c;
    u8 *field_90;
    u8 *field_94;
    u8 *buffer;
} State080318E8;

extern Resources080318E8 data_03002740;
extern State080318E8 *g_state_03002810;
extern u8 data_02003CB0[];

/* Complete [0x080318E8, 0x08031978): 144 bytes, 58 instructions. */
void func_080318E8(void)
{
    Resources080318E8 *resources = &data_03002740;
    u8 **slot;
    s32 i;

    for (i = 0, slot = resources->slots; i < 12; i++)
        *slot++ = 0;
    resources->first = (u8 *)0x06005000;
    resources->second = (u8 *)0x06007000;
    g_state_03002810->field_8c = (u8 *)0x06005000;
    g_state_03002810->field_88 = (u8 *)0x06006000;
    g_state_03002810->field_94 = (u8 *)0x06007000;
    g_state_03002810->field_90 = (u8 *)0x06007800;
    resources->slots[0] = g_state_03002810->buffer;
    resources->slots[1] = g_state_03002810->buffer + 0x78;
    resources->slots[2] = g_state_03002810->buffer + 0xd0;
    resources->slots[3] = g_state_03002810->buffer + 0x820;
    resources->slots[4] = g_state_03002810->buffer + 0xcf0;
    resources->slots[5] = g_state_03002810->buffer + 0x12a0;
    resources->slots[10] = data_02003CB0;
}
