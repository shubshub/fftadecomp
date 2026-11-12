#include "control_flags.h"

/* Complete [0x0803155C, 0x08031624): 200 bytes.
 * Target: 10b5094c2078ff2851d0fe2814d107490a1c4a321078462010704b310878132008700348034a16e0a427000340090003f027000346130000fd281dd10a490a1c4a321078422010704b310878012008700648a1225200111c0180054801800549087a088123e0000040090003f027000350000004a00e00030e490a1c4a321078422010704b310878012008700a49a1225200101c08800949094a101c0880094b1a7a207800022021084302431a8110bc01bc00474009000350000004f027000346130000a00e0003
 */
typedef struct {
    u8 unknown_00[8];
    u16 control;
} Display3155C;

extern u8 data_030027A4;
extern u16 data_030027F0;
extern u16 data_04000050;
extern Display3155C data_03000EA0;

void func_0803155C(void)
{
    u8 *mode = &data_030027A4;
    if (*mode == 0xff)
        return;
    if (*mode == 0xfe) {
        g_control_flags_03000940.bldcnt_lo = 0x46;
        g_control_flags_03000940.bldcnt_hi = 0x13;
        data_030027F0 = 0x1346;
        data_04000050 = 0x1346;
        data_03000EA0.control &= 0xff;
    } else if (*mode == 0xfd) {
        g_control_flags_03000940.bldcnt_lo = 0x42;
        g_control_flags_03000940.bldcnt_hi = 1;
        data_030027F0 = 0x142;
        data_04000050 = 0x142;
        data_03000EA0.control &= 0xff;
    } else {
        g_control_flags_03000940.bldcnt_lo = 0x42;
        g_control_flags_03000940.bldcnt_hi = 1;
        data_04000050 = 0x142;
        data_030027F0 = 0x1346;
        data_03000EA0.control = (data_03000EA0.control & 0xff) | ((*mode << 8) | 0x20);
    }
}
