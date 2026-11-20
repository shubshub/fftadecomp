#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x8620];
    u8 effects[0x334];
    u8 unknown_8954[0xE];
    u8 selection;
    u8 mode_selection;
    u8 unknown_8964[3];
    u8 result;
    u16 duration;
    u8 unknown_896A[0x29];
    u8 menu;
    u8 cursor_frame;
    u8 unknown_8995[3];
    u32 effect_seed;
} TitleMenu;

typedef struct {
    u8 unknown_0000[0x2FC2];
    unsigned mode : 2;
} GameOptions;

extern TitleMenu *data_0200F3B0;
extern GameOptions g_state_02000000;
extern u16 data_03000000[];
extern const s16 data_083A8C6C[];
extern const s16 data_083A8C78[];
extern const u8 data_083A8C9E[], data_083A8CAC[], data_083A8CC0[];
extern const u8 data_083A8CD4[], data_083A8CE2[], data_083A8CF0[], data_083A8CFE[];
extern void func_08141540(u16 song_id);
extern void func_08137A7C(u32 value, u32 *destination);
extern void func_08135CFC(u8 mode);
extern void func_0813790C(void *effects);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, u32 palette_offset);

/* The title renderer numbers the normal, selected and cursor variants. */
#define DRAW(source, x, y, flipped, style) \
    func_08001F34(source, x, y, 0, 0, 0, flipped, 0, 0, 0, (style))

/* Complete Thumb symbol [0x08136A10, 0x08136DEC), 988 bytes. */
void func_08136A10(u8 *phase)
{
    s16 x = 0;
    s16 y = 0;
    u8 styles[3];
    u8 flip;
    s16 frame;

    styles[0] = styles[1] = styles[2] = 1;
    flip = 0;
    switch (data_0200F3B0->menu) {
    case 0:
        if (data_03000000[2] & 0x80) {
            if (data_0200F3B0->selection == 2)
                data_0200F3B0->selection = 0;
            else
                data_0200F3B0->selection++;
            func_08141540(109);
        } else if (data_03000000[2] & 0x40) {
            if (data_0200F3B0->selection == 0)
                data_0200F3B0->selection = 2;
            else
                data_0200F3B0->selection--;
            func_08141540(109);
        }
        styles[data_0200F3B0->selection] = 3;
        x = data_083A8C6C[data_0200F3B0->selection << 1];
        y = data_083A8C6C[(data_0200F3B0->selection << 1) + 1];
        if ((data_03000000[1] & 8) || (data_03000000[1] & 1)) {
            switch (data_0200F3B0->selection) {
            case 0:
                func_08141540(153);
                *phase = 10;
                data_0200F3B0->duration = 30;
                data_0200F3B0->result = 4;
                func_08137A7C(23, &data_0200F3B0->effect_seed);
                break;
            case 1:
                func_08141540(153);
                *phase = 10;
                data_0200F3B0->duration = 20;
                data_0200F3B0->result = 2;
                func_08137A7C(23, &data_0200F3B0->effect_seed);
                break;
            case 2:
                func_08141540(100);
                data_0200F3B0->menu = 1;
                data_0200F3B0->mode_selection = g_state_02000000.mode;
                break;
            }
        }
        break;
    case 1: {
        u8 mode_styles[3];
        mode_styles[0] = mode_styles[1] = mode_styles[2] = 1;
        if (data_03000000[2] & 0x80) {
            if (data_0200F3B0->mode_selection == 2)
                data_0200F3B0->mode_selection = 0;
            else
                data_0200F3B0->mode_selection++;
            func_08141540(109);
        } else if (data_03000000[2] & 0x40) {
            if (data_0200F3B0->mode_selection == 0)
                data_0200F3B0->mode_selection = 2;
            else
                data_0200F3B0->mode_selection--;
            func_08141540(109);
        }
        x = data_083A8C78[data_0200F3B0->mode_selection << 1];
        y = data_083A8C78[(data_0200F3B0->mode_selection << 1) + 1] + 3;
        if (data_03000000[1] & 2) {
            func_08141540(105);
            data_0200F3B0->menu = 0;
            break;
        }
        if (data_03000000[1] & 1) {
            func_08141540(100);
            func_08135CFC(data_0200F3B0->mode_selection);
            func_0813790C(data_0200F3B0->effects);
            data_0200F3B0->menu = 0;
        }
        mode_styles[data_0200F3B0->mode_selection] = 3;
        DRAW(data_083A8CD4, 154, 80, 0, mode_styles[0]);
        DRAW(data_083A8CE2, 154, 96, 0, mode_styles[1]);
        DRAW(data_083A8CF0, 154, 112, 0, mode_styles[2]);
        flip = 1;
        break;
    }
    }
    DRAW(data_083A8C9E, 28, 72, 0, styles[0]);
    DRAW(data_083A8CAC, 20, 88, 0, styles[1]);
    DRAW(data_083A8CC0, 12, 112, 0, styles[2]);
    data_0200F3B0->cursor_frame++;
    data_0200F3B0->cursor_frame %= 30U;
    frame = data_0200F3B0->cursor_frame / 5U;
    DRAW(data_083A8CFE, x + frame, y, flip, 4);
}
