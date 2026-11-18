#include "ffta.h"

extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target: [0x080DAE70, 0x080DAE7C), 12 bytes.
 * Target bytes: 00b5a02266f0fafc01bc0047
 * Copy 160 halfwords through the GBA BIOS CpuSet wrapper. */
void func_080DAE70(const void *source, void *destination)
{
    func_0814186C(source, destination, 0xA0);
}
