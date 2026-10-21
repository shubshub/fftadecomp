// func_080CB210 - 0x080CB210, 60 bytes (0x2A code + 2 pad + 16 literal pool)
//
// target bytes (ROM 0x080CB210..0x080CB24B):
//   10 b5 0c 1c 00 04 02 0c 08 49 09 4b 9a 42 05 d9 08 48
//   82 42 02 d8 08 48 09 18 0e 23 00 2c 00 d0 23 60 08 1c
//   10 bc 02 bc 08 47 00 00 40 19 00 02 69 01 00 00 77 01
//   00 00 a4 05 00 00
//
// The indexed span (16 bytes) stops in the middle of the function; the body
// runs to the interworking return `pop {r1}; bx r1` at 0x080CB238, and the
// four literal pool words sit at 0x080CB23C..0x080CB24B.
//
// What it does: it picks the inventory bank that holds a given item id.
// The item array lives in RAM at 0x02001940 and holds 0x169 four-byte
// records; the overflow bank of 14 more records follows it.  The id is
// truncated to 16 bits, and an id in 0x16A..0x177 selects the overflow
// bank.  The bank base is returned and the number of records in the
// selected bank is written through the second argument.
//
// Build notes, all of them load-bearing:
//
//  - The id is narrowed to 16 bits in a local, so the mask lands at the
//    range test and not earlier.  The local is u32 because the range test
//    is unsigned: `bls`/`bhi`, not the signed `bgt`/`ble` a u16 local
//    would give (u16 promotes to int, and int compares are signed).
//  - The bank base is a named global, so the address stays opaque and is
//    not folded into the offset below.
//  - The offset of the overflow bank is the constant 0x169 records, not
//    the `length` variable.  Written as `records += length` agbcc keeps
//    the variable and computes the offset at run time (`lsl r0, r2, #2`),
//    and it then allocates the registers the other way round: the length
//    in r2 and the id in r3, where the ROM has the id in r2 and the
//    length in r3.  As a constant the offset becomes the pool word
//    0x5A4 (= 0x169 * 4) that the ROM has, and the registers fall into
//    place.
//  - The bank length is one variable: it is compared against the id and
//    it is what gets stored through `count`, so the ROM keeps it in r3
//    and overwrites it with 14 in the overflow case.
//
// Literal pool:
//   0x080CB23C  0x02001940   g_state_02001940 (item array)
//   0x080CB240  0x00000169   361 records in the first bank
//   0x080CB244  0x00000177   375 - highest id in the overflow bank
//   0x080CB248  0x000005A4   0x169 * 4 - offset of the overflow bank

#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern InventoryRecord g_state_02001940[];

InventoryRecord *func_080CB210(u32 identifier, s32 *count)
{
    u32 id = (u16)identifier;
    InventoryRecord *records = g_state_02001940;
    s32 length = 0x169;

    if (id > length && id <= 0x177) {
        records += 0x169;
        length = 14;
    }
    if (count != 0)
        *count = length;
    return records;
}
