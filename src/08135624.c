typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    u8 unknown_0000[0x3C33];
    u8 count;
    u16 entries[256];
} SelectionState;

typedef struct {
    u8 unknown_00[16];
} SelectionEntry;

extern SelectionState g_state_02000000;
extern const SelectionEntry g_table_08528F34[];
extern u8 func_081343C8(void *source, void *target, u16 value, u8 mode,
                         u32 flags, s16 amount, const void *data,
                         const SelectionEntry *entry);

/* Complete [0x08135624, 0x0813569C): 120 bytes, including literal pools. */
u8 func_08135624(void *source)
{
    u8 result = 0;
    s32 index;

    for (index = 0; index < g_state_02000000.count; index++) {
        result |= func_081343C8(source, 0, 0, 0, 1, 0, 0,
                    &g_table_08528F34[g_state_02000000.entries[index]]);
    }
    return result;
}
