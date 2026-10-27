#include "ffta.h"

/* Complete [0x081310FC, 0x08131114): 24 bytes, 11 instructions. */
typedef struct {
    u32 first;
    u32 second;
    u8 unknown_08[0x1C];
    u8 selector;
} SelectionRecord;

extern u32 func_0812D398(u32 first, u32 second, u8 selector);

u8 func_081310FC(const SelectionRecord *record)
{
    return func_0812D398(record->first, record->second, record->selector);
}
