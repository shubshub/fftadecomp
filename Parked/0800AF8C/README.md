# 0x0800AF8C - byte-identical, parked on a policy question: four arms that return the same field (30 bytes)

Target: complete `[0x0800AF8C, 0x0800AFAA)`, 30 bytes, 15 instructions; the index row `0800AF8C 0800AFAA 30 15` is
correct. Default flags, no data symbols, no literal pool. Retried 2026-11-16 with kit fcdf2d45.

`0800AF8C.c` prints `MATCH - byte identical` (15/15 instructions, 30/30 bytes, elf-symbol-cfg-leaf-v2) and
`plausible.py --strict` exits 0. It is not shipped because its four arms compute the same value: inert code waits for
the maintainers' answer to the policy question below.

## What the ROM shows

It loads the table's flags (`ldrh r1, [r2, #2]` at 0x0800AF90), tests 8 and 0x8000 without using either result (the
`ands` at 0x0800AF94 and 0x0800AF9A are both overwritten unused), saves lr although nothing is called, and returns the
u16 at offset 0 of the record data, read as two bytes. That is the two-byte header src/0800B13C.c names `unknown_00[2]`;
the three callers (src/0800B2A4.c, src/0800B394.c, src/0800B47C.c) store `func_0800AF8C(node) - 1`, so it is an entry
count.

That fits a source that branched on both bits into four arms, one typed data pointer per record layout, as
src/0800ACA8.c and src/0800B13C.c split the layouts. All four arms read the same offset; agbcc merges them after
register allocation (the branches are still present after global allocation and gone after the post-reload jump pass),
which leaves the flag loads, the dead `ands` and the `push {lr}`.

## Forms tried (default flags)

| form | result |
| --- | --- |
| `0800AF8C.c`: four braced arms, one record type per layout | MATCH 30/30, plausible |
| four braced arms that all cast to the same record type | MATCH 30/30, plausible |
| four braceless arms `return read_le16(table->data);` (the helper of src/0800AA54.c) | 15/15 identical, `SUSPECT: inert-control-flow`, `HAND-ASM REQUIRED BUT NOT ALLOWED` |
| the same with braces around each arm | MATCH 30/30, plausible |
| no flag test | 12 < 30 bytes (extent refusal) |
| a test of flag 8 alone | 24 < 30 bytes (extent refusal) |

So the per-layout casts are not what clears plausible.py: its inert-control-flow rule (one regex in `inert_control_flow`)
only sees an if/else whose arms are single unbraced statements and whose condition has no parentheses, and the braces
alone take the arms out of its view. Declaration order does not matter (the only locals are the per-arm pointers).

## Policy question

When the ROM itself contains a flag test whose arms compute the same result, and no source without the test
reproduces it, may the source have identical arms, or arms that differ only by a cast to a per-layout type? The same
question covers 0x0800ADD8 and the always-zero term of 0x0800F860.

kit issue: shubshub/fftadecomp-kit#201 (policy question)
