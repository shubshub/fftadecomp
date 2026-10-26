#include "ffta.h"

/* 0x080D47DC..0x080D480C: 48 bytes, 23 instructions. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
} TaskRecord;

extern TaskRecord *func_08005BFC(void *task);

void func_080D47DC(void *task, u16 value)
{
    TaskRecord *record = func_08005BFC(task);
    u16 previous = record->value;
    u16 replacement = (previous & 0xF) | (value << 4);

    if (previous > 0xFF) {
        replacement += 0x100;
    }
    record->value = replacement;
}
