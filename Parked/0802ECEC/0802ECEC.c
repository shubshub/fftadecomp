#include "ffta.h"

/* Target: complete [0x0802ECEC, 0x0802ED88), 156 bytes. */
typedef struct {
    u8 unknown_00[7];
    u8 count;
    u8 unknown_08;
    u8 selected;
} FilterState;

typedef struct {
    u8 unknown_0000[0x3c34];
    u16 identifiers[0];
} ResourceState;

typedef struct {
    u8 category;
    u8 unknown_01[15];
} ResourceEntry;

extern FilterState *data_0200F444;
extern ResourceState g_state_02000000;
extern const ResourceEntry g_table_08528F34[];

void func_0802ECEC(u8 filter)
{
    s32 index;

    data_0200F444->selected = 0;
    for (index = 0; index < data_0200F444->count; index++) {
        if (g_state_02000000.identifiers[index]) {
            if ((u8)(filter - 0x56) <= 0x54) {
                if (g_state_02000000.identifiers[index] != filter - 0x55)
                    continue;
            } else if ((u8)(filter - 0xab) <= 5) {
                if (g_table_08528F34[g_state_02000000.identifiers[index]].category !=
                    filter - 0xaa)
                    continue;
            }
            data_0200F444->selected |= 1 << index;
        }
    }
}
