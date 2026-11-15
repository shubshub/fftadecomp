#include "ffta.h"

/* Complete [0x0802BD44, 0x0802BD8E): 74 bytes.
 * f0b5474680b40b1c071c002020cb00240f213e1c04ce9c46013080460723281c0840
 * 002800d00c43013b0901002bf6daa2432a433a606346371c40460728e5dd08bc9846
 * f0bc01bc0047
 */
void func_0802BD44(void *destination, const void *source)
{
    const u32 *input = source;
    u32 *output = destination;
    u32 value;
    u32 mask;
    u32 nibble;
    u32 previous;
    s32 row;
    s32 column;

    for (row = 0; row < 8; input++, output++, row++) {
        value = *input;
        mask = 0;
        nibble = 0xF;
        previous = *output;

        for (column = 0; column < 8; column++, nibble <<= 4) {
            if (value & nibble)
                mask |= nibble;
        }

        *output = (previous & ~mask) | value;
    }
}
