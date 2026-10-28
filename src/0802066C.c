#include "ffta.h"

/* 0x0802066C..0x080206BE: 82 bytes. */
typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 unknown_54[4];
} ResourceRecord;

typedef struct {
    u16 selected;
    u8 unknown_02[0x27];
    u8 position;
} ResourceSelection;

extern const u8 data_08569104[];
extern ResourceSelection data_02007F10;

static inline u8 has_resource(const ResourceRecord *record)
{
    return record->resource_offset != 0;
}

u8 func_0802066C(void)
{
    const u8 *base = data_08569104;
    ResourceSelection *selection = &data_02007F10;
    const ResourceRecord *record =
        &((const ResourceRecord *)base)[selection->selected];

    if (has_resource(record) == 0)
        return 0;
    return selection->position;
}
