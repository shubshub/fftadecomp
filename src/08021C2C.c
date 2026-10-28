#include "ffta.h"

/* 0x08021C2C..0x08021C36: 10 bytes. */
typedef struct {
    u32 flags;
} Flags08021C2C;

u32 func_08021C2C(const Flags08021C2C *record)
{
    return (record->flags >> 18) & 1;
}
