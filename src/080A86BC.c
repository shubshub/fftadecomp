#include "ffta.h"

typedef struct {
    s16 first;
    s16 second;
    s16 third;
    s16 unknown_06;
} Entry080A86BC;

typedef struct {
    u8 unknown_00[0x10];
    Entry080A86BC entries[2];
    u8 unknown_20[0x2E];
    s16 selector;
} Struct080A86BC;

void func_080A86BC(Struct080A86BC *source, s16 *destination)
{
    destination[0] = source->entries[source->selector].first;
    destination[1] = source->entries[source->selector].second;
    destination[2] = source->entries[source->selector].third;
}
