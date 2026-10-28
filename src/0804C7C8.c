#include "ffta.h"

/* 0x0804C7C8..0x0804C7EA: 34 bytes. */
typedef struct {
    u8 unknown_00[8];
    u16 current;
    u8 unknown_0A[4];
    u8 count;
    u8 unknown_0F[13];
} Record0804C7C8;

u8 func_0804C7C8(const Record0804C7C8 *records, u16 index)
{
    u8 result = 0;

    if (records[index].current + 1 == records[index].count)
        result = 1;
    return result;
}
