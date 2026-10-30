#include "ffta.h"

extern u8 data_02003CB0[];
extern const u8 data_083AF710[];
extern void func_0800543C(void *destination, const void *source);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [08053648, 08053674), 44 bytes:
 * 10b5074c0749201cb1f7f4fe0649c0225200201ceef006f910bc01bc00470000b03c000210f73a0800580106
 */
void func_08053648(void)
{
    u8 *buffer = data_02003CB0;

    func_0800543C(buffer, data_083AF710);
    func_0814186C(buffer, (void *)0x06015800, 0x180);
}
