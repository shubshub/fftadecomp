#include "ffta.h"

typedef struct {
    u8 unknown_00[7];
    u8 step;
    u8 height;
    u8 unknown_09[7];
    u8 text_state[0];
} TextPanel;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

typedef struct TransferRecord TransferRecord;

extern TextPanel *data_0200F444;
extern u8 data_02004270[];
extern GraphicsState data_030008B0;
extern void (*g_callbacks_0836D4B8[])(void *destination, u32 size);
extern const u8 *const g_table_085567F0[];
extern void func_08015110(void *context, void *destination,
                          const void *text, u32 mode, u32 enabled);
extern TransferRecord *func_0802DFCC(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                         void *destination, u16 words);

/* 0x0802F1D0: 132 bytes; render and queue the panel's empty text row. */
void func_0802F1D0(void)
{
    u8 *buffer = data_02004270 +
        (data_0200F444->step + data_0200F444->height) * 0x2C0;
    TransferRecord *request;

    g_callbacks_0836D4B8[0](buffer, 0x2C0);
    func_08015110(data_0200F444->text_state, buffer,
                  g_table_085567F0[0], 0, 1);
    request = func_0802DFCC();
    func_08000ADC(request, buffer, data_030008B0.tiles +
                  ((data_0200F444->step + data_0200F444->height) *
                   0x2C0 + 0x21C0), 0xB0);
}
