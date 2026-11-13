#include "ffta.h"

// Complete [0x0802E160, 0x0802E338): 472 bytes, including the literal pools.

typedef struct Root0802E160 {
    u8 unknown_0000[0x3C34];
    u8 selections[0][2];
} Root0802E160;

typedef struct TextEntry0802E160 {
    u8 unknown_00;
    u8 text;
    u8 unknown_02[14];
} TextEntry0802E160;

typedef struct TextPanel0802E160 {
    u8 unknown_00[8];
    u8 count;
    u8 unknown_09[5];
    u8 active;
    u8 unknown_0F[1];
    u8 text_state[0x48C];
    u16 maps[0][0x34];
} TextPanel0802E160;

typedef struct Graphics0802E160 {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics0802E160;

typedef struct Transfer0802E160 Transfer0802E160;

extern Root0802E160 g_state_02000000;
extern TextPanel0802E160 *data_0200F444;
extern const TextEntry0802E160 g_table_08528F34[];
extern u8 data_02004270[];
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern const u8 *const g_table_085567F0[];
extern Graphics0802E160 data_030008B0;
extern const u8 *func_080CB4E0(u32 identifier);
extern void func_08015110(void *context, void *destination, const void *text,
                          u32 mode, u32 enabled);
extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                          u8 height, u8 stride, u16 tile, u8 palette);
extern Transfer0802E160 *func_0802DFCC(void);
extern void func_08000ADC(Transfer0802E160 *request, const void *source,
                         void *destination, u16 words);
extern void func_0802E008(void);

void func_0802E160(void)
{
    s32 i;

    for (i = 0; i < data_0200F444->count; i++) {
        u8 *buffer = data_02004270 + i * 0x2C0;
        u8 identifier;

        g_callbacks_0836D4B8[0](buffer, 0x2C0);
        identifier = g_state_02000000.selections[i][0];
        if (identifier != 0)
            func_08015110(data_0200F444->text_state, buffer,
                          func_080CB4E0(identifier), 0, 1);
        else
            func_08015110(data_0200F444->text_state, buffer,
                          g_table_085567F0[0], 0, 1);
        func_080157A8(data_0200F444->maps[i], 0, 0, 11, 1, 26,
                      i * 0x16 + 0x10E, 7);

        buffer = data_02004270 + (i + data_0200F444->count) * 0x2C0;
        g_callbacks_0836D4B8[0](buffer, 0x2C0);
        identifier = (g_table_08528F34 + identifier)->text;
        if (identifier != 0)
            func_08015110(data_0200F444->text_state, buffer,
                          func_080CB4E0(identifier), 0, 1);
        else
            func_08015110(data_0200F444->text_state, buffer,
                          g_table_085567F0[0], 0, 1);
        func_080157A8(data_0200F444->maps[i] + 12, 0, 0, 11, 1, 26,
                      (i + data_0200F444->count) * 0x16 + 0x10E, 8);
    }

    func_08000ADC(func_0802DFCC(), data_02004270, data_030008B0.tiles + 0x21C0,
                  data_0200F444->count * 0x160);
    data_0200F444->active = 0;
    func_0802E008();
}
