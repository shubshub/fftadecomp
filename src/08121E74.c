#include "ffta.h"

extern void *data_020159C4;
extern u8 *data_020159C8;
extern void func_0800718C(void *object);
extern void func_08022854(u8 *object);

/* Target bytes [08121E74, 08121E9C):
 * 30 B5 07 4D 28 68 E5 F6 87 F9 06 4C 20 68 00 F7
 * E7 FC 00 20 28 60 20 60 30 BC 01 BC 00 47 00 00
 * C4 59 01 02 C8 59 01 02.
 */
void func_08121E74(void)
{
    func_0800718C(data_020159C4);
    func_08022854(data_020159C8);
    data_020159C4 = 0;
    data_020159C8 = 0;
}
