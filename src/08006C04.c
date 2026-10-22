/* 0x08006C04 - 32 bytes
 * Target: 00b5 021c d078 ff28 08d0 011c 9068 8900 0918 0868 8022 1206
 *         1043 0860 01bc 0047
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

void func_08006C04(List *runner)
{
    if (runner->field_03 != 0xFF) {
        runner->words[runner->field_03] |= 0x80000000;
    }
}
