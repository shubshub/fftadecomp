#include "ffta.h"

/* 0x080268DC..0x080269D8: 252 bytes.
 * 10b581b00004000c6c466b466a46ff2191700121494259702170ca3808284ed88000024940180068874600000c690208306902083a6902084a69020854690208646902086e69020878690208826902089069020869460020087001202ee0694602200870032048700420887027e0694605200870062021e069460720087008204870092088701ae069460a2008700b2014e069460c2008700d200fe069460e2008700f200ae0694610200870112005e001201de06946122008701320487000230d4c6846c1180878ff2810d0000100190278417809021143827812040a43c078000610430028e3d10133022be9dd002001b010bc02bc0847782e0002
 */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04[12];
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
