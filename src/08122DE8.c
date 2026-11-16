#include "ffta.h"

/* Complete [0x08122DE8, 0x08122E1C): 52 bytes including the return literal.
 * Target: 00b5031c4a7801200856002807da80321206120e181c012103f0ecfa04e04a78
 *         181c022103f0e6fa014802bc0847000015010000
 */

extern void func_081263DC(void *owner, u8 first, u8 second);

u32 func_08122DE8(void *state, const u8 *command)
{
    if ((s8)command[1] < 0)
        func_081263DC(state, 1, command[1] + 0x80);
    else
        func_081263DC(state, 2, command[1]);
    return 0x115;
}
