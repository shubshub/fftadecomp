#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 field_02;
    u8 field_03;
    u8 field_04;
    u8 field_05;
    u8 unknown_06[2];
    u32 *words;
    u8 *flags;
} List;

void func_08006B9C(List *runner)
{
    if (runner->field_03 != 0xFF) {
        runner->words[runner->field_03] = 0;
    }
}
