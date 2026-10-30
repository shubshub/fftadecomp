#include "ffta.h"

extern u8 data_020084D8;

/* 0x08141500..0x08141514: 20 complete bytes.
 * Target: 03480178022008400006000e70470000d8840002.
 */
u8 func_08141500(void)
{
    return data_020084D8 & 2;
}
