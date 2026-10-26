#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1a88];
    u8 state;
    u8 unknown_1a89[0x29e3];
    u8 saved_command;
} Context0806B228;

extern Context0806B228 *data_0200F428;
extern u8 func_0806FE14(const u8 *state);
extern void func_08141540(u32 sound);

/* 0x0806B228..0x0806B274: 76 bytes, 28 instructions. */
void func_0806B228(u8 *command)
{
    if (func_0806FE14(&data_0200F428->state) == 1) {
        data_0200F428->saved_command = *command;
        *command = 0x3e;
        func_08141540(0x68);
    } else {
        *command = 0x50;
        func_08141540(0x69);
    }
}
