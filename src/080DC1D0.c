#include "ffta.h"

/* 0x080DC1D0..0x080DC1E6: 22 bytes. */
typedef struct {
    u32 value;
} WordRecord080DC1D0;

extern u32 func_080DD47C(WordRecord080DC1D0 *record);
extern u8 func_080DB944(u32 selector, u32 value);

u8 func_080DC1D0(WordRecord080DC1D0 *record)
{
    return func_080DB944(6, func_080DD47C(record));
}
