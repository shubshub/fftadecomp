#include "ffta.h"

struct RecordComponent {
    u8 data[0x6C];
};

struct Record {
    u8 unknown[0x1C];
    struct RecordComponent component;
};

struct RecordSet {
    u32 unknown;
    struct Record records[6];
};

extern void func_081378EC(struct RecordComponent *component);

void func_081379C8(struct RecordSet *set)
{
    u8 index;

    for (index = 0; index < 6; index++)
        func_081378EC(&set->records[index].component);
}
