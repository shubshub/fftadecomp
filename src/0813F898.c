#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813F898, 0x0813F934): 156 bytes, 48 instructions
// and 12 literal words.

typedef struct {
    u8 unknown_00[0x14];
    u16 *destination;
} Display0813F898;

typedef void (*BufferCopier0813F898)(void *, const void *, u32);

extern void *data_0200F3B0;
extern BufferCopier0813F898 data_0836D4BC[];
extern u16 data_03003860[][16];
extern Display0813F898 data_03000E60;
extern const u16 data_08998120[];
extern const u16 data_089980A0[];
extern const u8 data_0896D5C0[];
extern const u16 data_08998FE0[];

extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813F898 callback);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);

void func_0813F898(void)
{
    BufferCopier0813F898 *copy;
    void *graphics;
    u32 size;

    g_control_flags_03000940.bg0hofs = -32;
    g_control_flags_03000940.bg0vofs = -40;

    copy = data_0836D4BC;
    func_08142250(data_03003860[25], data_08998120, 0x20, copy[0]);
    func_08142250(data_03003860[0], data_089980A0, 0x80, copy[0]);
    data_03003860[0][0] = 0;

    graphics = data_0200F3B0;
    size = func_0800543C(graphics, data_0896D5C0);
    func_08141868(graphics, (void *)0x06000000, (size >> 2) & 0x1FFFFF);
    func_0813FB0C(data_08998FE0, data_03000E60.destination, 0xAA, 10, 0);
}
