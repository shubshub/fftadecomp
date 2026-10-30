#include "ffta.h"

extern void func_08013404(u32 first, u32 second);
extern void func_080611B0(void);
extern void func_080611D0(void);

/* Complete target: [0x080615C8, 0x080615E0), 24 bytes.
 * 00b503480349b1f719ff01bc00470000b1110608d1110608
 */
void func_080615C8(void)
{
    func_08013404((u32)func_080611B0, (u32)func_080611D0);
}
