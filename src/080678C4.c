#include "ffta.h"

typedef union {
    u16 *halfwords[0];
    u8 *bytes[0];
    u16 values[0][2];
} Entry080678C4;

typedef struct {
    u8 unknown_00[0x424];
    Entry080678C4 entries;
} Table080678C4;

typedef struct {
    Table080678C4 *table;
    u8 unknown_04[4];
    u8 mode;
} State080678C4;

typedef struct {
    u8 unknown_00[2];
    u8 category;
    u8 unknown_03[13];
} Category080678C4;

extern const Category080678C4 g_table_08521214[];
extern void *func_08005B28(u32 size);
extern void func_08005B40(void *buffer);
extern void func_080CB9B0(void *buffer, u32 category);
extern void func_080CB980(void *buffer, u32 id);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x080678C4, 0x08067994), 208 bytes.
 * f0b5051c1204170c0e1c287a042811d0042802dc032805d052e0052818d0062834d0
 * 4de080209ef71df9041c122164f05df83ce080209ef715f9041c2868b900024a8018
 * 4018006801882de02404000080209ef707f9041c2868b900084a8018401800680078
 * 000106494118887800280ad0c5225200101c89784018011c13e02404000014125208
 * 00210de080209ef7e9f8041c2868b9000b4a8018401800880a49552800d90131201c
 * 64f007f8201c311c4022d9f078ff201c9ef7dff88036301cf0bc02bc084724040000
 * 89010000
 */
u8 *func_080678C4(State080678C4 *state, void *output, u16 index)
{
    u8 *destination = output;
    void *buffer;

    switch (state->mode) {
    case 3:
        buffer = func_08005B28(0x80);
        func_080CB9B0(buffer, 0x12);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    case 4:
        buffer = func_08005B28(0x80);
        func_080CB980(buffer, *state->table->entries.halfwords[index]);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    case 5:
        {
            const Category080678C4 *entry;
            u16 id;

            buffer = func_08005B28(0x80);
            entry = &g_table_08521214[state->table->entries.bytes[index][0]];
            id = entry->category ? 0x18A + entry->category : 0;
            func_080CB980(buffer, id);
            func_0814186C(buffer, destination, 0x40);
            func_08005B40(buffer);
            destination += 0x80;
        }
        break;
    case 6:
        buffer = func_08005B28(0x80);
        func_080CB980(buffer, state->table->entries.values[index][0] > 0x55 ? 0x18A : 0x189);
        func_0814186C(buffer, destination, 0x40);
        func_08005B40(buffer);
        destination += 0x80;
        break;
    }
    return destination;
}
