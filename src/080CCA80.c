// 0x080CCA80 - 44 bytes as one ELF symbol (code plus the literal pool).
//
// Counts the non-zero entries of a 20-element u16 table at 0x02001F3C and
// returns how many of them are set.  The table is the u16 half of a pair: the
// u8 twin at 0x02002E64 is walked the same way by func_080CCA54, and
// func_080CCAAC writes the first free slot of this one.
//
// The table address is read in place out of RAM, so it is a plain constant
// and not a relocated symbol.  It has to live in a variable: written inline
// the compiler folds the access into its own literal pool entry instead of
// the single load the ROM has.
#include "ffta.h"

u32 func_080CCA80(void)
{
    u8 i = 0;
    u8 count = 0;
    const u16 *table = (const u16 *)0x02001F3C;

    for (; i <= 19; i++) {
        if (table[i] != 0)
            count++;
    }

    return count;
}
