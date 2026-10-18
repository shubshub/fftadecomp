/* func_08009888 - 0x08009888, 40 bytes of code + a 20-byte literal pool
 *
 * NOT MATCHED - it cannot be matched without a linked build.  Do not commit.
 *
 *   target code  10b5 0949 0022 0120 4871 0a71 0748 0849 4318 084c 0119
 *                0a70 0749 4018 0021 0280 1970 10bc 01bc 0047
 *   target pool  03000ed0 02000000 00002fbe 00002fbf 00002fbc
 *
 * The ROM materialises one base pointer from the pool (0x02000000, the first
 * word of EWRAM) and adds three *separate* field offsets to it - 0x2FBE,
 * 0x2FBF, 0x2FBC, one pool entry each - so the three addresses are never
 * folded into single absolute constants, and the three live values are what
 * forces the frame (`push {r4, lr}` / `pop {r4}` / `pop {r0}` / `bx r0`).
 * The IWRAM object at 0x03000ED0 gets its two bytes at offsets 4 and 5.
 *
 * agbcc only produces base-plus-separate-offsets when the base is a *symbol*
 * it cannot see through, so the original source reached these objects through
 * named globals.  The same idiom is everywhere in the ROM with this base:
 * func_080099C4 (offsets 0x1F1C, 0x2190, 0x2191) and func_0802DA00 (0x2FC4).
 * With named globals the pool holds `.word g_02000000` / `.word g_03000ED0`,
 * i.e. R_ARM_ABS32 data relocations, and match.py's linked profile only
 * accepts R_ARM_THM_CALL - the same limitation as 0x0800BC08 / 0x0800BC28.
 *
 * With the literal bases spelled below agbcc folds every access instead: one
 * pool entry (0x02002FBF) plus `sub #3` / `add #2`, 36 bytes, no frame.  A
 * literal base with widely separated offsets (measured at 0x1F1C / 0x2190 /
 * 0x2191) folds each address into its own absolute constant, so no literal
 * spelling reaches the ROM's shape either.
 */

#include "ffta.h"

void func_08009888(void)
{
    u8 *state = (u8 *)0x03000ED0;
    u8 *block = (u8 *)0x02000000;

    state[5] = 1;
    state[4] = 0;
    block[0x2FBF] = 0;
    *(u16 *)(block + 0x2FBC) = 0;
    block[0x2FBE] = 0;
}