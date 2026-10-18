/* func_08006ADC - 0x08006ADC, 26 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 0906 090e 8468 8b00 1b19 1a60 c068 4018 0021 0170 10bc 01bc 0047
 *
 * Sets one 32-bit slot in a table and clears its flag byte.  Two details had
 * to be right for this to match:
 *   - `index` is a u8, so the compiler masks it with lsl/lsr #24 before using
 *     it as an index;
 *   - the pointers live at +8 and +0xC, which is why Table has two words of
 *     padding in front of them.
 */

#include "ffta.h"

void func_08006ADC(Table *t, u8 index, u32 value) {
    t->words[index] = value;
    t->flags[index] = 0;
}