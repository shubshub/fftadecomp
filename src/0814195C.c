#include "ffta.h"

/* Complete [0x0814195C, 0x08141984): 40 bytes, 16 instructions and two
 * literal-pool words.  Decrements the nonzero u16 countdown at 0x03005E42
 * and sets the byte at 0x0200F360 when it reaches zero; the zero test is on
 * the decremented value (lsls #16 at 0x0814196C). */

extern u16 data_03005E42;
extern u8 data_0200F360;

void func_0814195C(void)
{
    if (data_03005E42 != 0 && --data_03005E42 == 0)
        data_0200F360 = 1;
}
