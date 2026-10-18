/* func_0801CAE0 - 0x0801CAE0, 58 bytes
 *
 * Reads four bytes from the fixed table at 0x02007F40 (offsets +0x2E..+0x31),
 * scales each by 8 (the first two) or by 8 then adds 8 (the last two), and
 * writes six s16 results.  The last two are the differences of the pairs
 * already in registers.
 *
 * Stores are interleaved with the loads, as the instructions do, and the
 * differences come from the values just written rather than re-read.
 *
 *   target  10b5 0e49 8c46 2e31 0c78 e400 0480 6146 2f31 0b78 db00 4380
 *           0131 0a78 d200 0832 8280 0131 0978 c900 0831 c180 121b 0281
 *           c91a 4181 10bc 01bc 0047
 */

#include "ffta.h"

void func_0801CAE0(s16 *out) {
    u8 *t = (u8 *)0x02007F40;
    out[0] = t[0x2e] << 3;
    out[1] = t[0x2f] << 3;
    out[2] = (t[0x30] << 3) + 8;
    out[3] = (t[0x31] << 3) + 8;
    out[4] = out[2] - out[0];
    out[5] = out[3] - out[1];
}
