#include "ffta.h"

/* 0x08099CB8..0x08099CC4: 12 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u32 value;
} ValueRecord;

u32 func_080C7B08(u32 value);

u32 func_08099CB8(ValueRecord *record)
{
    return func_080C7B08(record->value);
}
