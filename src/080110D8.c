#include "ffta.h"

/* 0x080110D8..0x080110F8: 32 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[7];
    u8 mode;
} Record080110D8;

u8 func_080110D8(const Record080110D8 *record)
{
    if (record->mode == 0)
        return 1;
    if (record->mode == 1)
        return 1;
    if ((record->flags & 0x80) == 0)
        return 0;
    return 1;
}
