#include "ffta.h"

extern const u8 data_088EB4A4[];
extern void func_080D45D0(const void *data, u32 first, u32 second,
                         u32 third, u32 mode);

/* Complete [0x080D8D78, 0x080D8D98): 32 bytes, 12 instructions. */
void func_080D8D78(void)
{
    func_080D45D0(data_088EB4A4, 0, 0, 0, 6);
}
