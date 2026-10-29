#include "ffta.h"

typedef struct AffineParameters080032F8 {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineParameters080032F8;

typedef struct DisplayShadow080032F8 {
    u16 unknown_00[13];
    u16 bg2pa;
    u16 bg2pb;
    u16 bg2pc;
    u16 bg2pd;
    u16 bg2x_low;
    u16 bg2x_high;
    u16 bg2y_low;
    u16 bg2y_high;
    u16 bg3pa;
    u16 bg3pb;
    u16 bg3pc;
    u16 bg3pd;
    u16 bg3x_low;
    u16 bg3x_high;
    u16 bg3y_low;
    u16 bg3y_high;
} DisplayShadow080032F8;

extern DisplayShadow080032F8 g_control_flags_03000940;

/* Complete target [0x080032F8, 0x0800337C): 132 bytes, 60 instructions. */
void func_080032F8(const AffineParameters080032F8 *parameters, u32 layer)
{
    switch (layer) {
    case 2:
        g_control_flags_03000940.bg2pa = parameters->pa;
        g_control_flags_03000940.bg2pb = parameters->pb;
        g_control_flags_03000940.bg2pc = parameters->pc;
        g_control_flags_03000940.bg2pd = parameters->pd;
        g_control_flags_03000940.bg2x_low = parameters->x;
        g_control_flags_03000940.bg2x_high = parameters->x >> 16;
        g_control_flags_03000940.bg2y_low = parameters->y;
        g_control_flags_03000940.bg2y_high = parameters->y >> 16;
        break;
    case 3:
        g_control_flags_03000940.bg3pa = parameters->pa;
        g_control_flags_03000940.bg3pb = parameters->pb;
        g_control_flags_03000940.bg3pc = parameters->pc;
        g_control_flags_03000940.bg3pd = parameters->pd;
        g_control_flags_03000940.bg3x_low = parameters->x;
        g_control_flags_03000940.bg3x_high = parameters->x >> 16;
        g_control_flags_03000940.bg3y_low = parameters->y;
        g_control_flags_03000940.bg3y_high = parameters->y >> 16;
        break;
    }
}
