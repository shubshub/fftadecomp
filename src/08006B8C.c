/* func_08006B8C - 0x08006B8C, 14 bytes (0x08006B8C .. 0x08006B99)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  09068068890d0918002008607047
 *
 * Clears one 32-bit slot of a table: the word at `words[index]` is set to
 * zero.  The table is the same object the sibling functions in this family
 * use (0x08006ADC, 0x08006AF8, 0x08006BE0, 0x08006C24), so `words` is the
 * u32 * at +0x08 of the shared `Table`.
 *
 * `index` is a u8, so the compiler masks it before scaling it: `lsls #24`
 * keeps the low byte, and the following `lsrs #22` is that masked value
 * multiplied by four (agbcc folds the u8 truncation and the shift together).
 */

#include "ffta.h"

void func_08006B8C(Table *t, u8 index)
{
    t->words[index] = 0;
}
