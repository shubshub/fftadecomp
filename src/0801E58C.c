#include "ffta.h"

typedef struct LayerState {
    u8 first_layer;
    u8 second_layer;
    u8 unknown_02[0x22];
    u16 x;
    u16 y;
    u16 offset_x;
    u16 offset_y;
} LayerState;

extern LayerState g_state_02007F40;
extern void func_08003508(s16 coordinate, u8 layer);
extern void func_08003558(s16 coordinate, u8 layer);
extern void func_0801B878(void);

/* 0801E58C..0801E5E0: 84 bytes, 34 instructions. */
void func_0801E58C(s16 x, s16 y)
{
    u16 relative_x;
    u16 relative_y;

    g_state_02007F40.offset_x = x * 8;
    g_state_02007F40.offset_y = y * 8;
    relative_x = g_state_02007F40.x - g_state_02007F40.offset_x;
    relative_y = g_state_02007F40.y - g_state_02007F40.offset_y;
    func_08003508(relative_x, g_state_02007F40.first_layer);
    func_08003558(relative_y, g_state_02007F40.first_layer);
    func_08003508(relative_x, g_state_02007F40.second_layer);
    func_08003558(relative_y, g_state_02007F40.second_layer);
    func_0801B878();
}
