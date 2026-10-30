#include "ffta.h"

typedef struct {
    u8 amount;
    u8 unknown_01[3];
} SpecialEntry080CC218;

typedef struct {
    u8 amount;
    u8 unknown_01[13];
    u8 type;
    u8 unknown_0F;
} Entry080CC218;

typedef struct {
    u8 unknown_00[0x2E5E];
    u8 first_type;
    u8 second_type;
} State080CC218;

extern const SpecialEntry080CC218 data_0839475C[];
extern const Entry080CC218 g_table_08528F34[];
extern State080CC218 g_state_02000000;

/* Complete [0x080CC218, 0x080CC2B4): 156 bytes, 60 instructions. */
u8 func_080CC218(u16 identifier)
{
    u8 amount;

    if (identifier > 0xAA) {
        u32 base = data_0839475C[identifier - 0xAB].amount;

        amount = base * 4;
        if (g_state_02000000.first_type == 9)
            amount = base * 8;
        else if (g_state_02000000.second_type == 9)
            amount = base * 2;
    } else {
        u16 index = identifier > 0x55 ? identifier - 0x55 : identifier;
        const Entry080CC218 *entry = &g_table_08528F34[index];
        u32 type;

        amount = entry->amount * 2;
        type = entry->type;
        if (type == g_state_02000000.first_type)
            amount = entry->amount * 4;
        else if (type == g_state_02000000.second_type)
            amount = entry->amount;
    }
    return amount;
}
