#include "ffta.h"

typedef struct {
    u8 unknown_00[0x168];
    void *transfer;
} TransferState;

extern TransferState g_state_02007F40;

/* 08020490..080204B0: 32 bytes. */
u8 func_08020490(void)
{
    return g_state_02007F40.transfer == 0;
}
