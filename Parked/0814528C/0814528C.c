#include "ffta.h"

struct AudioStateTableEntry {
    void *state;
    u32 unknown_04;
    u32 unknown_08;
};

struct AudioDataTableEntry {
    const void *header;
    u16 state_index;
    u16 unknown_06;
};

struct AudioStateHeader {
    const void *header;
};

extern const struct AudioStateTableEntry g_table_0814BB24[];
extern const struct AudioDataTableEntry g_table_0814BB48[];
void func_08145990(void *context);

/* 0x0814528C - 52 bytes.
 * Target: 00b50004094a0a49400b401883885900c918890089180a6811680068814202d1101c00f06ffb01bc0047000024bb140848bb1408
 */
void func_0814528C(u16 index)
{
    const struct AudioDataTableEntry *entry = &g_table_0814BB48[index];
    struct AudioStateHeader *state = g_table_0814BB24[entry->state_index].state;

    if (state->header == entry->header)
        func_08145990(state);
}
