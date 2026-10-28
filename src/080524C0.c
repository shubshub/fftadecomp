#include "ffta.h"

/* 0x080524C0..0x080524E8: 40 bytes, 15 reachable instructions. */
typedef struct {
    u8 unknown_0000[0x1D44];
    u8 selection;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u32 sound);

void func_080524C0(u8 *state)
{
    func_08141540(100);
    *state = 200;
    data_0200F428->selection = 254;
}
