#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 value_06;
} State080316D0;

extern u8 data_030027A4;
extern State080316D0 data_03000EA0;
extern u16 data_03000E50;
extern u16 data_04000200;

extern void func_08003398(void);

/* Complete target [0x080316D0, 0x08031708), 56 bytes:
 * 00b50849ff200870074ad18807480840d0800749088007490880d1f755fe01bc0047
 * 0000a4270003a00e0003fbff0000500e000300020004
 */
void func_080316D0(void)
{
    u16 value;

    data_030027A4 = 0xFF;
    value = data_03000EA0.value_06 & 0xFFFB;
    data_03000EA0.value_06 = value;
    data_03000E50 = value;
    data_04000200 = value;
    func_08003398();
}
