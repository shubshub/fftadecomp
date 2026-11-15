#include "ffta.h"

/* 0x0809D98C..0x0809D9D8: 76 bytes, 38 instructions.
 * Finds the entry whose key matches among thirteen 0xB4-byte entries at
 * object+8, then writes four halfwords to its record at +0x1E, +0x20, +0x22
 * and +0x24 and copies the first to +0x1C.
 */
typedef struct {
    void *key;
    Rec5 *record;
    u8 unknown_08[0xAC];
} Entry0809D98C;

typedef struct {
    u8 unknown_00[8];
    Entry0809D98C entries[13];
} Object0809D98C;

/* The ROM narrows the u16 arguments on entry and then sign-extends the first
 * one before the stores, so the setter takes s16.  The same five stores, with
 * the arguments materialised first, are inline at 0x0809D1E2 and 0x0809D494.
 * The out-of-line func_0809D620 has the same store sequence but zero-extends
 * its first argument, so it is not this setter.
 */
static inline void set_record(Rec5 *record, s16 a, s16 b, s16 c, s16 d)
{
    record->f2 = a;
    record->f3 = b;
    record->f4 = c;
    record->f5 = d;
    record->f1 = a;
}

void func_0809D98C(Object0809D98C *object, void *key, u16 a, u16 b, u16 c,
                   u16 d)
{
    Entry0809D98C *match;
    s32 i = 0;
    Entry0809D98C *entry = object->entries;

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
        set_record(match->record, a, b, c, d);
    }
}
