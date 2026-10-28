typedef unsigned char u8;

struct TableEntry;

extern u8 func_080C8570(u8 first, u8 second, int key);
extern struct TableEntry *const g_table_0851BA84[];

struct TableEntry *func_080CD428(u8 id, u8 index, u8 *first_output, u8 *second_output)
{
    u8 first = func_080C8570(id, id, 0x25);
    u8 second = func_080C8570(id, id, 0x26);

    if (first_output)
        *first_output = first;
    if (second_output)
        *second_output = second;

    return g_table_0851BA84[index];
}
