#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
    s16 value;
} SignedValueRecord;

/* Evaluator slot 19, [0x08131758, 0x08131760). */
s32 func_08131758(SignedValueRecord *record)
{
    return record->value >> 2;
}
