#include "ffta.h"

/* 0x0809A53C..0x0809A548: 12 bytes. */
typedef struct {
    u8 unknown_00[0x44];
    u32 value;
} ValueRecord;

u32 func_08021E3C(u32 value);

u32 func_0809A53C(ValueRecord *record)
{
    return func_08021E3C(record->value);
}
