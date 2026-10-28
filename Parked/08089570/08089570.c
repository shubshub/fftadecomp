#include "ffta.h"

typedef struct {
    u16 display_flags;
    u16 background_control[4];
} DisplayControls08089570;

extern DisplayControls08089570 g_control_flags_03000940;

/* 0x08089570 .. 0x080895A0: 48 bytes, including literal pools. */
void func_08089570(void)
{
    g_control_flags_03000940.background_control[0] = 0xAE0B;
    g_control_flags_03000940.background_control[1] = 0xAC0A;
    g_control_flags_03000940.background_control[2] = 0x2B0A;
    g_control_flags_03000940.background_control[3] = 0x2A08;
}
