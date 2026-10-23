#include "ffta.h"

u8 *func_080070C8(u8 *storage, u32 byte_count);
void func_0800C2C0(u8 *owner);
void func_0800C6CC(u8 *owner);
void func_0801159C(u8 *owner);

void func_0800A5F8(u8 *storage, u32 byte_count)
{
    *(u8 **)0x02008FF4 = func_080070C8(storage, byte_count);
    func_0800C2C0(*(u8 **)0x02008FF4);
    func_0800C6CC(*(u8 **)0x02008FF4);
    func_0801159C(*(u8 **)0x02008FF4);
}
