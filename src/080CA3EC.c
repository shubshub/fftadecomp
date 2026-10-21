/* 0x080CA3EC - 18 bytes
 * Target bytes:
 *   00b5 fff7d1ff 011c 8800 4018 0040 02bc 0847
 *   push {lr}; bl func_080CA394; add r1,r0,#0; lsl r0,r1,#2;
 *   add r0,r0,r1; lsl r0,r0,#1; pop {r1}; bx r1
 *
 * func_080CA394 returns a value in 0..127 for the record; this wrapper scales
 * it by ten.
 */

#include "ffta.h"

s32 func_080CA394(const void *object);

s32 func_080CA3EC(const void *object)
{
    return func_080CA394(object) * 10;
}
