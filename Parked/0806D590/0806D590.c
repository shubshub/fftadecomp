#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1A88];
    u8 state;
    u8 unknown_1A89[0x29E3];
    u8 event;
} State0806D590;

extern State0806D590 *data_0200F428;
extern u8 func_0806FE14(const u8 *state);
extern void func_08141540(u32 sound);

/* 0806D590..0806D5F4: 100 bytes, 37 reachable instructions. */
void func_0806D590(u8 *selection)
{
    if (func_0806FE14(&data_0200F428->state) == 4) {
        func_08141540(0x64);
        *selection = 0x3C;
        data_0200F428->event = 0x17;
    } else if (func_0806FE14(&data_0200F428->state) == 1) {
        func_08141540(0x68);
        *selection = 0x3E;
        data_0200F428->event = 0x17;
    }
}
