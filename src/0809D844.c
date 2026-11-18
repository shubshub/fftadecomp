#include "ffta.h"

extern void func_08022BA4(u8 first, u8 second);

/* Complete target: [0x0809D844, 0x0809D852), 14 bytes.
 * Target bytes: 00b50120022185f7abf901bc0047
 */
void func_0809D844(void)
{
    func_08022BA4(1, 2);
}
