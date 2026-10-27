#include "ffta.h"

/* 0x08135750..0x081357E8: 152 bytes. */
typedef struct {
    u8 unknown_0000[0x3C33];
    u8 count;
    u16 entries[1];
} RecordList;

typedef struct {
    u8 unknown_00[16];
} RecordConfig;

extern RecordList g_state_02000000;
extern RecordConfig g_table_08528F34[];
extern u8 func_081343C8(void *first, void *second, u16 value, u8 mode,
                         u32 flags, s16 amount, void *data,
                         RecordConfig *config);

u8 func_08135750(void *first, void *second, u16 value, u8 mode,
                u16 amount, void *data)
{
    s32 index;
    for (index = 0; index < g_state_02000000.count; index++) {
        if (func_081343C8(first, second, value, mode, 0, amount, data,
                         &g_table_08528F34[g_state_02000000.entries[index]]))
            return index + 1;
    }
    return 0;
}
