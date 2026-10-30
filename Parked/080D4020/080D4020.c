#include "ffta.h"

typedef struct {
    u8 unknown_00[0x4A];
    u32 field_4A : 8;
    u32 field_4B : 8;
} ControlState080D4020;

extern ControlState080D4020 g_control_flags_03000940;

/* 0x080D4020..0x080D4038:
 * 04 48 02 1C 4A 32 11 78 00 21 11 70 4B 30 02 78
 * 01 70 70 47 40 09 00 03. */
void func_080D4020(void)
{
    g_control_flags_03000940.field_4A = 0;
    g_control_flags_03000940.field_4B = 0;
}
