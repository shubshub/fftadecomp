typedef unsigned char u8;

struct Entry;

struct Source {
    unsigned int index;
    u8 unknown_04[0x102];
    u8 kind;
};

extern struct Entry data_02001F1C;
extern struct Entry *const g_table_085680DC[];
extern struct Entry *const g_table_085516D0[];

/* Target: 080CA1BC..080CA1F0, 52 bytes. */
struct Entry *func_080CA1BC(const struct Source *source)
{
    unsigned int index = source->index;

    switch (source->kind) {
    case 0:
        return g_table_085680DC[index];
    case 1:
        return g_table_085516D0[index];
    default:
        return &data_02001F1C;
    }

}
