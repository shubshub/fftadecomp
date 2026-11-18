#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 selection : 5;
    u8 primary : 1;
    u8 secondary : 1;
    u8 unknown_17 : 1;
    u8 unknown_03[3];
} ActionEntry;

/* 0x080D2E6C..0x080D2E78, six Thumb instructions. */
void func_080D2E6C(ActionEntry *entry)
{
    entry->primary = 0;
}
