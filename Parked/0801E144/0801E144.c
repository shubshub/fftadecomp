#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 unknown_02[0x22];
    s16 focus_x;
    s16 focus_y;
    s16 origin_x;
    s16 origin_y;
} ViewportState;

extern ViewportState g_state_02007F40;
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_0801B878(void);

/* Complete [0x0801E144, 0x0801E1B8): 116 bytes, 51 instructions. */
void func_0801E144(u16 x, u16 y, s16 inset_x, s16 inset_y)
{
    s32 origin_x;
    s32 origin_y;

    g_state_02007F40.focus_x = x;
    g_state_02007F40.focus_y = y;
    origin_x = ((s16)x - inset_x) & ~7;
    g_state_02007F40.origin_x = origin_x;
    origin_y = ((s16)y - inset_y) & ~7;
    g_state_02007F40.origin_y = origin_y;
    x -= origin_x;
    y -= origin_y;
    func_08003508((s16)x, g_state_02007F40.first_layer);
    func_08003558((s16)y, g_state_02007F40.first_layer);
    func_08003508((s16)x, g_state_02007F40.second_layer);
    func_08003558((s16)y, g_state_02007F40.second_layer);
    func_0801B878();
}
