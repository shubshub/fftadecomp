#include "ffta.h"

typedef struct {
    void *manager;
    u8 *allocation;
    u8 unknown_008[0x1100];
} State0805F3C4;

typedef void (*Initialize0805F3C4)(void *destination, u32 size);

extern State0805F3C4 *data_0200F44C;
extern Initialize0805F3C4 const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void *func_08005C14(void *storage, u32 byte_count);

/* 0x0805F3C4..0x0805F414:
 * 70 B5 46 46 40 B4 05 1C C3 F7 38 FA 04 1C 0C 4E
 * 34 60 0C 48 0C 49 88 46 02 68 20 1C E2 F0 34 FF
 * 30 68 44 60 44 44 09 48 2D 18 20 1C 29 1C A6 F7
 * 0F FC 31 68 08 60 08 BC 98 46 70 BC 01 BC 00 47
 * 4C F4 00 02 B8 D4 36 08 08 11 00 00 F8 EE FF FF. */
void func_0805F3C4(u32 size)
{
    u8 *storage = func_08022840(size);

    data_0200F44C = (State0805F3C4 *)storage;
    g_callbacks_0836D4B8[0](storage, sizeof(*data_0200F44C));
    data_0200F44C->allocation = storage;
    storage += sizeof(*data_0200F44C);
    data_0200F44C->manager = func_08005C14(storage,
        size - sizeof(*data_0200F44C));
}
