#include "ffta.h"

/* Complete target: [0x080CB388, 0x080CB44E), 198 bytes.
 * Target bytes: 00b50006000e01380d2859d8800002494018006887460000a4b30c08dcb30c08e2b30c08ecb30c08f2b30c08fcb30c0802b40c080cb40c0814b40c081ab40c0824b40c082cb40c0832b40c083cb40c0842b40c08b520400033e0014831e000006b010000b62040002be0014829e000006d010000b720400023e0014821e000007701000000481ce071010000b920400017e0014815e0000073010000004810e075010000ba2040000be0014809e000006f010000bb20400003e0b820400000e0002002bc0847
 */
u32 func_080CB388(u32 selector)
{
    u8 index = selector;

    switch (index) {
    case 1:
        return 0x16A;
    case 2:
        return 0x16B;
    case 3:
        return 0x16C;
    case 4:
        return 0x16D;
    case 5:
        return 0x16E;
    case 6:
        return 0x177;
    case 7:
        return 0x171;
    case 8:
        return 0x172;
    case 9:
        return 0x173;
    case 10:
        return 0x175;
    case 11:
        return 0x174;
    case 12:
        return 0x16F;
    case 13:
        return 0x176;
    case 14:
        return 0x170;
    default:
        return 0;
    }
}
