#include "ffta.h"

/* 0x0812B5D4..0x0812B5F6: 34 bytes, 17 instructions. */
typedef struct {
    u8 value;
    u8 unknown_01;
} __attribute__((packed)) ByteEntry;

u16 func_0812B5D4(const ByteEntry *entries)
{
    u16 count = 0;
    const ByteEntry *entry = entries;

    while (entry->value) {
        count++;
        entry = entries + count;
    }
    return count;
}
