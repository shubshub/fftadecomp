#include "ffta.h"

/* Complete [0x08025758, 0x080258C4): 364 bytes, including the switch table
 * and literal pools.
 * Target:
 *   30b5051c09040b0c06490868007901380a1c0e2800d999e08000034940180068
 *   8746000038f4000284570208f05702085a58020870580208f0570208f8570208
 *   c0570208c0570208c0570208a4580208f0570208a45802085458020884580208
 *   84580208c05702080949a87a8000401802681804291c94310968801340180068
 *   c0001218034910888000401868e0000084ba5108f0675508004a58e0f0675508
 *   106819040c149022d2008018001900780b1c0c2805d00c280cdb11280adc1028
 *   08db034a281c94300168a00044e00000f0675508074a281c9430016898134018
 *   0068800004494018017840780002084334e00000f067550844725208281ca030
 *   2ee01804291c943109688013401800680021a2f01bfb24e01804291c94310968
 *   801340180088a5f02ffe1ae0064c1804291c943109688013401800880021a4f0
 *   85ff800000190be080665208064a1804291c9431096880134018006880008018
 *   006830bc02bc084780665208
 *
 * Returns the text for entry `index` of a list record, looked up the way the
 * current menu mode stores the entry.  The record and state layout, the mode
 * grouping and the g_table_0851BA84 row walk are those of src/08028824.c;
 * the packed data_08527244 record is that of src/08074A54.c; the member at
 * 0xA0 is the `resource` of the caller src/08025B54.c.
 */
typedef struct {
    u8 unknown_00[0x0A];
    u8 byte_0A;
    u8 unknown_0B[0x89];
    const u32 *entries;
    u8 unknown_98[8];
    void *resource;
} Record08025758;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[0x47B];
    u8 bytes_480[0];
} State08025758;

typedef struct {
    u16 name;
    u16 value;
    u8 unknown_04[4];
} TableRecord08025758;

typedef struct __attribute__((packed)) {
    u16 name;
    u16 value;
} EncodedRecord08025758;

extern State08025758 *data_0200F438;
extern const TableRecord08025758 *const g_table_0851BA84[];
extern const u8 *const g_table_085567F0[];
extern const EncodedRecord08025758 data_08527244[];
extern const u8 *const g_table_08526680[];

extern s32 func_080C7EA4(const void *object, u32 selector);
extern const u8 *func_080CB4E0(u32 identifier);
extern s32 func_080CA7A4(u16 entry, u8 selector);

const u8 *func_08025758(const Record08025758 *record, s16 index)
{
    switch (data_0200F438->mode) {
    case 6:
    case 7:
    case 8:
    case 15:
    {
        /* The row walk of src/08028824.c: the ROM loads the row pointer
           (0x080257C8) before the entry (0x080257D6). */
        const TableRecord08025758 *table = g_table_0851BA84[record->byte_0A];
        table += record->entries[index];
        return g_table_085567F0[table->name];
    }
    case 1:
    case 4:
    case 10:
        return g_table_085567F0[record->entries[index]];
    case 5:
        switch (data_0200F438->bytes_480[index]) {
        case 12:
        case 16:
        case 17:
            return g_table_085567F0[record->entries[index]];
        default:
            /* Spelled as src/08074A54.c reads this table; the ROM scales
               the entry (0x0802583A) before it loads the base (0x0802583C). */
            return g_table_085567F0[(data_08527244 + record->entries[index])->name];
        }
    case 12:
        return record->resource;
    case 2:
        return (const u8 *)func_080C7EA4((const void *)record->entries[index], 0);
    case 3:
        /* Narrowed to u16 before the call: ldrh at 0x0802587C. */
        return func_080CB4E0((u16)record->entries[index]);
    case 13:
    case 14:
        return g_table_08526680[func_080CA7A4(record->entries[index], 0)];
    default:
        return g_table_08526680[record->entries[index]];
    }
}
