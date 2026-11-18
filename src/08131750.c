#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
    s16 value;
} SignedValueRecord;

/* Evaluator slot 18, [0x08131750, 0x08131756). */
s32 func_08131750(SignedValueRecord *record)
{
    return record->value;
}
