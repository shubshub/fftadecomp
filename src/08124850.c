#include "ffta.h"

// Complete target: 0x08124850..0x08124972, 290 bytes, 130 reached instructions.

typedef struct {
    u8 unknown_00[4];
    u8 kind;
    u8 unknown_05[2];
    u8 state;
    u8 unknown_08[0x10];
    u16 current;
    u16 maximum;
} Record08124850;

typedef struct {
    Record08124850 *record;
} Object08124850;

extern void *func_08096D7C(void);
extern s32 func_08099CDC(void *context, Object08124850 **objects);
extern u8 func_080C8280(Record08124850 *record);
extern u8 func_080CD92C(Record08124850 *record);
extern u8 func_080CDADC(Record08124850 *record);
extern u8 func_080CDA04(Record08124850 *record);
extern u8 func_080CDB24(Record08124850 *record);
extern u8 func_080C8240(Record08124850 *record);
extern u8 func_080C8260(Record08124850 *record);
extern u8 func_080C8298(Record08124850 *record);
extern void func_0809A570(Object08124850 *object, u32 action, u32 value);

void func_08124850(u8 mode)
{
    Object08124850 *objects[13];
    s32 count = func_08099CDC(func_08096D7C(), objects);
    s32 i;

    for (i = 0; i < count; i++) {
        Object08124850 *object = objects[i];
        Record08124850 *record = object->record;

        if (func_080C8280(record) ||
            (u16)(record->maximum / 10u) >= record->current ||
            func_080CD92C(record) || func_080CDADC(record) ||
            func_080CDA04(record) || func_080CDB24(record))
            continue;
        if (record->state == 0x31)
            continue;
        if (record->state == 0x32)
            continue;
        if (record->state == 0x45)
            continue;
        if (record->state == 0x46)
            continue;
        if (record->state == 0x47)
            continue;
        if (record->kind == 0x1e || record->kind == 0x39 ||
            record->kind == 0x3a || record->kind == 0x3b ||
            record->kind == 0x3c || record->kind == 0x3d ||
            record->kind == 0x3e || record->kind == 0x3f)
            continue;
        switch (mode) {
        case 0:
            if (!func_080C8240(object->record) && !func_080C8260(object->record) &&
                !func_080C8298(object->record))
                func_0809A570(object, 2, 0);
            break;
        case 1:
            if (func_080C8240(object->record))
                func_0809A570(object, 2, 0);
            break;
        case 2:
            if (func_080C8260(object->record))
                func_0809A570(object, 2, 0);
            break;
        default:
            func_0809A570(object, 2, 0);
            break;
        }
    }
}
