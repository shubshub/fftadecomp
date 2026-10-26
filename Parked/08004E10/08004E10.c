#include "ffta.h"

typedef struct {
    u8 mode;
    u8 stage;
    u8 unknown_02;
    u8 result;
    u8 unknown_04[7];
    u8 counter;
    u8 unknown_0c[8];
    s32 value;
} SerialState08004E10;

typedef struct {
    u8 unknown_00[6];
    u16 interrupts;
} InterruptState08004E10;

extern SerialState08004E10 data_030028A0;
extern InterruptState08004E10 data_03000EA0;
extern void func_08004F34(void *);
extern void func_08004EC8(void *);

/* 0x08004E10..0x08004EC8: 184 bytes, 71 instructions. */
u8 func_08004E10(void *send, void *receive)
{
    switch (data_030028A0.stage) {
    case 0:
        {
            u8 *serial = (u8 *)0x04000128;
            u32 control = serial[0];

            if (control & 8) {
                u32 remote = *(u8 *)0x04000134;

                if (!(remote & 2))
                    break;
                if ((remote & 5) == 1 && data_030028A0.value == -1) {
                    data_03000EA0.interrupts =
                        (data_03000EA0.interrupts & 0xff7f) | 0x40;
                    *(u16 *)0x04000200 = data_03000EA0.interrupts;
                    serial[1] &= ~0x40;
                    *(u16 *)0x04000202 = 0xc0;
                    *(u32 *)0x0400010c = 0x00c0b1fc;
                    data_030028A0.mode = 8;
                    serial[0] = control | 0x80;
                }
            }
        }
    case 1:
        func_08004F34(receive);
        func_08004EC8(send);
        data_030028A0.stage = 1;
        break;
    }
    data_030028A0.counter++;
    return data_030028A0.result;
}
