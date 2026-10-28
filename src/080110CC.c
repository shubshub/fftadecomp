#include "ffta.h"

/* 0x080110CC..0x080110D6: 10 bytes. */
typedef struct {
    u8 unknown_00[0x30];
    s8 value;
} Record080110CC;

s8 func_080110CC(Record080110CC *record)
{
    return record->value;
}
