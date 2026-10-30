#include "ffta.h"

extern const u32 g_table_08393318[256];

/* Complete [0x0813ADF0, 0x0813AE30): 64 bytes, 28 instructions.
 * 70b5041cd24300238b4210d20a4e0b4de018007850400006120a3240800d40190068
 * 4240581c0004030c8b42f0d3d243101c70bc02bc0847ffffff0018333908
 */
u32 func_0813ADF0(const u8 *bytes, u32 length, u32 crc)
{
    u16 index;

    crc = ~crc;

    for (index = 0; index < length; index++) {
        crc = g_table_08393318[(crc ^ bytes[index]) & 0xFF] ^
              ((crc >> 8) & 0x00FFFFFF);
    }

    crc = ~crc;
    return crc;
}
