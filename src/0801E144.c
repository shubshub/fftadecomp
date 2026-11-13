#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 unknown_02[0x22];
    s16 target_x;
    s16 target_y;
    s16 shift_x;
    s16 shift_y;
} ViewportState;

extern ViewportState g_state_02007F40;
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_0801B878(void);

// 0801E144..0801E1B8: 116 bytes, 51 instructions.
void func_0801E144(u16 x, u16 y, s16 inset_x, s16 inset_y)
{
    s32 span_x;
    s32 span_y;

    g_state_02007F40.target_x = x;
    g_state_02007F40.target_y = y;
    span_x = (s16)x - inset_x;
    g_state_02007F40.shift_x = span_x & ~7;
    span_y = (s16)y - inset_y;
    g_state_02007F40.shift_y = span_y & ~7;
    x -= g_state_02007F40.shift_x;
    y -= g_state_02007F40.shift_y;

    func_08003508(x, g_state_02007F40.first_layer);
    func_08003558(y, g_state_02007F40.first_layer);
    func_08003508(x, g_state_02007F40.second_layer);
    func_08003558(y, g_state_02007F40.second_layer);
    func_0801B878();
}
