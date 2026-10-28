#include "ffta.h"

/* 0x08020008..0x0802006C: 100 bytes. */
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

typedef struct {
    u8 unknown_00[0x0C];
    u8 count;
} Resource;

extern const u8 data_08569104[];
extern ResourceSelection data_02007F10;

static inline u8 has_resource(const ResourceRecord *record)
{
    return record->resource_offset != 0;
}

u8 func_08020008(void)
{
    const u8 *base = data_08569104;
    ResourceSelection *selection = &data_02007F10;
    const ResourceRecord *record = &((const ResourceRecord *)base)[selection->selected];
    if (has_resource(record)) {
        const Resource *resource = (const Resource *)(base + record->resource_offset);
        if (selection->position + 1 < resource->count)
            return 1;
    }
    return 0;
}
