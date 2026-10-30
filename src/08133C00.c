#include "ffta.h"

/* Complete [0x08133C00, 0x08133CC8): 200 bytes, 49 instructions.
 * 00b50004000cfb380d285ad88000024940180068874600001c3c1308543c1308
 * 5a3c1308643c13086a3c1308743c13087a3c1308843c13088c3c1308923c1308
 * 9c3c1308a23c1308ac3c1308b23c1308bc3c1308b520400034e0014832e00000
 * 6b010000b62040002ce001482ae000006d010000b720400024e0014822e00000
 * 7701000000481de071010000b920400018e0014816e0000073010000ba204000
 * 10e001480ee000006f010000b820400008e0014806e0000075010000bb204000
 * 00e0002002bc0847
 */
u16 func_08133C00(u16 selector)
{
    switch (selector) {
    case 0xFB:
        return 0x16A;
    case 0xFC:
        return 0x16B;
    case 0xFD:
        return 0x16C;
    case 0xFE:
        return 0x16D;
    case 0xFF:
        return 0x16E;
    case 0x100:
        return 0x177;
    case 0x101:
        return 0x171;
    case 0x102:
        return 0x172;
    case 0x103:
        return 0x173;
    case 0x104:
        return 0x174;
    case 0x105:
        return 0x16F;
    case 0x106:
        return 0x170;
    case 0x107:
        return 0x175;
    case 0x108:
        return 0x176;
    default:
        return 0;
    }
}
