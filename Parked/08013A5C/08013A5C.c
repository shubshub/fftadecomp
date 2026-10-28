#include "ffta.h"

/* 0x08013A5C..0x08013A86: 42 bytes. */
typedef struct {
    u8 unknown_00[0x13];
    u8 mode;
} State08013A5C;

extern State08013A5C g_state_020020D0;
extern const u8 data_084966B0[];

u8 func_08013A5C(u16 index)
{
    if (g_state_020020D0.mode != 0)
        return 0x10;
    return *((s16)index + data_084966B0);
}
