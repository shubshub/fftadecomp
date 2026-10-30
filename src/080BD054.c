#include "ffta.h"

extern u8 *data_020101F0;
extern void func_08022854(u8 *object);

/* 0x080BD054..0x080BD06C:
 * 10 B5 04 4C 20 68 65 F7 FB FB 00 20 20 60 10 BC
 * 01 BC 00 47 F0 01 01 02. */
void func_080BD054(void)
{
    func_08022854(data_020101F0);
    data_020101F0 = 0;
}
