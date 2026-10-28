#include "ffta.h"

typedef struct {
    u8 unknown_000[0xc1d];
    u8 selected;
    u8 unknown_c1e[0x3e];
    u16 values[5];
} SelectionState0807A734;

extern SelectionState0807A734 *data_03002818;
extern void func_08141540(u32 sound);

/* Complete target [0x0807A734, 0x0807A79C): 104 bytes, 42 instructions. */
u8 func_0807A734(void)
{
    u8 previous = data_03002818->selected;

    do {
        if (data_03002818->selected != 0)
            data_03002818->selected--;
        else
            data_03002818->selected = 4;
    } while (data_03002818->values[data_03002818->selected] == 0);

    if (previous != data_03002818->selected)
        func_08141540(0x65);
    return data_03002818->selected;
}
