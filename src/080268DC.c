#include "ffta.h"

/* Unit template slot lookup, 0x080268DC..0x080269D8 (252 bytes). */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06[2];
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

extern UnitTemplate data_02002E78[];

u8 func_080268DC(u16 kind)
{
    u8 slots[3];
    s32 i;

    slots[0] = slots[1] = slots[2] = 0xFF;

    switch (kind) {
    case 0xCA:
        slots[0] = 0;
        slots[1] = 1;
        break;
    case 0xCB:
        slots[0] = 2;
        slots[1] = 3;
        slots[2] = 4;
        break;
    case 0xCC:
        slots[0] = 5;
        slots[1] = 6;
        break;
    case 0xCD:
        slots[0] = 7;
        slots[1] = 8;
        slots[2] = 9;
        break;
    case 0xCE:
        slots[0] = 10;
        slots[1] = 11;
        break;
    case 0xCF:
        slots[0] = 12;
        slots[1] = 13;
        break;
    case 0xD0:
        slots[0] = 14;
        slots[1] = 15;
        break;
    case 0xD1:
        slots[0] = 16;
        slots[1] = 17;
        break;
    case 0xD2:
        slots[0] = 18;
        slots[1] = 19;
        break;
    }

    for (i = 0; i <= 2; i++) {
        if (slots[i] == 0xFF)
            return 0;
        if (data_02002E78[slots[i]].name != 0)
            return 1;
    }
    return 0;
}
