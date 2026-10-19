/* func_08017884 - 0x08017884, 32 bytes.
 *
 * target  10b5 041c 0904 090c fff7deff 0004 0028 03db 010c 201c
 *         fff74bff 10bc 01bc 0047
 *
 * The indexed span stops at 0x0801788E, which cuts the function in half (it
 * lands in the middle of the first `bl`); the body actually runs to 0x080178A4
 * because the next indexed function starts there.  match.py sizes from the ELF
 * symbol, so all 32 bytes have to come out.  There is no literal pool - the
 * 22 bytes the truncated index called padding are the rest of the function.
 *
 * `lsls #16 / lsrs #16` on r1 before the first call is the u16 narrowing of the
 * incoming argument, and `lsls r0,#16 / cmp r0,#0 / blt` is the signed test of
 * the callee's result; `lsrs r1, r0, #16` then reuses that same shifted value
 * to pass the result on as a u16.  0x0801784C returns -1 when it fails, so
 * the result is signed and only a non-negative one is forwarded.
 */

#include "ffta.h"

s16 func_0801784C(void *state, u16 step);
void func_08017734(void *state, u16 amount);

void func_08017884(void *state, u32 step) {
    s16 amount = func_0801784C(state, (u16)step);
    if (amount >= 0)
        func_08017734(state, (u16)amount);
}