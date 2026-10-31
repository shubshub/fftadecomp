#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0A];
    u8 byte_0A;
    u8 unknown_0B[0x89];
    const u32 *entries;
} Record08028824;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[0x47B];
    u8 bytes_480[0];
} State08028824;

typedef struct {
    u8 unknown_00[2];
    u16 value_02;
    u8 unknown_04[4];
} TableRecord08028824;

typedef struct {
    u8 unknown_00[2];
    u8 byte_02;
    u8 byte_03;
} EncodedRecord08028824;

extern State08028824 *data_0200F438;
extern const TableRecord08028824 *const g_table_0851BA84[];
extern const u16 data_0852A13E[];
extern const EncodedRecord08028824 data_08527244[];
extern const u16 data_0852A212[];

s32 func_080CA7A4(u16 entry, u8 selector);

/* Target: complete [0x08028824, 0x0802896E), 330 bytes. */
u16 func_08028824(const Record08028824 *record, u16 index)
{
    u16 result = 0;

    switch (data_0200F438->mode) {
    case 6:
    case 7:
    case 8:
    case 15:
        result = g_table_0851BA84[record->byte_0A]
                    [record->entries[(s16)index]].value_02 + 1;
        break;
    case 1:
    case 4:
    case 10:
        result = data_0852A13E[record->entries[(s16)index]] + 1;
        break;
    case 5:
        switch (data_0200F438->bytes_480[(s16)index]) {
        case 12:
        case 16:
        case 17:
            result = data_0852A13E[record->entries[(s16)index]] + 1;
            break;
        default:
        {
            const EncodedRecord08028824 *entry =
                &data_08527244[record->entries[(s16)index]];

            result = (entry->byte_02 | entry->byte_03 << 8) + 1;
            break;
        }
        }
        break;
    case 3:
        result = data_0852A212[record->entries[(s16)index]] + 1;
        break;
    case 13:
    case 14:
        result = func_080CA7A4((u16)record->entries[(s16)index], 1) + 1;
        break;
    case 2:
    case 9:
    case 11:
    case 12:
    case 16:
    case 17:
    default:
        break;
    }
    return result;
}
