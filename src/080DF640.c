// Target 0x080DF640, 282 bytes, including a 23-entry and a 5-entry jump table:
// 70b50906 0e0efdf7 17ff051c 0321e8f7 29fc041c 2404240c 281c0421 e8f722fc
// 0004030c 8d225200 601e1628 68d88000 01494018 00688746 (jump tables, cases)
// 002e04d0 301c111c 61f012ff 02e0101c 61f0e6fe 70bc01bc 0047
#include "ffta.h"

extern void *func_080DD478(const void *);
extern s32 func_080C7EA4(const void *, u32);
extern void func_08141570(s32, u16);
extern void func_08141520(u16);

void func_080DF640(void *actor, u8 player)
{
    void *unit = func_080DD478(actor);
    u16 first = func_080C7EA4(unit, 3);
    u16 second = func_080C7EA4(unit, 4);
    u16 sound = 0x11A;

    switch (first) {
    case 1:
        sound = 0x75;
        switch (second) {
        case 0x6D: case 0x6E: case 0x6F:
            sound = 0x26C;
            break;
        }
        break;
    case 2:
        sound = 0x76;
        break;
    case 5:
        sound = 0x78;
        break;
    case 6: case 8: case 9: case 15: case 17:
        sound = 0x92;
        break;
    case 3: case 20:
        sound = 0x77;
        break;
    case 7: case 11: case 12: case 13: case 14: case 16:
        sound = 0x7A;
        break;
    case 10: case 18:
        sound = 0x93;
        break;
    case 21:
        switch (second) {
        case 0x62: case 0x65:
            sound = 0x7A;
            break;
        case 0x61:
            sound = 0x93;
            break;
        case 0x63:
            sound = 0x26C;
            break;
        case 0x64:
            sound = 0x11A;
            break;
        }
        break;
    case 4: case 22:
        sound = 0x79;
        break;
    case 23:
        switch (second) {
        case 0x70: case 0x71: case 0x72: case 0x73:
            sound = 0x75;
            break;
        }
        break;
    case 19:
        sound = 0x75;
        break;
    }
    if (player)
        func_08141570(player, sound);
    else
        func_08141520(sound);
}
