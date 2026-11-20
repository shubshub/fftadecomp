#include "ffta.h"

typedef struct {
    u16 first[160];
    u16 second[160];
    u16 third[160];
    u16 fourth[160];
} ScanlinePlanes;

typedef struct __attribute__((packed)) {
    u16 first;
    u16 second;
    u16 third;
    u16 fourth;
} ScanlineRow;

/* Complete [0x0800D324, 0x0800D3BA), 150 bytes.
 * Mode 2 interleaves four planes into the inactive scanline DMA buffer. */
void func_0800D324(void *state, u16 *destination)
{
    const ScanlinePlanes *planes = state;
    volatile ScanlineRow *out = (void *)destination;
    u8 line;

    for (line = 0; line < 160; line++, out++) {
        out->first = planes->first[line];
        out->second = planes->second[line];
        out->third = planes->third[line];
        out->fourth = planes->fourth[line];
    }
}
