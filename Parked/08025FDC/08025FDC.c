// 0x08025FDC - 260 bytes: 0x08025FDC..0x080260E0 including the literal pool
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x35];
    u8 override_1;
    u8 override_2;
} Record080CCE60;

typedef struct {
    u8 unknown_00[0x18];
    Record080CCE60 *record;
} Context08025FDC;

typedef struct {
    u16 identifier;
    u8 kind;
    u8 unknown_03[5];
} Entry08025FDC;

extern Context08025FDC *data_0200F438;
const u8 *func_080CCE60(Record080CCE60 *record, u8 mode, u8 *first, u8 *second);
u8 func_080CD560(const void *object, u8 index);
u32 func_080CCD50(u16 index, u8 selector);
void *func_08096D7C(void);
s32 func_080970E8(void *context, Record080CCE60 *record);

u32 func_08025FDC(u8 mode)
{
    const u8 *table = 0;
    u8 override = 0;
    u8 first;
    u8 last;
    int index;

    switch (mode) {
    case 6:
        table = func_080CCE60(data_0200F438->record, 1, &first, &last);
        override = data_0200F438->record->override_1;
        break;
    case 7:
        table = func_080CCE60(data_0200F438->record, 2, &first, &last);
        override = data_0200F438->record->override_2;
        break;
    }

    if (func_080970E8(func_08096D7C(), data_0200F438->record)) {
        for (index = first; index <= last; index++) {
            const Entry08025FDC *entry =
                (const Entry08025FDC *)(table + 4) + index;
            if ((entry->kind == 1 || entry->kind == 4) &&
                func_080CD560(data_0200F438->record, index) &&
                func_080CCD50(entry->identifier, 0x15))
                return 1;
        }
    } else {
        if (override == 1)
            return 1;
        for (index = first; index <= last; index++) {
            const Entry08025FDC *entry =
                (const Entry08025FDC *)table + index;
            if ((entry->unknown_03[3] == 1 || entry->unknown_03[3] == 4) &&
                func_080CD560(data_0200F438->record, index))
                return 1;
        }
    }
    return 0;
}
