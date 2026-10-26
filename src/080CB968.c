typedef unsigned char u8;

struct Table;

extern const struct Table data_08417F88;
extern void *func_080071A8(const struct Table *table, u8 key);

/* Target: 080CB968..080CB980, 24 bytes. */
void *func_080CB968(u8 key)
{
    return func_080071A8(&data_08417F88, key);
}
