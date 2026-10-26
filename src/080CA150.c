#include "ffta.h"

typedef struct {
    u32 value;
} __attribute__((packed)) PackedKey;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

u32 func_080CA150(const PackedKey *key)
{
    u32 i;

    for (i = 0; i < 725; i++) {
        if (g_table_085680DC[i] ==
            key->value)
            return i;
    }
    for (i = 0; i < 107; i++) {
        if (g_table_085516D0[i] ==
            key->value)
            return i | 0x8000;
    }
    return 0;
}
