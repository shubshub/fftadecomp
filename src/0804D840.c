#include "ffta.h"

/* Target: complete [0x0804D840, 0x0804D86C), 44 bytes. */
extern u32 func_0804E9D0(void);
extern u8 func_08038694(u16 value);
extern u8 *func_0804CA58(u32 bytes);
extern void func_080CB27C(u8 *buffer);
extern void func_0804CA6C(void *buffer);
extern void func_0804E358(u8 mode);

void func_0804D840(void)
{
    u8 *buffer;

    func_08038694((u16)func_0804E9D0());
    buffer = func_0804CA58(0x62);
    func_080CB27C(buffer);
    func_0804CA6C(buffer);
    func_0804E358(5);
}
