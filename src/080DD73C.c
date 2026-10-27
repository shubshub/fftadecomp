#include "ffta.h"

/* 0x080DD73C..0x080DD746: 10 bytes. */
typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} FlagRecord;

u32 func_080DD73C(const FlagRecord *record)
{
    return (record->flags >> 15) & 1;
}
