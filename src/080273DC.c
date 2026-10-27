#include "ffta.h"

typedef struct {
    u8 mode;
    u8 unknown_01;
    u8 width;
    u8 unknown_03[0x11];
} TextDisplay;

typedef struct {
    u8 unknown_00[0x80];
    TextDisplay display;
    u32 *identifier;
    u8 unknown_98[8];
    u8 *text;
} TextState;

typedef struct {
    u8 unknown_00[0xC];
    u16 identifier;
} MenuControl;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern MenuControl *data_0200F438;
extern BufferCopier data_0836D4BC[];
extern u8 data_030039C8[];
extern const u8 data_08497418[];
extern const u8 *const g_table_085567F0[];
extern u8 *func_080CBABC(u32 index);
extern void *func_08005B28(u32 size);
extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                        u16 index, u32 first, u32 second);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 0x080273DC..0x08027528: 332 bytes; prepare text for the selected identifier. */
void func_080273DC(TextState *state)
{
    TextDisplay *display = &state->display;
    u16 special = data_0200F438->identifier & 0x4000;

    if (special) {
        data_0836D4BC[0](data_030039C8, func_080CBABC(0) + 8, 6);
        data_0836D4BC[0](data_030039C8 + 0x12, func_080CBABC(0) + 0x1A, 6);
        state->text = func_08005B28(0x100);
        func_08013E9C(state->text, data_08497418, state->text + 0x80,
                      data_0200F438->identifier & 0x3FFF, 0, 0);
        display->width = 24;
        display->mode = 2;
        *state->identifier = data_0200F438->identifier & 0x3FFF;
    } else if (data_0200F438->identifier & 0x8000) {
        state->text = func_08005B28(0x100);
        func_08013E9C(state->text, data_08497418, state->text + 0x80,
                      data_0200F438->identifier & 0x7FFF, 0, 0);
        display->width = 24;
        display->mode = 2;
        *state->identifier = data_0200F438->identifier & 0x7FFF;
    } else {
        state->text = func_08005B28(0x40);
        *state->identifier = func_080CCD50(data_0200F438->identifier, 0);
        func_08018C24(state->text, g_table_085567F0[*state->identifier]);
    }
}
