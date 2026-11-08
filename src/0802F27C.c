#include "ffta.h"

/* Target: complete [0x0802F27C, 0x0802F35C), 224 bytes. */
typedef void (*BufferCopier)(void *, const void *, u32);
typedef void (*StateCallback)(void *, u32);
typedef struct TransferRecord TransferRecord;
typedef struct {
    u8 unknown_00[0x10];
    u8 *destination;
} GraphicsState;

extern BufferCopier data_0836D4BC[];
extern StateCallback g_callbacks_0836D4B8[];
extern u8 data_03003940[];
extern u8 data_02003CB0[];
extern const u8 data_083C4888[];
extern const u8 data_083C4C14[];
extern GraphicsState data_030008B0;
extern u8 data_06015800[];
extern u8 data_06016C00[];
extern u8 *data_0200F444;
extern const u8 *func_080CBABC(u32 index);
extern void func_0800543C(void *, const void *);
extern TransferRecord *func_0802DFCC(void);
extern void func_08000ADC(TransferRecord *, const void *, void *, u16);

void func_0802F27C(u8 alternate)
{
    BufferCopier *copy = data_0836D4BC;
    u8 *palette = data_03003940;
    u8 *buffer;

    copy[0](palette, func_080CBABC(0x14), 0x20);
    copy[0](palette + 0x40, func_080CBABC(0x16), 0x20);
    copy[0](palette + 0x20, func_080CBABC(0x1A), 0x20);
    buffer = data_02003CB0;
    func_0800543C(buffer, data_083C4888);
    func_08000ADC(func_0802DFCC(), buffer,
                 data_030008B0.destination + 0x1C00, 0x170);
    buffer = data_02003CB0 + 0x1C00;
    func_0800543C(buffer, data_083C4C14);
    func_08000ADC(func_0802DFCC(), buffer,
                 alternate ? data_06016C00 : data_06015800, 0x120);
    g_callbacks_0836D4B8[0](data_0200F444 + 0x7DC, 0x34);
}
