#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 x;
    u16 y;
} State_02007F40;

extern State_02007F40 g_state_02007F40;

/* 0x0801E700: 16 bytes, including the referenced state literal. */
void func_0801E700(u16 *x, u16 *y)
{
    *x = g_state_02007F40.x;
    *y = g_state_02007F40.y;
}
