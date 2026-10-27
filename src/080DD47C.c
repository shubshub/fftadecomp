#include "ffta.h"

typedef struct {
    u32 value;
} WordRecord;

extern WordRecord *func_080A880C(WordRecord *record);

/* Complete target: 0x080DD47C..0x080DD488, 12 bytes. */
u32 func_080DD47C(WordRecord *record)
{
    return func_080A880C(record)->value;
}
