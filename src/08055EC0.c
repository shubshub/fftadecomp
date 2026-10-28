#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA8];
    u16 flags;
    u8 unknown_AA[0x5E];
} MenuUnit;

typedef struct {
    u8 unknown_00[0x2D3A];
    u8 unitIds[0x1B];
    u8 selection;
} MenuSelection;

extern MenuUnit g_state_02000000[];
extern MenuSelection *data_0200F428;
extern void func_08141540(u32 sound);

void func_08055EC0(u8 *state)
{
    func_08141540(0x64);
    if (!(g_state_02000000[data_0200F428->unitIds[data_0200F428->selection]].flags & 0x10))
        *state = 0x64;
    else
        *state = 0x78;
}
