#include "control_flags.h"

typedef void (*ClearBuffer)(void *destination, u32 size);
extern ClearBuffer const g_callbacks_0836D4B8[];

/* Initialize the LCD register shadow and the first columns of the two affine matrices. */
void func_080032B0(void)
{
    g_callbacks_0836D4B8[0](&g_control_flags_03000940, sizeof(g_control_flags_03000940));
    g_control_flags_03000940.display = 0x60;
    g_control_flags_03000940.bg2pa = g_control_flags_03000940.bg2pc = 0x100;
    g_control_flags_03000940.bg3pa = g_control_flags_03000940.bg3pc = 0x100;
}
