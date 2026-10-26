#include "ffta.h"

/* Target: complete [0x08137040, 0x08137192), 338 bytes. */
typedef struct {
    u8 unknown_00[0x898f];
    u8 frame;
    u8 first;
    u8 second;
    u8 third;
} AnimationState;

extern AnimationState *data_0200F3B0;
extern const u8 data_083A8C9E[];
extern const u8 data_083A8CAC[];
extern const u8 data_083A8CC0[];
extern s32 func_08137194(s32, s32, s32, s32);
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);

u32 func_08137040(void)
{
    s16 x;

    data_0200F3B0->frame++;
    if (data_0200F3B0->frame == 5)
        data_0200F3B0->first = 1;
    if (data_0200F3B0->frame == 10)
        data_0200F3B0->second = 1;
    if (data_0200F3B0->frame == 15)
        data_0200F3B0->third = 1;

    if (data_0200F3B0->first) {
        x = func_08137194(data_0200F3B0->first, 30, -100, 28);
        func_08001F34(data_083A8C9E, x, 72, 0, 0, 0, 0, 0, 0, 0, 0);
        if (data_0200F3B0->first < 30)
            data_0200F3B0->first++;
    }
    if (data_0200F3B0->second) {
        x = func_08137194(data_0200F3B0->second, 30, -100, 20);
        func_08001F34(data_083A8CAC, x, 88, 0, 0, 0, 0, 0, 0, 0, 0);
        if (data_0200F3B0->second < 30)
            data_0200F3B0->second++;
    }
    if (data_0200F3B0->third) {
        x = func_08137194(data_0200F3B0->third, 30, -100, 12);
        func_08001F34(data_083A8CC0, x, 112, 0, 0, 0, 0, 0, 0, 0, 0);
        if (data_0200F3B0->third < 30)
            data_0200F3B0->third++;
        else
            return 1;
    }
    return 0;
}
