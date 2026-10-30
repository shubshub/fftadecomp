#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 kind;
    u8 handler;
} ActionRecord;

typedef struct {
    u8 unknown_00[0x30];
    ActionRecord *record;
} ActionState;

extern ActionState data_0200F3F0;

/* Complete [0x08131474, 0x08131480): 12 bytes, 4 reachable Thumb instructions.
 * 0148006b80787047f0f30002
 */
u8 func_08131474(void)
{
    return data_0200F3F0.record->handler;
}
