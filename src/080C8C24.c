#include "ffta.h"

typedef struct UpdatedRecord {
    u8 unknown_00[4];
    u8 category;
    u8 first;
    u8 unknown_06;
    u8 selector;
    u8 secondary;
    u8 unknown_09[2];
    u8 value_0B;
    u8 values_0C[9];
    u8 unknown_15[0x1F];
    u8 attributes[4];
} UpdatedRecord;

void func_080CB4C0(void *object);
u32 func_080C8570(u8 first, u8 second, u8 selector);
s32 func_080C7EA4(const void *object, u32 selector);
u8 func_080C8228(const void *object);
void func_080CA2E8(void *object);

void func_080C8C24(UpdatedRecord *record, u8 selector)
{
    u8 *attributes;

    func_080CB4C0(record);
    if (record->category == 1)
        record->first = selector;
    record->selector = selector;
    if (record->secondary == selector)
        record->secondary = 0;
    record->value_0B = func_080C8570(record->first, record->selector, 0x0D);
    record->values_0C[0] = 1;
    record->values_0C[1] = func_080C8570(record->first, record->selector, 0x0E);
    record->values_0C[2] = func_080C8570(record->first, record->selector, 0x0F);
    record->values_0C[3] = func_080C8570(record->first, record->selector, 0x10);
    record->values_0C[4] = func_080C8570(record->first, record->selector, 0x11);
    record->values_0C[5] = func_080C8570(record->first, record->selector, 0x12);
    record->values_0C[6] = func_080C8570(record->first, record->selector, 0x13);
    record->values_0C[7] = func_080C8570(record->first, record->selector, 0x14);
    record->values_0C[8] = func_080C8570(record->first, record->selector, 0x15);
    attributes = record->attributes;
    attributes[1] = func_080C8570(record->first, record->selector, 0x0C);
    if (func_080C7EA4(record, 5))
        attributes[2] = func_080C8570(record->secondary, record->secondary, 0x0C);
    if (attributes[1] == attributes[2]) {
        attributes[2] = 0;
        record->secondary = 0;
    }
    if (func_080C8228(record)) {
        attributes[3] = 1;
        if (attributes[2] == 1) {
            attributes[2] = 0;
            record->secondary = 0;
        }
    } else {
        attributes[3] = 0;
    }
    func_080CA2E8(record);
}
