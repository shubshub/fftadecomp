#include "ffta.h"

/* Complete target [0x080231C0, 0x080231D8), 24 bytes, 8 instructions, one
 * padding halfword and one literal word:
 * 00b50448a32101705d214170e0f7e4f8fce70000d00e0003
 * Requests a soft reset: stores the reset code 0x5DA3 (as func_0800221C does
 * on A+B+Select+Start) and waits for VBlank forever; the function has no
 * return in the ROM (bl func_08003398 at 0x080231CC, b back at 0x080231D0). */

typedef struct {
    u8 code_0;
    u8 code_1;
    u8 unknown_02[3];
    u8 enabled;
} Control080231C0;

extern Control080231C0 data_03000ED0;

extern void func_08003398(void);

void func_080231C0(void)
{
    data_03000ED0.code_0 = 0xA3;
    data_03000ED0.code_1 = 0x5D;
    for (;;)
        func_08003398();
}
