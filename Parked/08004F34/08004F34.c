#include "ffta.h"

// Complete target [0x08004F34, 0x08004FF4): 192 bytes, 85 instructions,
// four literal words.

typedef struct {
    u16 unknown_00[2];
    u32 payload[4];
} Packet08004F34;

typedef struct {
    u8 unknown_00[2];
    u8 field_02;
    u8 field_03;
    u8 unknown_04[0x4C];
    Packet08004F34 *packets[2];
} State08004F34;

extern State08004F34 data_030028A0;
typedef u32 (*ReadyProbe08004F34)(void);
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 func_08004F34(u32 (*destination)[4])
{
    u8 ready[4];
    u32 zero;
    s32 i;
    u32 j;
    u32 sum;

    *(u32 *)ready = ((ReadyProbe08004F34)0x03002B70)();
    data_030028A0.field_03 = 0;
    for (i = 0; i < 2; i++) {
        sum = 0;
        for (j = 0; j < 10; j++)
            sum += ((const u16 *)data_030028A0.packets[i])[j];
        if (ready[i] != 0 && (s16)sum == -1) {
            func_0814186C(data_030028A0.packets[i]->payload, destination[i], 0x04000004);
            data_030028A0.field_03 |= 1 << i;
        }
        zero = 0;
        func_0814186C(&zero, data_030028A0.packets[i]->payload, 0x05000004);
    }
    data_030028A0.field_02 |= data_030028A0.field_03;
    return data_030028A0.field_03;
}
