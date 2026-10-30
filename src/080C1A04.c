#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 lower : 4;
    u8 upper : 4;
} Nibbles080C1A04;

typedef struct {
    u8 unknown_00[0x54D2];
    Nibbles080C1A04 fields[2];
    u8 unknown_54D4[8];
    u16 values[2];
} State080C1A04;

extern State080C1A04 data_020101F8;

/* Complete [0x080C1A04, 0x080C1A78): 116 bytes, 46 instructions. */
void func_080C1A04(u8 slot, u16 value, u8 lower, u8 upper)
{
    if (slot == 0) {
        data_020101F8.fields[0].lower = lower;
        data_020101F8.fields[0].upper = upper;
        data_020101F8.values[0] = value;
    } else {
        data_020101F8.fields[1].lower = lower;
        data_020101F8.fields[1].upper = upper;
        data_020101F8.values[1] = value;
    }
}
