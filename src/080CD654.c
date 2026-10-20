#include "ffta.h"

void func_080CD654(u8 *record, u8 value)
{
    u8 current = record ? record[0x3A] : 0;

    if (value == current) {
        record[0x3A] = 0;
    } else {
        current = record ? record[0x3B] : 0;
        if (value == current) {
            record[0x3B] = 0;
        } else {
            current = record ? record[0x3C] : 0;
            if (value == current)
                record[0x3C] = 0;
        }
    }
}
