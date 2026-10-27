#include "ffta.h"

/* 0x08011644..0x08011690: 76 bytes / 29 instructions. */
struct Entry08011644;

struct Snapshot08011644 {
    struct Entry08011644 **source;
    struct Entry08011644 *value;
};

extern struct Entry08011644 *data_02009178;
extern struct Entry08011644 *data_0200917C;
extern struct Entry08011644 *data_02009174;
extern struct Entry08011644 *data_02009180;

void func_08011644(struct Snapshot08011644 *snapshot, u8 selector)
{
    struct Entry08011644 **source;

    switch (selector) {
    case 0:
        source = &data_02009178;
        break;
    case 1:
        source = &data_0200917C;
        break;
    case 2:
        source = &data_02009174;
        break;
    case 3:
        source = &data_02009180;
        break;
    default:
        return;
    }
    snapshot->source = source;
    snapshot->value = *source;
}
