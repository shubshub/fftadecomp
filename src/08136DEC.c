#include "ffta.h"

// Target: complete [0x08136DEC, 0x08137040), 596 bytes.
typedef struct {
    u8 unknown_0000[0x898b];
    u8 timer;
    u8 count;
    u8 phase;
    u8 skipped;
} TitleState;

extern TitleState *data_0200F3B0;
extern u16 data_03000000[];
extern const u8 data_083A8C84[];
extern void *func_08147AD0(u16 first, u16 count, u16 duration);
extern void func_08141540(u16 song_id);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);

u32 func_08136DEC(void)
{
    s16 x = 65;
    s16 y = 105;
    u8 visible = 1;

    switch (data_0200F3B0->phase) {
    case 0:
        data_0200F3B0->timer++;
        x = 300 - data_0200F3B0->timer * 4;
        if (x <= 64) {
            x = 65;
            data_0200F3B0->timer = data_0200F3B0->count = 0;
            data_0200F3B0->phase++;
        }
        break;
    case 1:
        data_0200F3B0->timer++;
        if (data_0200F3B0->timer > 34)
            visible = 0;
        if (data_0200F3B0->timer > 49) {
            data_0200F3B0->count++;
            data_0200F3B0->timer = 0;
        }
        if (data_0200F3B0->count > 7) {
            data_0200F3B0->timer = data_0200F3B0->count = 0;
            data_0200F3B0->phase++;
        }
        break;
    case 2:
        data_0200F3B0->timer++;
        x = 65 - data_0200F3B0->timer * 4;
        if (x < -100) {
            data_0200F3B0->timer = data_0200F3B0->count = 0;
            visible = 0;
            data_0200F3B0->phase++;
        }
        break;
    case 3:
        visible = 0;
        data_0200F3B0->timer++;
        if (data_0200F3B0->timer > 64) {
            data_0200F3B0->phase = data_0200F3B0->timer = data_0200F3B0->count = 0;
        }
        break;
    case 4:
        visible = 1;
        data_0200F3B0->timer++;
        if (data_0200F3B0->timer > 5) {
            func_08147AD0(336, 16, 15);
            data_0200F3B0->timer = 0;
            data_0200F3B0->phase = 5;
        }
        break;
    case 5:
        data_0200F3B0->timer++;
        x = 65 - data_0200F3B0->timer * 8;
        if (x < -100) {
            data_0200F3B0->timer = data_0200F3B0->count = 0;
            return 1;
        }
        break;
    }

    if (visible)
        func_08001F34(data_083A8C84, x, y, 0, 0, 0, 0, 0, 0, 0, 0);

    if (data_03000000[1] & 8) {
        if (!data_0200F3B0->skipped) {
            func_08141540(153);
            data_0200F3B0->skipped = 1;
            data_0200F3B0->phase = 4;
            data_0200F3B0->timer = 0;
        }
    }
    return 0;
}
