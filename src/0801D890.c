#include "ffta.h"

/* 0x0801D890..0x0801D8B8: 40 bytes. */
typedef struct {
    u8 unknown_00[0x228];
    u8 enabled;
} OutputState;

extern OutputState g_state_02007F40;

void func_0801D890(u8 *first, u8 *second)
{
    if (g_state_02007F40.enabled == 0) {
        *first = 0xFF;
        *second = 0xFF;
    } else {
        *first = 1;
        *second = 0;
    }
}
