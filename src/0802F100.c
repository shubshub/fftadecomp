#include "ffta.h"

typedef struct Root0802F100 {
    u8 unknown_00[0x1F3C];
    u8 selections[0][2];
} Root0802F100;

typedef struct TextEntry0802F100 {
    u8 unknown_00;
    u8 text;
    u8 unknown_02[14];
} TextEntry0802F100;

typedef struct TextPanel0802F100 {
    u8 unknown_00[7];
    u8 step;
    u8 height;
    u8 unknown_09[3];
    s16 selected;
    u8 unknown_0E[2];
    u8 text_state[0];
} TextPanel0802F100;

typedef struct Graphics0802F100 {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics0802F100;

typedef struct Transfer0802F100 Transfer0802F100;

extern Root0802F100 g_state_02000000;
extern TextPanel0802F100 *data_0200F444;
extern const TextEntry0802F100 g_table_08528F34[];
extern u8 data_02004270[];
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern const u8 *const g_table_085567F0[];
extern Graphics0802F100 data_030008B0;
extern const u8 *func_080CB4E0(u32 identifier);
extern void func_08015110(void *context, void *destination, const void *text,
                          u32 mode, u32 enabled);
extern Transfer0802F100 *func_0802DFCC(void);
extern void func_08000ADC(Transfer0802F100 *request, const void *source,
                         void *destination, u16 words);
extern void func_0802EB58(void);

/* Complete [0x0802F100, 0x0802F1D0): 208 bytes, 79 instructions. */
void func_0802F100(void)
{
    const TextEntry0802F100 *entry = &g_table_08528F34[
        g_state_02000000.selections[data_0200F444->selected][0]];
    u8 *buffer = data_02004270 +
        (data_0200F444->step + data_0200F444->height) * 0x2C0;
    u8 identifier = entry->text;
    Transfer0802F100 *request;

    g_callbacks_0836D4B8[0](buffer, 0x2C0);
    if (identifier != 0) {
        const u8 *text = func_080CB4E0(identifier);
        func_08015110(data_0200F444->text_state, buffer, text, 0, 1);
    } else {
        func_08015110(data_0200F444->text_state, buffer,
                      g_table_085567F0[0], 0, 1);
    }
    request = func_0802DFCC();
    func_08000ADC(request, buffer, data_030008B0.tiles +
                  ((data_0200F444->step + data_0200F444->height) *
                   0x2C0 + 0x21C0), 0xB0);
    func_0802EB58();
}
