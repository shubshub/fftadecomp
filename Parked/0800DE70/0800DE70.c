#include "ffta.h"

typedef struct {
    u16 first[160];
    u16 second[160];
} ScanlinePlanes;

typedef struct __attribute__((packed)) {
    u16 first;
    u16 second;
} ScanlinePair;

void func_0800DE70(const ScanlinePlanes *planes, ScanlinePair *out)
{
    u8 line;

    for (line = 0; line < 160; line++, out++) {
        out->first = planes->first[line];
        out->second = planes->second[line];
    }
}
