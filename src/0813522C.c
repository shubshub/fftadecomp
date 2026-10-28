#include "ffta.h"

/* 0x0813522C..0x081352CC: 160 bytes, including the literal pools. */
typedef struct {
    u8 unknown_00;
    u8 linked_index;
    u8 unknown_02[14];
} SelectionEntry;

typedef struct {
    u8 unknown_00[0x3C33];
    u8 count;
    u16 ids[0];
} SelectionState;

extern SelectionState g_state_02000000;
extern const SelectionEntry g_table_08528F34[];
extern u8 func_081343C8(void *, void *, u16, u8, int, s16,
                        const void *, const SelectionEntry *);

u8 func_0813522C(void *source, void *target, u16 entry, u8 mode,
                 u16 option, const void *options)
{
    int i;

    for (i = 0; i < g_state_02000000.count; ++i) {
        if (func_081343C8(source, target, entry, mode, 0, (s16)option,
                         options,
                         &g_table_08528F34[g_table_08528F34[
                             g_state_02000000.ids[i]].linked_index]))
            return i + 1;
    }
    return 0;
}
