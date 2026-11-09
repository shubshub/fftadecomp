#include "control_flags.h"

typedef struct AffineParameters080032F8 {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineParameters080032F8;

/* Complete target [0x080032F8, 0x0800337C): 132 bytes, 60 instructions. */
void func_080032F8(const AffineParameters080032F8 *parameters, u32 layer)
{
    switch (layer) {
    case 2:
        g_control_flags_03000940.bg2pa = parameters->pa;
        g_control_flags_03000940.bg2pb = parameters->pb;
        g_control_flags_03000940.bg2pc = parameters->pc;
        g_control_flags_03000940.bg2pd = parameters->pd;
        g_control_flags_03000940.bg2x_l = parameters->x;
        g_control_flags_03000940.bg2x_h = parameters->x >> 16;
        g_control_flags_03000940.bg2y_l = parameters->y;
        g_control_flags_03000940.bg2y_h = parameters->y >> 16;
        break;
    case 3:
        g_control_flags_03000940.bg3pa = parameters->pa;
        g_control_flags_03000940.bg3pb = parameters->pb;
        g_control_flags_03000940.bg3pc = parameters->pc;
        g_control_flags_03000940.bg3pd = parameters->pd;
        g_control_flags_03000940.bg3x_l = parameters->x;
        g_control_flags_03000940.bg3x_h = parameters->x >> 16;
        g_control_flags_03000940.bg3y_l = parameters->y;
        g_control_flags_03000940.bg3y_h = parameters->y >> 16;
        break;
    }
}
