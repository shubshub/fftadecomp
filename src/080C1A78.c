#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54B0];
    u8 field_54b0;
    u8 field_54b1;
    u8 field_54b2;
    u8 field_54b3;
    u8 unknown_54b4[0xE];
    u16 values[0];
} State080C1A78;

extern State080C1A78 data_020101F8;

/* Complete target: [0x080C1A78, 0x080C1AD4), 92 bytes. */
u16 func_080C1A78(u8 index, u8 *first, u8 *second)
{
    if (index == 0) {
        *first = data_020101F8.field_54b2;
        *second = data_020101F8.field_54b3;
    } else {
        *first = data_020101F8.field_54b0;
        *second = data_020101F8.field_54b1;
    }
    return data_020101F8.values[index];
}
