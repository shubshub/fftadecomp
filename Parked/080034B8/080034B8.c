#include "ffta.h"

typedef struct {
    u16 display;
    u16 background_0 : 16;
    u16 background_1 : 16;
    u16 background_2 : 16;
    u16 background_3 : 16;
} DisplayControl080034B8;

extern DisplayControl080034B8 g_control_flags_03000940;

void func_080034B8(u16 control, u8 layer)
{
    if (layer == 0)
        g_control_flags_03000940.background_0 = control;
    else if (layer == 1)
        g_control_flags_03000940.background_1 = control;
    else if (layer == 2)
        g_control_flags_03000940.background_2 = control;
    else
        g_control_flags_03000940.background_3 = control;
}
