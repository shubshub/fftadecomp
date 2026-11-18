#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *current;
    u32 unknown_08;
    u32 length;
    u32 distance;
} Transfer08022748;

extern void (*const data_0836D4BC)(void *destination, const void *source, u32 length);

/* 0x08022748: 40 bytes; copy from the back-reference and advance the output cursor. */
u32 func_08022748(Transfer08022748 *transfer)
{
    data_0836D4BC(transfer->current, transfer->current - transfer->distance,
                  transfer->length);
    transfer->current += transfer->length;
    return 0;
}
