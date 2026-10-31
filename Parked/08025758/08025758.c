/* Complete target [0x08025758,0x080258C4), 364 bytes.
 * 30b5051c09040b0c06490868007901380a1c0e2800d999e080000349401800688746000038f40002
 * 84570208f05702085a58020870580208f0570208f8570208c0570208c0570208c0570208a4580208
 * f0570208a4580208545802088458020884580208c05702080949a87a8000401802681804291c9431
 * 0968801340180068c0001218034910888000401868e0000084ba5108f0675508004a58e0f0675508
 * 106819040c149022d2008018001900780b1c0c2805d00c280cdb11280adc102808db034a281c9430
 * 0168a00044e00000f0675508074a281c943001689813401800688000044940180178407800020843
 * 34e00000f067550844725208281ca0302ee01804291c943109688013401800680021a2f01bfb24e0
 * 1804291c94310968801340180088a5f02ffe1ae0064c1804291c943109688013401800880021a4f0
 * 85ff800000190be080665208064a1804291c9431096880134018006880008018006830bc02bc0847
 * 80665208
 */

#include "ffta.h"

typedef union {
    u32 value;
    u16 id;
    void *object;
} Entry08025758;

typedef struct {
    u8 unknown_00[0x0A];
    u8 kind;
    u8 unknown_0B[0x89];
    Entry08025758 *entries;
    u8 unknown_98[8];
    void *resource;
} Record08025758;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[0x47B];
    u8 subtypes[0];
} State08025758;

typedef struct {
    u16 name;
    u8 unknown_02[6];
} Selection08025758;

typedef struct {
    u8 low;
    u8 high;
    u8 unknown_02[2];
} Encoded08025758;

extern State08025758 *data_0200F438;
extern const Selection08025758 *const g_table_0851BA84[];
extern void *const g_table_085567F0[];
extern void *const g_table_08526680[];
extern const Encoded08025758 data_08527244[];

s32 func_080C7EA4(const void *object, u32 selector);
u32 func_080CB4E0(u32 value);
s32 func_080CA7A4(u16 entry, u8 selector);

void *func_08025758(const Record08025758 *record, u16 index)
{
    switch (data_0200F438->mode) {
    case 6:
    case 7:
    case 8:
    case 15:
        return g_table_085567F0[
            g_table_0851BA84[record->kind]
                [record->entries[(s16)index].value].name];
    case 1:
    case 4:
    case 10:
        return g_table_085567F0[record->entries[(s16)index].value];
    case 5:
        switch (data_0200F438->subtypes[(s16)index]) {
        case 12:
        case 16:
        case 17:
            return g_table_085567F0[record->entries[(s16)index].value];
        default:
        {
            const Encoded08025758 *entry =
                &data_08527244[record->entries[(s16)index].value];

            return g_table_08526680[entry->low | entry->high << 8];
        }
        }
    case 12:
        return record->resource;
    case 2:
        return (void *)func_080C7EA4(record->entries[(s16)index].object, 0);
    case 3:
        return (void *)func_080CB4E0(record->entries[(s16)index].id);
    case 13:
    case 14:
        return g_table_08526680[
            func_080CA7A4(record->entries[(s16)index].id, 0)];
    default:
        return g_table_08526680[record->entries[(s16)index].value];
    }
}
