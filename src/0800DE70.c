#include "ffta.h"

/* 0x0800DE70..0x0800DEBE: 78 bytes. The DMA back buffer contains
 * two scroll halfwords per line. Each byte store reads its lane first. */

typedef struct {
    u16 first[160];
    u16 second[160];
} ScanlinePlanes;

typedef struct __attribute__((packed)) {
    volatile u16 first;
    volatile u16 second;
} ScanlinePair;

void func_0800DE70(const ScanlinePlanes *planes, ScanlinePair *out)
{
    u8 line;

    for (line = 0; line < 160; line++, out++) {
        out->first = planes->first[line];
        out->second = planes->second[line];
    }
}
