#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813F794, 0x0813F898): 260 bytes, 87 instructions
// and 16 literal words.

typedef struct {
    u8 unknown_00[0x14];
    u16 *destination;
} Display0813F794;

typedef void (*BufferCopier0813F794)(void *, const void *, u32);

extern void *data_0200F3B0;
extern BufferCopier0813F794 data_0836D4BC[];
extern u16 data_03003860[][16];
extern Display0813F794 data_03000E60;
extern Display0813F794 data_03000990;
extern u8 data_06010000[];
extern const u16 data_089981A0[];
extern const u16 data_08998240[];
extern const u16 data_089987C0[];
extern const u16 data_089992D8[];
extern const u8 data_0896A1AC[];
extern const u8 data_0897A064[];

extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813F794 callback);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);
extern void func_0813FBB0(void *destination, u16 value, u16 bank);

void func_0813F794(void)
{
    BufferCopier0813F794 *copy;
    void *graphics;
    u32 size;

    g_control_flags_03000940.bldalpha_lo = 6;
    g_control_flags_03000940.bldalpha_hi = 15;
    g_control_flags_03000940.bg0hofs = -16;
    g_control_flags_03000940.bg0vofs = -40;

    copy = data_0836D4BC;
    func_08142250(data_03003860[0], data_089981A0, 0xA0, copy[0]);
    func_08142250(data_03003860[25], data_08998240, 0x80, copy[0]);
    func_08142250(data_03003860[16], data_089987C0, 0xE0, copy[0]);
    func_08142250(data_03003860[22], &data_089987C0[0x60], 0x20, copy[0]);
    data_03003860[0][0] = 0;

    graphics = data_0200F3B0;
    size = func_0800543C(graphics, data_0896A1AC);
    func_08141868(graphics, (void *)0x06000000, (size >> 2) & 0x1FFFFF);
    size = func_0800543C(graphics, data_0897A064);
    func_08141868(graphics, data_06010000, (size >> 2) & 0x1FFFFF);

    func_0813FB0C(data_089992D8, data_03000E60.destination, 0xF2, 0x16, 0);
    func_0813FBB0(data_03000990.destination, 0x260, 15);
}
