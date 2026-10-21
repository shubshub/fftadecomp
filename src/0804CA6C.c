/* func_0804CA6C - 0x0804CA6C, 20 bytes (0x0804CA6C .. 0x0804CA80)
 *
 * The free-side twin of func_0804CA58: it reads the owner pointer out of the
 * RAM word at 0x0201F53C and hands it to func_08007170 together with the
 * caller's byte count.  func_08007170 subtracts its own 12-byte header from
 * that count and releases the block.
 *
 * The literal pool holds one word, 0x0201F53C, at 0x0804CA7C - the only
 * constant the function needs.  The address is kept in a variable so the
 * compiler loads it once out of the pool and dereferences it, the
 * `ldr r0, [pc, #8]` / `ldr r0, [r0]` pair the ROM has.
 *
 * The count stays a u32 all the way into the call: the ROM copies the
 * incoming argument with `adds r1, r0, #0` and never narrows it, so a u16
 * parameter here - or a u16 parameter on the callee - would add a
 * `lsls #16 / lsrs #16` pair the ROM does not have.
 */

#include "ffta.h"

void func_08007170(void *block, u32 bytes);

void func_0804CA6C(u32 bytes)
{
    void **owner = (void **)0x0201F53C;

    func_08007170(*owner, bytes);
}
