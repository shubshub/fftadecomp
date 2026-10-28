#include "ffta.h"

extern u16 data_04000134;
extern u8 data_03002B60;
extern u8 data_030028A0;
extern u8 data_03002B44;
extern u8 data_03002884;

/* 0x08004D68 - 166 bytes, including literal pools. */
u8 func_08004D68(void)
{
    u16 *port = &data_04000134;
    u8 input = *port;

    if (data_03002B60 > 70)
        return 0;
    if (data_030028A0 & 8) {
        input &= 2;
        if (data_03002B44 & 1)
            *port = 0x8055;
        else
            *port = 0x8050;
    } else {
        input &= 5;
        if (data_03002B44 & 1)
            *port = 0x8022;
        else
            *port = 0x8020;
    }
    if (input == data_03002884) {
        data_03002B60++;
    } else {
        data_03002884 = input;
        data_03002B60 = 0;
    }
    data_03002B44 ^= 1;
    return 1;
}
