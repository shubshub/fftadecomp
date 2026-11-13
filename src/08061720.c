#include "ffta.h"

typedef void (*BufferInitializer08061720)(void *destination, u32 bytes);

extern void *data_0200F450;
extern u8 data_02003CB0[];
extern const u8 data_083B53A4[];
extern u8 data_06012700[];
extern BufferInitializer08061720 g_callbacks_0836D4B8[];
extern void func_080C95C0(u16 index, u32 value);
extern void *func_08022840(u32 size);
extern u8 *func_0800543C(void *destination, const void *source);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x08061720, 0x08061778): 88 bytes, 27 instructions.
 * 70b50d20002167f04bff0d4c0d4d0e4e301cc1f785f828600c490a68311ce0f085fd
 * 0b49201ca3f779fec020800024180849201c8022e0f089f870bc01bc0047b03c0002
 * 50f40002b4450000b8d43608a4533b0800270106 */
void func_08061720(void)
{
    u8 *buffer;
    void **slot;
    u32 size;

    func_080C95C0(13, 0);
    buffer = data_02003CB0;
    slot = &data_0200F450;
    size = 0x45B4;
    *slot = func_08022840(size);
    g_callbacks_0836D4B8[0](*slot, size);
    func_0800543C(buffer, data_083B53A4);
    func_0814186C(buffer + 0x300, data_06012700, 0x80);
}
