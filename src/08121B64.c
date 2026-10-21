/* func_08121B64 - 0x08121B64, 20 bytes (16 code + 4 literal pool)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5011c02480068e5f6e4fa02bc0847c4590102
 *
 * A wrapper with no body of its own: it reads the owner pointer out of the
 * RAM word at 0x020159C4, hands it to func_08007138 together with the
 * caller's byte count, and returns the block that call hands back.
 *
 * The literal pool holds one word, 0x020159C4, at 0x08121B74 - the only
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

void *func_08007138(void *owner, u32 size);

void *func_08121B64(u32 size)
{
    void **owner = (void **)0x020159C4;

    return func_08007138(*owner, size);
}
