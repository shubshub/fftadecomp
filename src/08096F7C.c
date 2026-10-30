#include "ffta.h"

extern u8 data_0200F4C0[];
extern u32 func_08092390(void *camera);

/* Complete target [0x08096F7C, 0x08096F8C): 16 bytes, 5 instructions. */
u32 func_08096F7C(void)
{
    return func_08092390(data_0200F4C0);
}
