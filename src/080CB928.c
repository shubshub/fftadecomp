typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Object {
    u8 unknown_00[4];
    u8 index;
};

struct NameEntry {
    u8 unknown_00[0xB];
    u8 name;
};

extern const u8 data_08417F88[];
extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(void *object);
extern u32 func_080C92F0(void *object, u32 selector);
extern const u8 *func_080071A8(const u8 *table, u16 index);

/* Target: 080CB928..080CB968, 64 bytes. */
const u8 *func_080CB928(struct Object *object)
{
    const u8 *names = data_08417F88;
    u32 name;

    if (func_080C817C(object))
        name = ((const struct NameEntry *)g_table_085273D8[object->index])->name;
    else
        name = func_080C92F0(object, 9);

    return func_080071A8(names, (u8)name);
}
