#include "ffta.h"

typedef struct {
    u8 unknown_00[0xFC];
    s8 cached[4];
} CachedRecord;

void func_080CA2E8(void *object);

s32 func_080CA610(void *object)
{
    CachedRecord *record = object;
    s8 *cached;

    func_080CA2E8(object);
    cached = record->cached;
    return cached[2];
}
