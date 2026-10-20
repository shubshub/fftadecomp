#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
    s16 value;
} SignedValueRecord;

s32 func_08131A78(SignedValueRecord *record)
{
    s32 value = record->value;
    s32 result;

    if (value < 0)
        value = -value;
    result = value / 4;
    if (result == 0)
        result = 1;
    return result;
}
