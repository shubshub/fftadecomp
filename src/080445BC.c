#include "ffta.h"

/* Target: complete [0x080445BC, 0x080445DA), 30 bytes. */
struct EntrySpecification {
    u8 slot : 3;
    u8 unknown_03 : 1;
    u8 mode : 2;
    u8 type : 4;
    u8 unknown_0a : 6;
    u8 position : 5;
    u8 unknown_15 : 2;
    u8 resource : 8;
    u8 unknown_1f : 1;
} __attribute__((packed));

extern u32 func_080445DC(struct EntrySpecification *specification, u8 slot,
                        u32 unused, u8 option);

u32 func_080445BC(struct EntrySpecification *specification, u8 option)
{
    return func_080445DC(specification, (u8)(specification->position - 1),
                          0, option);
}
