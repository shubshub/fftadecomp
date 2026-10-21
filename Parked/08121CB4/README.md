# 0x08121CB4 - parked, no match

86 bytes. The source is recovered and compiles to **82 of 86 bytes**; only the
register allocation differs. The diagnosis below is the agent's, and it is
specific enough to pick up later.

## What it does

The state pointer comes from `0x020159CC`. If it is non-NULL the slot is
`state + 0x4D8 + index * 8` and the function returns the pointer stored at
slot+4. If the state is NULL it falls back to `0x02002EBC + count * 264`, where
count is the u16 at `0x02003CA6`.

The count==0 path re-loads through the null slot pointer (`ldr r0,[r1,#4]` with
r1 = 0). That is the ROM's own behaviour, not a decompiler artefact.

## Pool values

| address | value | meaning |
|---|---|---|
| `0x08121CC8` | `0x020159CC` | the state pointer |
| `0x08121CF8` | `0x02000000` | root state block - `g_state_02000000` already exists |
| `0x08121CFC` | `0x00003CA6` | offset of the u16 count |
| `0x08121D00` | `0x00002EBC` | offset of the 264-byte-record table |

## The difference: register allocation only

Structure, control flow, arithmetic (`index*8`, `count*33*8`), both literal
pools, block order and every branch displacement match. What differs is which
register holds what:

| | ROM | attempt |
|---|---|---|
| slot pointer | `r1`, shared with the state pointer | `r2`, shared with the index |
| the null store | `movs r1,#0` | `movs r2,#0` |
| count block | address in `r2`, count in `r0` | address in `r0` |

The ROM also has an extra two-byte `adds r1,r0,#0` copy of the count that the
attempt is missing - which is why the size is 82 rather than 86, and why the
pool alignment differs with it.

agbcc's `-da` dumps show the state pseudo and the slot pseudo **do not
conflict** (`29 conflicts: 29 34 38 39 0 13`, no `27`), so sharing `r1` is
legal; the allocator simply lands on a different fixed point. What steers it is
the *local allocation* of the count block: the ROM keeps the `0x3CA6` offset in
`r0` and the address in `r2`, leaving `r0` usable for the count global and `r1`
for the slot - while every source shape found puts the address in `r0`, which
takes `r0` out of play and pushes the slot pointer to `r2`/`r3`.

## Ruled out

branch orientation (only `if (state == 0) ... else ...` gives the ROM's `bne`
plus the `movs r?,#0` fall-through and the split literal pool); `goto` versus a
duplicated return; the slot pointer as a separate variable versus the pointer
modified in place; the redundant `p = 0` store (agbcc deletes it whenever the
pointer is provably zero in that branch, so the ROM's `movs r1,#0` can only be a
separate pseudo sharing `r1`); struct member versus byte pointer versus local
pointer base; `264` versus `33*8` versus `8*33` versus `sizeof`; the
association of the table address (`(base+0x2EBC)+count*264` matches the ROM,
`count*264+0x2EBC+base` does not); parameter width and index narrowing inline
versus in a local; `entry[1]` versus `->value` versus a byte-offset load; and
the scopes of `base`/`count`/`table` - function scope puts the slot in `r1` but
hoists the symbol load to the top, shifting everything by two bytes, while
block scope keeps the load in the count block but puts the slot in `r2`/`r3`.

This is the same class of problem as `Parked/0801C984`: agbcc's allocator
reaching a different fixed point, with the source shape and the allocation
order pulling in opposite directions.