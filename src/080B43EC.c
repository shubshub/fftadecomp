#include "ffta.h"

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080CCD50(u16 entry, u8 selector);

/* Complete target: [0x080B43EC, 0x080B448C), 160 bytes.
 * Target bytes: 10b50004000c041c0904090c002811d1081c032116f0d0f900040114044a8018000c01280fd913290dd0d920400034e00000f3ff042118f095fc0004000c80210840002802d0e120400026e0201c062118f088fc0004000c023805281cd88000014940180068874658440b0870440b0874440b0878440b087c440b087c440b0880440b08042008e0442006e0232004e0322002e0132000e0422010bc02bc0847
 */
u16 func_080B43EC(u16 first, u16 second)
{
    u16 value4;

    if (first == 0) {
        s16 value = func_080CA7A4(second, 3);

        if ((u16)(value - 13) <= 1 || value == 19)
            return 0x1C2;
        return 0x1B2;
    }

    value4 = func_080CCD50(first, 4);
    if (value4 & 0x80)
        return 0x1C2;

    switch ((u16)func_080CCD50(first, 6)) {
    case 2:
        return 4;
    case 3:
        return 0x44;
    case 4:
        return 0x23;
    case 5:
    case 6:
        return 0x32;
    case 7:
        return 0x13;
    default:
        return 0x42;
    }
}
