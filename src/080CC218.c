#include "ffta.h"

/* Complete [0x080CC218, 0x080CC2B4): 156 bytes, 60 instructions.
 * 30b50004000c011caa281fd90749ab388000401802789006010e054b054c1819
 * 0078092808d1d00624e000005c473908000000025e2e0000034c181900780928
 * 26d1500616e000005f2e0000081c552901d9081c553800040749000b42181478
 * 6006010e054d064be818937b0078834208d1a006010e0be0348f520800000002
 * 5e2e0000044c28190078834200d11178081c30bc02bc08475f2e0000
 */

typedef struct {
    u8 value;
    u8 unknown_01[3];
} ExtraEntry;

typedef struct {
    u8 value;
    u8 unknown_01[13];
    u8 type;
    u8 unknown_0F;
} BaseEntry;

typedef struct {
    u8 unknown_0000[0x2E5E];
    u8 previous_first;
    u8 previous_second;
} State080CC218;

extern const ExtraEntry data_0839475C[];
extern const BaseEntry g_table_08528F34[];
extern State080CC218 g_state_02000000;

u8 func_080CC218(u16 entry)
{
    u8 amount;
    u16 index;

    if (entry > 0xAA) {
        amount = data_0839475C[entry - 0xAB].value << 2;
        if (g_state_02000000.previous_first == 9)
            amount = data_0839475C[entry - 0xAB].value << 3;
        else if (g_state_02000000.previous_second == 9)
            amount = data_0839475C[entry - 0xAB].value << 1;
        return amount;
    }

    index = entry > 0x55 ? entry - 0x55 : entry;
    amount = g_table_08528F34[index].value << 1;
    if (g_table_08528F34[index].type == g_state_02000000.previous_first)
        amount = g_table_08528F34[index].value << 2;
    else if (g_table_08528F34[index].type == g_state_02000000.previous_second)
        amount = g_table_08528F34[index].value;
    return amount;
}
