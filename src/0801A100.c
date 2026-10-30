#include "ffta.h"

typedef struct {
    u16 index;
    u16 field_02;
    u8 unknown_04[0xC];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
    u8 unknown_14[0x14];
    u8 field_28;
    u8 field_29;
} State0801A100;

extern State0801A100 data_02007F10;
extern u8 func_0801DB98(s16 index);
extern void func_0801DB2C(u16 index);

/* Target [0x0801A100, 0x0801A15C), 92 complete bytes:
 * 30b50004000c09060d0e002801d1ff2002e001380004000c0e4c
 * 2080ff2805d00004001403f038fd0006000e6082094c608aff28
 * 01d003f0f9fc0020207406496180211c29310d700139087030bc
 * 01bc00470000107f0002ffff0000
 */
void func_0801A100(u16 index, u8 value)
{
    if (index == 0)
        index = 0xFF;
    else
        index--;
    data_02007F10.index = index;
    if (index == 0xFF)
        data_02007F10.selector = 0xFF;
    else
        data_02007F10.selector = func_0801DB98((s16)index);
    if (data_02007F10.selector != 0xFF)
        func_0801DB2C(data_02007F10.selector);
    data_02007F10.enabled = 0;
    data_02007F10.field_02 = 0xFFFF;
    data_02007F10.field_29 = value;
    data_02007F10.field_28 = 0;
}
