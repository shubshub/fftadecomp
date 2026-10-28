#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 unknown_54[4];
} ResourceRecord08020628;

typedef struct {
    u16 selected;
} ResourceSelection08020628;

extern const u8 data_08569104[];
extern ResourceSelection08020628 data_02007F10;

u8 func_08020628(void)
{
    const u8 *base = data_08569104;
    ResourceSelection08020628 *selection = &data_02007F10;
    const ResourceRecord08020628 *record =
        &((const ResourceRecord08020628 *)base)[selection->selected];

    return record->resource_offset != 0;
}
