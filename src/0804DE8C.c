#include "control_flags.h"

typedef struct {
    u8 unknown_00[12];
    u8 width;
    u8 height;
    u8 unknown_0e[6];
    u16 *destination;
} Display0804DE8C;

extern Display0804DE8C data_03000990;
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete body 0x0804DE8C..0x0804DF08: 124 bytes including literal pool. */
void func_0804DE8C(void)
{
    u16 zero;
    g_control_flags_03000940.display &= 0xF7FF;
    g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
    g_control_flags_03000940.bldalpha_lo = (g_control_flags_03000940.bldalpha_hi = 0);
    zero = 0;
    func_0814186C(&zero, data_03000990.destination,
        (data_03000990.width * data_03000990.height) | 0x01000000);
    g_control_flags_03000940.bldcnt_lo = 0x48;
    g_control_flags_03000940.bldcnt_hi = 0x33;
    g_control_flags_03000940.bldalpha_lo = 14;
    g_control_flags_03000940.bldalpha_hi = 9;
}
