#include "ffta.h"

typedef struct {
    u8 unknown_000[0xc1d];
    u8 selection;
    u8 unknown_c1e[0x3e];
    u16 entries[5];
} SelectionState0807A6CC;

extern SelectionState0807A6CC *data_03002818;
extern void func_08141540(u32 sound);

/* 0x0807A6CC .. 0x0807A734: 104 bytes, including literal pools. */
u8 func_0807A6CC(void)
{
    u8 previous = data_03002818->selection;

    do {
        if (data_03002818->selection <= 3)
            data_03002818->selection++;
        else
            data_03002818->selection = 0;
    } while (data_03002818->entries[data_03002818->selection] == 0);

    if (previous != data_03002818->selection)
        func_08141540(0x65);

    return data_03002818->selection;
}
