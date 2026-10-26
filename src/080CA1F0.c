typedef unsigned char u8;
typedef unsigned int u32;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

struct PackedKey {
    u32 value;
} __attribute__((packed));

/* Target: 080CA1F0..080CA22C, 60 bytes. */
u32 func_080CA1F0(const struct PackedKey *key)
{
    u32 index = key->value;

    if (index > 0x7FFF)
        return g_table_085516D0[index & 0x7FFF];
    return g_table_085680DC[index];
}
