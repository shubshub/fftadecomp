# 0x0800ADD8 - byte-identical, parked on a policy question: two bit-0 halves that compute the same thing (198 bytes)

Retry of Parked/0800ADD8 on 2026-11-16, kit fcdf2d45, default profile. Not shipped: a policy question, the same one as
Parked/0800AF8C, not a byte problem.

`0800ADD8.c` prints `MATCH - byte identical` (99/99 instructions, 198/198 bytes; complete ELF symbol, closed leaf CFG,
no relocations) and passes `plausible.py --strict`. Index row 0800ADD8 0800AE9E 198 is correct; no data symbols, no literal pool.

## What the ROM shows

It tests flag bit 0 of the table (`ldrh r1, [r5, #2]; movs r0, #1; ands r0, r1; cmp r0, #0; beq 0x0800AE08` at
0x0800ADF0-0x0800ADF8) and then tests 0x4000 on each path (0x0800ADFA-0x0800AE02 and 0x0800AE08-0x0800AE10). Both
bit-0 paths perform the same loads at the same offsets and widths. The only instruction unique to one path is
`mov r2, ip` at 0x0800AE48, a copy of a value r2 already holds: the register-allocation leftover that stopped the
compiler merging the two copies one instruction short. So the original source had two copies of the body under a
bit-0 test that changes nothing in this function.

What bit 0 means: func_0800B2A4 sets it when `g_records_02009000[index].format == 0`. The unmerged func_0800B568
(0x0800B6D0, 0x0800B8AA) tests it to choose the renderer for the frame this function locates: bit 0 set,
func_0800A71C (halfword cells, `ldrh r3, [r0]` at 0x0800A96C); clear, func_0800AA54 (byte cells, `ldrb r2, [r0]` at
0x0800AC20). So bit 0 does select a record layout in this module, but the difference is in the payload only; the
four-field header this function reads is the same in both, as the two renderers' shared `TileLayout` shows.

## Forms tried (default flags; plausible --strict exit 0 unless stated)

| Form | Result |
| --- | --- |
| the source here: two braced bit-0 halves, identical text | MATCH 198/198 |
| per-mode record types (`u16 cells[1]` in the bit-0 half, `u8 cells[1]` in the other; halves differ by cast only) | MATCH 198/198 |
| shared static inline body, braceless `if (table->flags & 1) read_frame(...); else read_frame(...);` | 99/99 identical, plausible `SUSPECT: inert-control-flow`, HAND-ASM REQUIRED BUT NOT ALLOWED |
| the same with braces around each arm | MATCH 198/198 |
| no bit-0 test, one 0x4000 split (the earlier parked shape) | 162 < 198 |
| ternary on bit 0 | 162 < 198 (folded away) |
| `switch (table->flags & 0x4001)`, four cases | 250 bytes |
| halves swapped (`if (!(table->flags & 1))`) | 198 bytes, 98/99 instructions |
| `u16` masked local instead of `index &= 0x3FFF` | 258 bytes |
| no `frames` local | MATCH 198/198 (either is acceptable) |

No form whose halves read different fields or widths can match: the ROM's two paths read the same ones.

## Why it is parked

The two halves do the same thing. plausible.py's inert-control-flow rule does not flag them only because it is one
regex that sees braceless single-statement arms with an unparenthesised condition; the braceless spelling of the
same code is refused. Shipping would mean clearing that rule by the shape of the text alone, so inert code waits for
the maintainers' answer to the policy question - the same one 0x0800AF8C waits for (there the arms merged completely
and only dead `ands` remain; here they merged partly and a live branch remains).

Question for the maintainers, covering both 0x0800AF8C and 0x0800ADD8: when the ROM itself contains a flag test
whose arms compute identical results, and no source without the test reproduces it, may the source have identical
arms (or arms that differ only by a cast to a per-layout type)? If yes, which spelling - identical text, or per-layout
types?

kit issue: shubshub/fftadecomp-kit#201 (policy question)
