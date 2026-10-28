#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u8 value;
} Child0809D9D8;

typedef struct {
    void *key;
    Child0809D9D8 *child;
    u8 unknown_08[0xAC];
} Entry0809D9D8;

typedef struct {
    u8 unknown_00[8];
    Entry0809D9D8 entries[13];
} Object0809D9D8;

/* 0x0809D9D8..0x0809DA0A: 50 bytes, 25 instructions. */
void func_0809D9D8(Object0809D9D8 *object, void *key, u8 value)
{
    Entry0809D9D8 *match;
    s32 i = 0;
    Entry0809D9D8 *entry = object->entries;

    for (;;) {
        if (entry->key == key) {
            match = entry;
            break;
        }
        entry++;
        i++;
        if (i >= 13) {
            match = 0;
            break;
        }
    }
    if (match) {
        match->child->value = value;
    }
}
