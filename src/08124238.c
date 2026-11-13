#include "ffta.h"

// Complete [0x08124238, 0x0812429E): 102 bytes, 51 instructions.

extern void *func_08096D7C(void);
typedef struct {
    void *unit;
} Entry08124238;

extern u32 func_08099CDC(void *context, Entry08124238 **entries);
extern u8 func_080C8240(void *object);
extern u8 func_080C82B8(void *object);

Entry08124238 *func_08124238(void)
{
    Entry08124238 *entries[13];
    s32 count;
    s32 index;

    count = func_08099CDC(func_08096D7C(), entries);
    for (index = 0; index < count; index++) {
        Entry08124238 *entry = entries[index];

        if (func_080C8240(entry->unit) && func_080C82B8(entry->unit))
            return entry;
    }
    for (index = 0; index < count; index++) {
        Entry08124238 *entry = entries[index];

        if (func_080C8240(entry->unit))
            return entry;
    }
    return 0;
}
