#include "ffta.h"

/* 0x08003558..0x080035A8: 80 bytes / 30 instructions. */
struct ControlWord08003558 {
    u32 value : 16;
    u32 unknown_02 : 16;
};

struct Control08003558 {
    u8 unknown_00[0x0C];
    struct ControlWord08003558 first;
    struct ControlWord08003558 second;
    struct ControlWord08003558 third;
    struct ControlWord08003558 fourth;
};

extern struct Control08003558 g_control_flags_03000940;

void func_08003558(u16 value, u8 selector)
{
    if (selector == 0)
        g_control_flags_03000940.first.value = value;
    else if (selector == 1)
        g_control_flags_03000940.second.value = value;
    else if (selector == 2)
        g_control_flags_03000940.third.value = value;
    else
        g_control_flags_03000940.fourth.value = value;
}
