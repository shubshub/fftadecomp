/* func_0804CA58 - 0x0804CA58, 20 bytes (0x0804CA58 .. 0x0804CA6C)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5011c02480068baf76afb02bc08473cf50102
 *
 * A wrapper with no body of its own: it reads the owner pointer out of the
 * RAM word at 0x0201F53C, hands it to func_08007138 together with the
 * caller's byte count, and returns that call's result.
 *
 * The literal pool holds one word, 0x0201F53C, at 0x0804CA68 - the only
 * constant the function needs.  The address is kept in a variable so the
 * compiler loads it once out of the pool and dereferences it, the
 * `ldr r0, [pc, #8]` / `ldr r0, [r0]` pair the ROM has.
 *
 * The count stays a u32 all the way into the call: the ROM copies the
 * incoming argument with `adds r1, r0, #0` and never narrows it, so a u16
 * parameter here would add a `lsls #16 / lsrs #16` pair the ROM does not
 * have.  Dividing the count by four is func_08007138's business, not this
 * function's.
 */

#include "ffta.h"

void *func_08007138(void *owner, u32 bytes);

void *func_0804CA58(u32 bytes)
{
    void **owner = (void **)0x0201F53C;

    return func_08007138(*owner, bytes);
}
