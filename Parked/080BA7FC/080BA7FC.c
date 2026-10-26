#include "ffta.h"

typedef struct {
    u32 field_00;
    u8 unknown_04[4];
    u8 active;
    u8 unknown_09[3];
} ActiveRecord;

/* 0x080BA7FC..0x080BA816: 26 bytes. */
void func_080BA7FC(ActiveRecord *records)
{
    s32 i;

    records[0].field_00 = 0;
    for (i = 12; i >= 0; i--)
        records[i].active = 0;
}
