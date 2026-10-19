/* func_080C15DC - 0x080C15DC, 104 bytes of code + a 12-byte literal pool
 *
 * The module's state object at 0x020101F8, same as 080C14D8 / 080C1654 /
 * 080C1700.  The offsets come straight off the instructions:
 *
 *   +0x54CC  u8 values[4]      ring buffer
 *   +0x54D0  u8 mode : 4       low nibble,  set from the third argument
 *   +0x54D0  u8 next : 4       high nibble, post-incremented - the index
 *                            `values[...]` uses is the value *before* the
 *                            increment, which is why the ROM reloads the
 *                            pre-increment nibble with a second `lsrs #28`
 *                            rather than reusing the incremented one
 *   +0x54D1  two 4-bit fields  low nibble from arg a, high nibble from arg b
 *
 * The pool is the base address plus one entry per field offset (0x54D1,
 * 0x54D0, 0x54CC), so the base has to stay in a local pointer - folding the
 * offsets into absolute addresses folds each access into its own constant.
 *
 * Store order is the instruction order, which is not the offset order:
 * 0x54D1 first, then 0x54D0, then the ring write.
 *
 * Argument narrowing: a and c are `lsls #24 / lsrs #24` at the top because
 * they feed 4-bit fields; b only gets `lsls #24` there and is folded into the
 * field insert as `(b << 24) >> 20`, i.e. `(u8)b << 4`.  All three are u8.
 *
 *   target  70b5 4e46 4546 60b4 0006 000e 0906 1206 120e 154b 9846 154b
 *           4344 9946 0f26 3040 1d78 1024 6442 231c 2b40 0343 090d 3340
 *           0b43 4846 0370 0e4b 4344 3240 1878 0440 1443 2106 080f 0130
 *           0001 3440 0443 1c70 090f 084b 9844 4144 0220 0870 18bc 9846
 *           a146 70bc 01bc 0047
 *           f801 0102 d154 0000 d054 0000 cc54 0000
 */

#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54CC];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
    u8 unknown_54D1_lo : 4;
    u8 unknown_54D1_hi : 4;
} State080C15DC;

void func_080C15DC(u8 a, u8 b, u8 c)
{
    State080C15DC *state = (State080C15DC *)0x020101F8;

    state->unknown_54D1_lo = a;
    state->unknown_54D1_hi = b;
    state->mode = c;
    state->values[state->next++] = 2;
}