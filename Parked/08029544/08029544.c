#include "ffta.h"

typedef struct State08029544 {
    u8 unknown_00[0x20];
    void *source;
    u8 unknown_24[4];
    void *window;
} State08029544;

extern State08029544 *data_0200F438;
extern u16 g_control_flags_03000940;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void *func_08005B00(void *, u32);
extern void func_0801174C(void *, u32, u8, void *, void *, u32, u32,
                          u32, u32, u32);
extern void func_0801339C(u32);
extern void func_08028B94(void);
extern void func_08028BA8(void);
extern void func_08013404(void (*)(void), void (*)(void));

/* Complete [0x08029544, 0x0802966C): 296 bytes, including jump table. */
void func_08029544(u8 kind)
{
    u8 wide = 0;
    u8 index = 0;
    void *window;
    u32 flags = g_control_flags_03000940 | 0xC00;

    g_control_flags_03000940 = flags;

    switch (kind) {
    case 1:
        wide = 1;
        index = 1;
        break;
    case 2:
        wide = 1;
        index = 0xd;
        break;
    case 3:
        index = 5;
        break;
    case 4:
        index = 6;
        break;
    case 5:
        index = 0x21;
        break;
    case 6:
    case 7:
    case 9:
    case 10:
        index = kind + 0x12;
        break;
    case 8:
        index = 0x23;
        break;
    case 11:
        index = 0xc;
        break;
    }

    window = func_08005B00(data_0200F438->source, 0xA04);
    data_0200F438->window = window;
    if (wide) {
        func_0801174C(window, 2, index, data_030008B0, data_03000990,
                      2, 2, 0x18, 0, 0x3a0);
        func_0801339C(2);
    } else {
        func_0801174C(window, 1, index, data_030008B0, data_03000990,
                      2, 2, 0x18, 4, 0x3a0);
        func_0801339C(2);
    }
    func_08013404(func_08028B94, func_08028BA8);
}
