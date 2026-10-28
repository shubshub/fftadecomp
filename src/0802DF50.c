#include "ffta.h"

typedef struct {
    u16 category : 4;
    u16 value : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} __attribute__((packed)) CategoryEntry0802DF50;

typedef void (*BufferInitializer0802DF50)(void *destination, u32 size);

extern CategoryEntry0802DF50 data_02003C3C[24];
extern BufferInitializer0802DF50 const g_callbacks_0836D4B8[];

/* Complete [0x0802DF50, 0x0802DF90): 64 bytes, 27 instructions. */
CategoryEntry0802DF50 *func_0802DF50(void)
{
    CategoryEntry0802DF50 *entry = data_02003C3C;
    s32 index;

    for (index = 0; index < 24; index++, entry++) {
        if (entry->value == 0) {
            g_callbacks_0836D4B8[0](entry, sizeof(*entry));
            return entry;
        }
    }
    return 0;
}
