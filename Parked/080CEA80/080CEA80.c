#include "ffta.h"

typedef struct {
    u8 unknown_00[0x98];
    u32 primary_random;
    u32 secondary_random;
    u16 index;
    u16 override_index;
    u8 unknown_A4[2];
    u8 values[2];
    u8 record_indices[3];
} SelectionState;

extern SelectionState g_state_020020D0;
extern const u16 g_count_0854D1B4;
extern const u8 g_table_085273D8[][14];

u32 func_08002804(void);
void func_080C9574(u16 bitIndex, u16 enabled);
s32 func_080C7EA4(const void *object, u32 selector);
void func_080C9E00(void *object);

void func_080CEA80(u8 flag)
{
    u32 random_value = (s16)func_08002804();

    random_value |= func_08002804() << 16;
    if (flag) {
        u8 *record;
        s32 remaining;

        g_state_020020D0.primary_random = random_value;
        if (func_08002804() & 1)
            func_080C9574(0x5A5, 1);
        record = (u8 *)0x02000080;
        remaining = g_count_0854D1B4;
        while (remaining != 0) {
            if (g_table_085273D8[func_080C7EA4(record, 1)][0] == 0)
                func_080C9E00(record);
            remaining--;
            record += 0x108;
        }
    } else {
        g_state_020020D0.secondary_random = random_value;
        if (func_08002804() & 1)
            func_080C9574(0x5A6, 1);
    }
}
