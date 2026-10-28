#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 value : 16;
} ControlChannel;

typedef struct {
    u8 unknown_00[8];
    ControlChannel channels[4];
} ControlState;

extern ControlState g_control_flags_03000940;

/* 08003508..08003558: 80 bytes. */
void func_08003508(u16 value, u8 channel)
{
    if (channel == 0)
        g_control_flags_03000940.channels[0].value = value;
    else if (channel == 1)
        g_control_flags_03000940.channels[1].value = value;
    else if (channel == 2)
        g_control_flags_03000940.channels[2].value = value;
    else
        g_control_flags_03000940.channels[3].value = value;
}
