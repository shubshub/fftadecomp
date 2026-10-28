#include "ffta.h"

/* 0x0814164C..0x0814168C: 64 bytes. */
extern u8 data_020084D8[];
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern void func_08145990(void *);

void func_0814164C(u16 channel)
{
    void *sound = 0;

    if (data_020084D8[0] & 2) {
        switch (channel) {
        case 1:
            sound = data_0200F2E0;
            break;
        case 2:
            sound = data_0200F320;
            break;
        }
        if (sound != 0)
            func_08145990(sound);
    }
}
