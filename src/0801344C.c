#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    u8 unknown_00[0x13];
    u8 mode;
} CopyState;

extern BufferCopier const data_0836D4BC[];
extern const u8 data_08433330[][128];
extern CopyState g_state_020020D0;
extern const u8 data_084966B0[];

/* 0801344C..0801348C: 64 bytes. */
u8 func_0801344C(void *destination, s16 index)
{
    const u8 *record = data_08433330[index];

    data_0836D4BC[0](destination, record, 128);
    if (g_state_020020D0.mode != 0)
        return 16;
    return data_084966B0[index];
}
