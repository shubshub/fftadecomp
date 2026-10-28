#include "ffta.h"

struct Record080BA6E4 {
    u8 unknown00[0x108];
};

struct Context080BA6E4 {
    u8 unknown00[0x0C];
    struct Record080BA6E4 *entries[149];
    s8 count;
};

extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete [0x080BA6E4, 0x080BA728): 68 bytes, 33 instructions. */
void func_080BA6E4(void *data,
                   struct Record080BA6E4 *records, s32 count)
{
    struct Record080BA6E4 *record = records;
    struct Context080BA6E4 *context = data;
    s32 i;

    for (i = 0; i < count; i++, record++) {
        if (func_080C7EA4(record, 1)) {
            context->entries[context->count] = record;
            context->count++;
        }
    }
}
