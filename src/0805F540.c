#include "ffta.h"

typedef struct PointerList0805F540 {
    u8 unknown_00[0x1B];
    u8 count;
    u8 unknown_1C[4];
    void *entries[66];
} PointerList0805F540;

typedef void (*BufferInitializer0805F540)(void *destination, u32 size);

extern PointerList0805F540 *data_0200F44C;
extern BufferInitializer0805F540 const g_callbacks_0836D4B8[];

/* Complete [0x0805F540, 0x0805F588): 72 bytes, 30 instructions. */
void func_0805F540(void *const *entries, s32 count)
{
    s32 index;

    g_callbacks_0836D4B8[0](data_0200F44C->entries,
                           sizeof(data_0200F44C->entries));
    for (index = 0; index < count; index++)
        data_0200F44C->entries[index] = entries[index];
    data_0200F44C->count = count;
}
