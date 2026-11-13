#include "ffta.h"

/* 0x0801AE48: 16 bytes including the literal pool.
 * Target: 0248808d400b012108407047407f0002.
 * Return bit 13 of the halfword at state offset 0x2C.
 */
typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
} State0801AE48;

extern State0801AE48 g_state_02007F40;

u32 func_0801AE48(void)
{
    return (g_state_02007F40.flags >> 13) & 1;
}
