#include "ffta.h"

typedef struct {
    u16 value00;
    u16 value02;
    u16 value04;
    u8 unknown06[2];
    u8 value08;
    u8 value09;
    u8 value0A;
    u8 value0B;
    u8 value0C;
    u8 value0D;
    u16 value0E;
    s8 value10;
    s8 value11;
    s8 value12;
    s8 value13;
    s8 value14;
    s8 value15;
    s8 value16;
    s8 value17;
    u8 unknown18[5];
    u8 value1D;
    u8 unknown1E[2];
} EntryRecord;

extern const EntryRecord g_table_0851D180[];

u8 func_080C95A8(u16 index);

s32 func_080CA7A4(u16 entry, u8 selector)
{
    const EntryRecord *record = &g_table_0851D180[entry];
    u32 value;

    switch (selector) {
    case 0:
        return record->value00;
    case 1:
        return record->value02;
    case 2:
        return record->value04;
    case 3:
        return record->value08;
    case 4:
        return record->value09;
    case 5:
        return record->value0A;
    case 6:
        return record->value0B;
    case 7:
        return record->value0C;
    case 8:
        return record->value0D;
    case 9:
        return record->value0E;
    case 10:
        if (func_080C95A8(13))
            return record->value10;
        value = record->value10;
        if (entry == 0x33)
            value += func_080C95A8(1);
        if (value > 255)
            value = 255;
        return value;
    case 11:
        if (func_080C95A8(13))
            return record->value11;
        value = record->value11;
        if (entry == 0x12E)
            value += func_080C95A8(3);
        if (value > 255)
            value = 255;
        return value;
    case 12:
        if (func_080C95A8(13))
            return record->value12;
        value = record->value12;
        if (entry == 0x94)
            value += func_080C95A8(2);
        if (value > 255)
            value = 255;
        return value;
    case 13:
        if (func_080C95A8(13))
            return record->value13;
        value = record->value13;
        if (entry == 0x11E)
            value += func_080C95A8(4);
        if (value > 255)
            value = 255;
        return value;
    case 14:
        return record->value14;
    case 15:
        return record->value15;
    case 16:
        return record->value16;
    case 17:
        return record->value17;
    case 18:
        return record->value1D;
    default:
        return 0;
    }
}
