#include "ffta.h"

// Complete target [0x0813F604, 0x0813F794): 400 bytes, 156 instructions
// and 24 literal words.

typedef struct {
    u8 unknown_0000[0x1120];
    u8 tiles_1120[0x6EE0];
    u32 packed_size;
    u8 unknown_8004[0xBD4];
    u16 palettes[24][16];
} Graphics0813F604;

typedef struct {
    u8 unknown_00[0x14];
    u16 *destination;
} Display0813F604;

typedef void (*BufferCopier0813F604)(void *, const void *, u32);

extern Graphics0813F604 *data_0200F3B0;
extern BufferCopier0813F604 data_0836D4BC[];
extern u16 data_03003B20[][16];
extern Display0813F604 data_03000E60;
extern Display0813F604 data_030008B0;
extern Display0813F604 data_03000990;
extern u8 data_06008000[];
extern u8 data_06010000[];
extern u8 data_06016440[];
extern const u16 data_089983E0[];
extern const u16 data_089987C0[];
extern const u16 data_089987A0[];
extern const u16 data_089994BC[];
extern const u16 data_08999A3C[];
extern const u8 data_089710B4[];
extern const u8 data_08979748[];
extern const u8 data_0897A064[];
extern const u8 data_08974834[];

extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813F604 callback);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *, void *, u32);
extern void func_0814186C(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);
extern void func_0813FBB0(void *destination, u16 value, u16 bank);

void func_0813F604(void)
{
    Graphics0813F604 *graphics = data_0200F3B0;
    /* One local for the copier passed to all seven func_08142250 calls, as
     * in src/0813BB04.c and src/08135D6C.c.  The ROM loads its address
     * straight after graphics. */
    BufferCopier0813F604 *copy = data_0836D4BC;
    u32 size;

    func_08142250(graphics->palettes[0], data_089983E0, 0x1E0,
                  copy[0]);
    func_08142250(data_0200F3B0->palettes[16], data_089987C0, 0xE0,
                  copy[0]);
    func_08142250(data_03003B20[0], &data_089987C0[0x60], 0x20,
                  copy[0]);
    func_08142250(data_0200F3B0->palettes[22], &data_089987C0[0x60], 0x20,
                  copy[0]);
    func_08142250(data_0200F3B0->palettes[23], &data_089987C0[0x60], 0x20,
                  copy[0]);

    size = func_0800543C(graphics, data_089710B4);
    func_08141868(graphics, data_06008000, (size >> 2) & 0x1FFFFF);
    func_0813FB0C(data_089994BC, data_03000E60.destination, 320, 10, 0);

    func_0800543C(graphics, data_08979748);
    func_08141868(graphics, data_06016440, 0x448);
    func_0814186C(graphics->tiles_1120, (void *)0x06000000, 0x540);
    func_0813FB0C(data_08999A3C, data_030008B0.destination, 600, 30, 0);

    func_08142250(data_0200F3B0->palettes[15], data_089987A0, 0x1E,
                  copy[0]);
    size = func_0800543C(graphics, data_0897A064);
    func_08141868(graphics, data_06010000, (size >> 2) & 0x1FFFFF);
    func_08142250(data_03003B20[9], data_089987A0, 0x20, copy[0]);

    func_0813FBB0(data_03000990.destination, 0x260, 15);
    graphics = data_0200F3B0;   /* the ROM reloads it into graphics' register */
    data_0200F3B0->packed_size = func_0800543C(graphics, data_08974834);
}
