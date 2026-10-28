#include "ffta.h"

/* 0x08003620 .. 0x0800363C: 28 bytes. */
extern u16 g_control_flags_03000940;

void func_08003620(u8 value)
{
    g_control_flags_03000940 = (g_control_flags_03000940 & 0xFFF8) | value;
}
