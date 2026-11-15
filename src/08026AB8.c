#include "ffta.h"

/* Only fields reached by this scan and the defining range helper are named. */
typedef struct {
    u8 unknown_00[6];
    u8 table_index;
    u8 unknown_07;
    u8 entity;
    u8 unknown_09[0x2C];
    u8 override_1;
    u8 override_2;
    u8 override_3;
} Record080CCE60;

typedef struct {
    u8 unknown_00[0x18];
    Record080CCE60 *record;
} Context08026AB8;

typedef struct {
    u16 identifier;
    u8 kind;
    u8 unknown_03[5];
} Entry08026AB8;

extern Context08026AB8 *data_0200F438;
const u8 *func_080CCE60(Record080CCE60 *record, u8 mode, u8 *first, u8 *second);
u8 func_080CD560(const void *object, u8 index);
u32 func_080CCD50(u16 index, u8 selector);

u8 func_08026AB8(void *context)
{
    int enabled = 0;
    int category;
    u8 first;
    u8 last;

    for (category = 0; category < 3; category++) {
        switch (category) {
        case 0:
            enabled = data_0200F438->record->override_1;
            break;
        case 1:
            enabled = data_0200F438->record->override_2;
            break;
        case 2:
            enabled = data_0200F438->record->override_3;
            break;
        }

        if (enabled != 0) {
            const u8 *table = func_080CCE60(data_0200F438->record,
                                          category + 1, &first, &last);
            int index;

            for (index = first; index <= last; index++) {
                const Entry08026AB8 *entry =
                    (const Entry08026AB8 *)(table + 4) + index;
                if ((entry->kind == 1 || entry->kind == 4) &&
                    func_080CD560(data_0200F438->record, index) &&
                    func_080CCD50(entry->identifier, 0x13))
                    return 1;
            }
        }
    }
    return 0;
}
