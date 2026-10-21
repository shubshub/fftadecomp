// func_08036350 - 0x08036350, 110 bytes (0x08036350..0x080363BE)
//
// target bytes (ROM 0x08036350..0x080363BD):
//   00 b5 00 06 02 0e 0c 4b 00 2a 2d d0 92 21 89 00
//   58 18 01 78 01 20 08 40 00 28 01 d1 09 2a 23 d0
//   06 48 07 49 40 18 01 78 02 20 08 40 00 28 0d d1
//   1c 2a 0b d1 18 e0 00 00 10 2c 00 02 00 00 00 02
//   58 2e 00 00 48 1c 00 06 00 0e 0e e0 00 21 48 00
//   40 18 80 00 18 18 b3 30 00 78 90 42 f2 d0 48 1c
//   00 06 01 0e 1d 29 f2 d9 00 20 02 bc 08 47
//
// The indexed span runs to 0x080363C0, but the body ends at the interworking
// return `pop {r1}; bx r1` at 0x080363BC, so the function is 110 bytes; the
// two bytes at 0x080363BE are alignment padding before the next prologue.
//
// What it does: it looks a value up in a 30-entry table and returns the
// 1-based index of the entry that holds it, or 0 when the value is not in the
// table.  The table lives in the state object at RAM 0x02002C10: its record
// array starts at +0xB0, every record is 12 bytes and the searched byte is
// the one at +3 (the same field func_08036330 reads).  Two values are
// excluded: 9 is refused while bit 0 of the flag byte at 0x02002E58 is clear,
// and 28 (0x1C) while bit 1 of it is clear.
//
// The flag byte is reached twice, through the two views of the state: as
// +0x248 of the object at 0x02002C10 and as +0x2E58 of the root block at
// 0x02000000.  Both land on RAM 0x02002E58 (0x02002C10 + 0x248 =
// 0x02000000 + 0x2E58), which is why the ROM loads it twice and the
// compiler cannot fold the two loads together.
//
// Build notes, all of them load-bearing:
//
//  - The object at 0x02002C10 has to be reached through the named global
//    g_state_02002C10.  With the literal 0x02002C10 agbcc folds the base
//    and the member offset into a single pool word (0x02002E58) and the
//    runtime add disappears; through the symbol the base stays opaque, so
//    the offset is added at runtime - `movs r1,#0x92 / lsls r1,r1,#2 /
//    adds r0,r3,r1` for +0x248 and `adds r0,r0,#0xB3` for the record field.
//  - The same goes for the root block: g_state_02000000 keeps 0x02000000
//    and 0x2E58 in two pool words (`ldr r0,[pc] / ldr r1,[pc] / adds`),
//    which is what the ROM does.  The literal 0x02000000 folds to the
//    single word 0x02002E58 instead.
//  - The address of the object at 0x02002C10 has to live in a variable.
//    Used directly, each access folds into its own pool entry and the ROM's
//    one load becomes two (`ldr r3,[pc]` at the top and a second one in the
//    loop).  In a variable the compiler keeps it in r3 and uses it for both
//    the flag byte and the record scan.
//  - The record address is `base + index * 12 + 0xB3`: the record array is
//    at +0xB0 and the searched byte at +3 inside the record, so the two
//    constants fold into 0xB3, which is added after the scaled index.
//  - The scan counter is a u8 (`lsls #24 / lsrs #24` on the increment) and
//    the bound is 0x1D, so the loop runs 30 times and the result is the
//    1-based index narrowed to a u8.
//
// NOTE: g_state_02002C10 has to be added to config/data_symbols.json as
// "g_state_02002C10": "0x02002C10" - it is the object the pool word at
// 0x08036388 points at, and match.py's linked profile needs the symbol to
// resolve that relocation.

#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 value;
    u8 unknown_04[8];
} Entry08036350;

typedef struct {
    u8 unknown_00[0xb0];
    Entry08036350 entries[30];
    u8 unknown_218[0x30];
    u8 flags;
} State08036350;

typedef struct {
    u8 unknown_0000[0x2e58];
    u8 flags;
} Root08036350;

extern State08036350 g_state_02002C10;
extern Root08036350 g_state_02000000;

u8 func_08036350(u8 param)
{
    State08036350 *state = &g_state_02002C10;
    u8 i;

    if (param == 0)
        return 0;
    if (!(state->flags & 1) && param == 9)
        return 0;
    if (!(g_state_02000000.flags & 2) && param == 0x1c)
        return 0;
    for (i = 0; i < 30; i++)
        if (state->entries[i].value == param)
            return i + 1;
    return 0;
}
