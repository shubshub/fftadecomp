#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 value_06;
} State08089C4C;

extern u8 data_030027A4;
extern State08089C4C data_03000EA0;
extern u16 data_03000E50;
extern u16 data_04000200;

extern void func_08003398(void);

/* 08089C4C..08089C84: 00b50849ff200870074ad18807480840d080074908800749088079f797fb01bc00470000a4270003a00e0003fbff0000500e000300020004. */
void func_08089C4C(void)
{
    u16 value;

    data_030027A4 = 0xFF;
    value = data_03000EA0.value_06 & 0xFFFB;
    data_03000EA0.value_06 = value;
    data_03000E50 = value;
    data_04000200 = value;
    func_08003398();
}
