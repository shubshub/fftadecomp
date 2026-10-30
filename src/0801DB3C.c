#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 field_10;
    u8 unknown_11;
    u16 field_12;
} State0801DB3C;

extern State0801DB3C data_02007F10;
extern u16 data_03003860;
extern u16 data_02008390[];
extern void func_08000D48(u32 channel, const void *source,
                          void *destination, u32 control);

/* Target [0x0801DB3C, 0x0801DB78), 60 complete bytes:
 * 10b50a4c608aff280cd0094a0949088810800231a022d204074b0220e3f7f6f8
 * 0120207410bc01bc00470000107f0002603800039083000201004020
 */
void func_0801DB3C(void)
{
    if (data_02007F10.field_12 != 0xFF) {
        data_03003860 = data_02008390[0];
        func_08000D48(2, data_02008390 + 1, (void *)0x05000000, 0x20400001);
        data_02007F10.field_10 = 1;
    }
}
