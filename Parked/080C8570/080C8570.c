#include "ffta.h"

typedef struct CategoryRecord {
    u8 value_00[2];
    u8 unknown_02[2];
    u8 category;
    u8 redirect;
    u8 value_06;
    u8 value_07[2];
    u8 value_09[2];
    u8 value_0B_low : 4;
    u8 value_0B_high : 4;
    u8 value_0C;
    u8 value_0D;
    u8 value_0E;
    u8 value_0F;
    u8 value_10;
    u8 value_11;
    u8 unknown_12_low : 3;
    u8 value_12_middle : 3;
    u8 value_12_high : 2;
    u8 value_13_low : 1;
    u8 value_13_middle : 3;
    u8 value_13_high : 3;
    u8 value_13_top : 1;
    u8 value_14_low : 2;
    u8 value_14_middle : 3;
    u8 value_14_high : 3;
    u8 value_15_low : 3;
    u8 unknown_15_high : 5;
    u8 value_16;
    u8 value_17;
    u8 value_18;
    u8 value_19;
    u8 value_1A;
    u8 value_1B_low : 4;
    u8 value_1B_high : 4;
    u8 value_1C;
    u8 value_1D;
    u8 value_1E_low : 4;
    u8 value_1E_high : 4;
    u8 value_1F;
    u8 value_20;
    u8 value_21;
    u8 value_22;
    u8 value_23;
    u8 value_24;
    u8 value_25;
    u8 value_26;
    u8 unknown_27;
    u8 value_28;
    u8 value_29;
    u8 value_2A;
    u8 value_2B_low : 4;
    u8 value_2B_high : 4;
    u8 value_2C;
    u8 value_2D;
    u8 value_2E;
    u8 value_2F;
    u8 value_30;
    u8 value_31;
    u8 unknown_32[2];
} CategoryRecord;

extern const CategoryRecord g_table_08521A14[];

u32 func_080C8570(u8 first, u8 second, u8 selector)
{
    u32 offset = first * sizeof(CategoryRecord);
    const u8 *table = (const u8 *)g_table_08521A14;
    const CategoryRecord *record = (const CategoryRecord *)(table + offset);

    while (1) {
        switch (selector) {
        case 0:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_00[0] | (record->value_00[1] << 8);
            break;
        case 1:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->category;
            break;
        case 2:
            return record->redirect;
        case 3:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_06;
            break;
        case 4:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_07[0] | (record->value_07[1] << 8);
            break;
        case 5:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_09[0] | (record->value_09[1] << 8);
            break;
        case 6:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0B_low;
            break;
        case 7:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0B_high;
            break;
        case 8:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0C;
            break;
        case 9:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0D;
            break;
        case 10:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0E;
            break;
        case 11:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_0F;
            break;
        case 12:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_10;
            break;
        case 13:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_11;
            break;
        case 14:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_12_middle;
            break;
        case 15:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_12_high | (record->value_13_low << 2);
            break;
        case 16:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_13_middle;
            break;
        case 17:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_13_high;
            break;
        case 18:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_13_top | (record->value_14_low << 1);
            break;
        case 19:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_14_middle;
            break;
        case 20:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_14_high;
            break;
        case 21:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_15_low;
            break;
        case 22:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_16;
            break;
        case 23:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_17;
            break;
        case 24:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_18;
            break;
        case 25:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_19;
            break;
        case 26:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_1A | (record->value_1B_low << 8);
            break;
        case 27:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_1B_high | (record->value_1C << 4);
            break;
        case 28:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_1D | (record->value_1E_low << 8);
            break;
        case 29:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_1E_high | (record->value_1F << 4);
            break;
        case 30:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_28;
            break;
        case 31:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_29;
            break;
        case 32:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2A;
            break;
        case 34:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2B_low;
            break;
        case 35:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2B_high;
            break;
        case 33:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2C;
            break;
        case 36:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2D;
            break;
        case 37:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2E;
            break;
        case 38:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_2F;
            break;
        case 39:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_30;
            break;
        case 40:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_31;
            break;
        case 41:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_20;
            break;
        case 42:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_21;
            break;
        case 43:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_22;
            break;
        case 44:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_23;
            break;
        case 45:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_24;
            break;
        case 46:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_25;
            break;
        case 47:
            if (record->redirect == 0xFF)
                record = (const CategoryRecord *)(table + second * sizeof(CategoryRecord));
            else if (record->redirect != 0)
                record = (const CategoryRecord *)(table + record->redirect * sizeof(CategoryRecord));
            else
                return record->value_26;
            break;
        }
    }
}
