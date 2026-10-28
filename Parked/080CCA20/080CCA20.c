#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01[3];
} ExtraEntry;

typedef struct {
    u8 value;
    u8 unknown_01[15];
} BaseEntry;

extern const ExtraEntry data_0839475C[];
extern const BaseEntry g_table_08528F34[];

static inline const BaseEntry *base_entry(u16 value)
{
    u32 index = value;
    const BaseEntry *table = g_table_08528F34;

    if (value > 0x55)
        index = value - 0x55;
    return &table[index];
}

u8 func_080CCA20(u16 value)
{
    if (value > 0xAA)
        return data_0839475C[value - 0xAB].value;
    return base_entry(value)->value;
}
