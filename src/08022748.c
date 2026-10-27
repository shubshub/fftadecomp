#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *current;
    u32 unknown_08;
    u32 length;
    u8 *begin;
} Transfer08022748;

extern void (*data_0836D4BC)(u8 *destination, u32 offset, u32 length);

/* 0x08022748: 40 bytes; transfer the current span and advance the cursor. */
u32 func_08022748(Transfer08022748 *transfer)
{
    data_0836D4BC(transfer->current, transfer->current - transfer->begin,
                  transfer->length);
    transfer->current += transfer->length;
    return 0;
}
