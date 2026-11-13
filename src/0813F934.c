#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813F934, 0x0813F9F8): 196 bytes, 61 instructions
// and 15 literal words.

typedef struct {
    u8 unknown_00[0x14];
    u16 *destination;
} Display0813F934;

typedef void (*BufferCopier0813F934)(void *, const void *, u32);

extern void *data_0200F3B0;
extern BufferCopier0813F934 data_0836D4BC[];
extern u16 data_03003860[][16];
extern Display0813F934 data_03000E80;
extern u8 data_06002400[];
extern const u16 data_08998020[];
extern const u16 data_089988E0[];
extern const u16 data_08997F80[];
extern const u16 data_08998E60[];
extern const u8 data_0896E738[];

extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813F934 callback);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);

void func_0813F934(void)
{
    void *graphics;
    BufferCopier0813F934 *copy;
    u32 size;

    g_control_flags_03000940.bg1hofs = -88;
    g_control_flags_03000940.bg1vofs = -8;

    graphics = data_0200F3B0;
    copy = data_0836D4BC;
    func_08142250(data_03003860[28], data_08998020, 0x80, copy[0]);
    func_08142250(data_03003860[25], data_089988E0, 0x20, copy[0]);
    func_08142250(data_03003860[6], data_08997F80, 0xA0, copy[0]);
    data_03003860[0][0] = 0;

    size = func_0800543C(graphics, data_0896E738);
    func_08141868(graphics, data_06002400, (size >> 2) & 0x1FFFFF);
    func_0813FB0C(data_08998E60, data_03000E80.destination, 0xC0, 12, 0);
}
