/* func_08006BE0 - 0x08006BE0, 34 bytes (0x08006BE0 .. 0x08006C01)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5021c0906090ed078ff2807d09068890009180868802212061043086001bc0047
 *
 * NB: the index has this span cut short at 14 bytes.  The function really
 * ends at the interworking return `pop {r0}; bx r0` on 0x08006C00/0x08006C01;
 * the two bytes at 0x08006C02 are the alignment gap before the next
 * function at 0x08006C04.
 *
 * Sets bit 31 of one word of a table, but only while the table has a usable
 * current entry: the byte at +3 is 0xFF when there is none, and the check
 * happens before the word is touched.
 *
 * The table layout this function sees:
 *   +0x00 u16          unknown
 *   +0x02 u8           number of entries
 *   +0x03 u8           current entry, 0xFF when there is none
 *   +0x08 u32 *        the words
 *   +0x0C u8  *        the per-word flag bytes
 * which is the same object the sibling functions in this family use; it is
 * spelled out here so that no shared header has to change.
 */

#include "ffta.h"

typedef struct {
    u16 unknown_00;   /* +0x00 */
    u8  count;        /* +0x02 */
    u8  index;        /* +0x03 */
    u32 unknown_04;   /* +0x04 */
    u32 *words;       /* +0x08 */
    u8  *flags;       /* +0x0C */
} TableSlot;

void func_08006BE0(TableSlot *t, u8 index)
{
    if (t->index != 0xFF) {
        t->words[index] |= 0x80000000;
    }
}
