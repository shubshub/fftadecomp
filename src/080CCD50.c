// 0x080CCD50 - 272 bytes as one ELF symbol (code, jump table and case
// bodies).
//
// Reads one field out of a 28-byte record of the table at 0x0855187C.
//
// The field offsets are the ones the instructions use; the rest of the
// record is still unknown, so the gaps are left unnamed:
//   +0x00  u16   selector 0
//   +0x02  u8    selector 1
//   +0x04  u8    selector 2
//   +0x05  u8    selector 3
//   +0x06  u8    selector 4
//   +0x07  u8    selector 5
//   +0x08  u8    selector 6
//   +0x09  u8    selector 7
//   +0x0A  u8    selector 8
//   +0x0B  u8    selector 33
//   +0x0C         selector 9 returns the address of this field
//   +0x10  u32   selector 10; selectors 11..31 read its bits 0..20
//   +0x14  u16   selector 32
#include "ffta.h"

u32 func_080CCD50(u16 index, u8 selector)
{
    // The table is read in place out of the ROM - the ROM's own literal pool
    // for this function holds that address - so it is a plain constant and
    // not a relocated symbol.
    // plausible: a ROM address read in place is a pointer, not a value.
    const u8 *record = (const u8 *)0x0855187C + index * 28;
    u8 bit = selector - 11;

    if (bit <= 20u) {
        u32 mask = 1u << bit;

        return (*(const u32 *)(record + 0x10) & mask) != 0;
    }

    switch (selector) {
    case 0:
        return *(const u16 *)record;
    case 1:
        return record[2];
    case 2:
        return record[4];
    case 3:
        return record[5];
    case 4:
        return record[6];
    case 5:
        return record[7];
    case 6:
        return record[8];
    case 7:
        return record[9];
    case 8:
        return record[0xA];
    case 9:
        return (u32)(record + 0xC);
    case 10:
        return *(const u32 *)(record + 0x10);
    case 32:
        return *(const u16 *)(record + 0x14);
    case 33:
        return record[0xB];
    default:
        return 0;
    }
}
