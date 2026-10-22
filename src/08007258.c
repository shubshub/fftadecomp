/* 0x08007258 - 24 bytes
 * Target: 00b5 011c 8020 4002 0904 0914 3af106fb 0004 0014 02bc 0847
 */
#include "ffta.h"

extern s32 func_08141874(s32 dividend, s32 divisor);

s32 func_08007258(s32 divisor)
{
    return (s16)func_08141874(65536, (s16)divisor);
}
