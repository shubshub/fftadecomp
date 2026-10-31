#include "ffta.h"

extern const u8 data_08528C24[][7];

/* Target: complete [0x080CC3C8, 0x080CC50E), 326 bytes.
 * 00b50006000e09060a0e132800d997e0800002494018006887460000e8c30c0838c40c0838c40c08
 * 48c40c0848c40c0848c40c0864c40c0864c40c0878c40c0878c40c0878c40c0894c40c0894c40c08
 * b0c40c08b0c40c08c4c40c08c4c40c08e0c40c08e0c40c08f4c40c08f4c40c080248d100891a0918
 * 08785ce0248c52080549d000801a401802785209407803210840c000104354e0248c52080348d100
 * 891a091848784006c00e4ae0248c52080549d000801a40184278d20980780f210840400010433ce0
 * 248c52080549d000801a401882781209c07801210840000110432ee0248c52080348d100891a0918
 * c8788006c00e24e0248c52080549d000801a4018c27892090079072108408000104316e0248c5208
 * 0348d100891a09180879c0080de00000248c52080348d100891a09184879c006c00e02e0248c5208
 * 002002bc0847
 */
u32 func_080CC3C8(u8 selector, u8 index)
{
    switch (selector) {
    case 0:
    case 1:
        return data_08528C24[index][0] & 0x1F;
    case 2:
    case 3:
    case 4:
        return (data_08528C24[index][0] >> 5) |
               ((data_08528C24[index][1] & 3) << 3);
    case 5:
    case 6:
        return (data_08528C24[index][1] >> 2) & 0x1F;
    case 7:
    case 8:
    case 9:
        return (data_08528C24[index][1] >> 7) |
               ((data_08528C24[index][2] & 0xF) << 1);
    case 10:
    case 11:
        return (data_08528C24[index][2] >> 4) |
               ((data_08528C24[index][3] & 1) << 4);
    case 12:
    case 13:
        return (data_08528C24[index][3] >> 1) & 0x1F;
    case 14:
    case 15:
        return (data_08528C24[index][3] >> 6) |
               ((data_08528C24[index][4] & 7) << 2);
    case 16:
    case 17:
        return data_08528C24[index][4] >> 3;
    case 18:
    case 19:
        return data_08528C24[index][5] & 0x1F;
    default:
        return 0;
    }
}
