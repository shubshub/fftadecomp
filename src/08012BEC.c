#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 status;
    u8 unknown_09[0x13];
    u8 mode;
} TextState08012BEC;

typedef struct {
    u16 pressed;
    u16 held;
    u16 repeated;
} InputState08012BEC;

extern TextState08012BEC *data_0200918C;
extern InputState08012BEC data_03000000;
extern u8 func_08012950(u8 immediate);

/* 0x08012BEC - 68 bytes. Advance text until its status changes. */
void func_08012BEC(void)
{
    s32 immediate = 0;

    for (;;)
    {
        u8 status = data_0200918C->status;

        if (func_08012950(immediate) != status)
            break;

        if (data_03000000.held & 3)
            immediate = 1;

        if (data_0200918C->mode == 1 || !immediate)
            break;
    }
}
