#include "ffta.h"

/* 0x080DD4C4..0x080DD4D4: 16 bytes. */
typedef struct {
    u32 value;
} Record080DD4C4;

u32 func_080DD4C4(const Record080DD4C4 *record)
{
    u32 result = 0;

    if (record)
        result = record->value;
    return result;
}
