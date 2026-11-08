#include "ffta.h"

/* Target: complete [0x08022A04, 0x08022A9C), 152 bytes. */
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 data_02003CB0[];
extern const u8 data_083AEEA4[];
extern const u8 data_083AF504[];
extern u8 data_06008A40[];
extern u8 data_06012500[];
extern BufferCopier data_0836D4BC[];
extern u16 data_03003A60[];
extern void func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *source, void *destination, u32 control);
extern const u8 *func_080CBA3C(u8 index);
extern const u8 *func_080CBA84(u32 index);

void func_08022A04(u8 flags)
{
    if (flags & 1) {
        u8 *buffer = data_02003CB0;

        func_0800543C(buffer, data_083AEEA4);
        func_08141868(buffer, data_06008A40, 0x2D0);
        func_0800543C(buffer, data_083AF504);
        func_08141868(buffer, data_06012500, 0x80);
    }
    if (flags & 2) {
        BufferCopier *copy = data_0836D4BC;
        u16 *palette = data_03003A60;

        copy[0](palette, func_080CBA3C(0), 0x200);
        palette = data_03003A60 - 0x100;
        copy[0](palette, func_080CBA84(0), 0x200);
    }
}
