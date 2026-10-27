#include "ffta.h"

/* 0x0800ADD8..0x0800AE9E: 198 bytes. */
typedef struct {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[16];
    const u8 *data;
} ResourceTable;

static inline u16 read_le16(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

void func_0800ADD8(const ResourceTable *table, u16 index, u32 *offset,
                  u16 *first, u16 *second, u16 *third, u16 *fourth)
{
    index &= 0x3FFF;
    if (table->flags & 0x4000) {
        const u8 *base = table->data;
        u32 entry_offset = ((const u16 *)base)[index];
        const u8 *entry = base + entry_offset;

        if (offset)
            *offset = entry_offset;
        if (first)
            *first = entry[0];
        if (second)
            *second = entry[1];
        if (third)
            *third = entry[2];
        if (fourth)
            *fourth = entry[3];
    } else {
        const u8 *base = table->data;
        u32 entry_offset = ((const u32 *)base)[index];
        const u8 *entry = base + entry_offset;

        if (offset)
            *offset = entry_offset;
        if (first)
            *first = read_le16(entry);
        if (second)
            *second = read_le16(entry + 2);
        if (third)
            *third = read_le16(entry + 4);
        if (fourth)
            *fourth = read_le16(entry + 6);
    }
}
