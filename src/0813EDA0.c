#include "ffta.h"

extern void func_08000D48(u32 channel, const void *source,
                          void *destination, u32 control);

/* Target [0x0813EDA0, 0x0813EDFC), 92 complete bytes:
 * 70b50c1c04990006060e1206120e1b041b0c09040d0c0021914207d2480000190380
 * 481c0006010e9142f7d3111c9f2907d8480000190580481c0006010e9f29f7d9
 * 8022d204044b301c211cc1f6acff70bc01bc0047000001004020
 */
void func_0813EDA0(u8 channel, u16 *buffer, u8 split, u16 first, u16 second)
{
    u8 row;

    for (row = 0; row < split; row++)
        buffer[row] = first;
    for (row = split; row < 160; row++)
        buffer[row] = second;
    func_08000D48(channel, buffer, (void *)0x04000000, 0x20400001);
}
