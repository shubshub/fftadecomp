/* 0x08006AB8 - 34 bytes
 * Target: 00b5 021c 0b1c d078 ff28 08d0 9168 8000 4018 0360 d178 d068
 *         4018 0021 0170 01bc 0047
 */

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

void func_08006AB8(List *runner, u32 entry)
{
    if (runner->field_03 != 0xFF) {
        runner->words[runner->field_03] = entry;
        runner->flags[runner->field_03] = 0;
    }
}
