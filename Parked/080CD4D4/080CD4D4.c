typedef unsigned char u8;

typedef struct {
    u8 unknown_00[6];
    u8 kind;
    u8 unknown_07[0x33];
    u8 index;
} Object;

typedef struct {
    u8 unknown_00[4];
    u8 value;
    u8 unknown_05[3];
} Entry;

extern const Entry *const g_table_0851BA84[];

unsigned int func_080CD4D4(const Object *object)
{
    int has_index;
    u8 kind;
    u8 index;

    if (object)
        has_index = object->index;
    else
        has_index = 0;
    if (!has_index)
        return 0;
    kind = object->kind;
    index = object->index;
    return g_table_0851BA84[kind][index].value;
}
