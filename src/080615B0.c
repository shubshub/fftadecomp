#include "ffta.h"

extern void func_08013404(u32 first, u32 second);
extern void func_08061188(void);
extern void func_0806119C(void);

/* Complete target: [0x080615B0, 0x080615C8), 24 bytes.
 * 00b503480349b1f725ff01bc00470000891106089d110608
 */
void func_080615B0(void)
{
    func_08013404((u32)func_08061188, (u32)func_0806119C);
}
