#include "ffta.h"

/* 0x08000FC8..0x0800105C: 148 bytes. */
typedef struct {
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
} CachedRecord;

extern u8 data_03000028;
extern u8 data_03003270[][32];
extern CachedRecord data_030032B0[][32];

int func_08000FC8(const CachedRecord *record)
{
    u8 *used = data_03003270[data_03000028];
    CachedRecord *records = data_030032B0[data_03000028];
    CachedRecord *entry = records;
    int index;

    for (index = 0; index < 32; entry++, index++) {
        if (used[index] && record->first == entry->first &&
            record->second == entry->second && record->third == entry->third &&
            record->fourth == entry->fourth)
            return index;
    }
    entry = records;
    for (index = 0; index < 32; entry++, index++) {
        if (!used[index]) {
            used[index] = 1;
            entry->first = record->first;
            entry->second = record->second;
            entry->third = record->third;
            entry->fourth = record->fourth;
            return index;
        }
    }
    return 0;
}
