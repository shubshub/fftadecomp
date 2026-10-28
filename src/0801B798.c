#include "ffta.h"

typedef struct Rectangle {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rectangle;

typedef struct DrawingState {
    u8 unknown_00[0x1E];
    u16 fill;
} DrawingState;

extern DrawingState g_state_02007F40;
extern u16 *func_0801AD1C(u8 layer);

/* 0801B798..0801B7F6: 94 bytes, 43 instructions. */
void func_0801B798(const Rectangle *rectangle, u8 layer)
{
    u16 fill = g_state_02007F40.fill;
    u16 *tiles = func_0801AD1C(layer);
    u8 x;
    u8 y;

    for (y = rectangle->top; y < rectangle->bottom && y < 64; y++) {
        for (x = rectangle->left; x < rectangle->right && x < 64; x++) {
            u16 *tile = tiles + (y * 64 + x);

            *tile = fill;
        }
    }
}
