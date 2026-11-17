# 0x08001244 - hide two entry lists: near miss alone, byte-identical in its original translation unit (120 bytes, 114/120 alone)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function hides the entries of the current list in two tables
(`data_03002F68[data_03002F58]` with count `data_03002F60[...]`, and `data_03003170[...]` with count
`data_03003168[...]`) by writing `0x00F800A8` to each 8-byte entry with the `static inline HideEntries(u64 *entry,
s32 count)` helper, character for character the helper of the matched `src/08001194.c`, and then clears both counts
with one chained assignment. Extent `[0x08001244, 0x080012BC)`: 46 instructions (`push {r4-r7, lr}` / `pop`), then a seven-word pool ending
at 0x080012BC. The index row `08001244 080012BC 120 46 return` is right; no new data symbol is needed.

## Not byte-identical alone

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08001244.c`:

```
verdict NOT MATCHING - bytes differ
40/46 instructions identical (114/120 bytes)
```

The six differing instructions are one register swap. The ROM keeps the address of `data_03002F58` in r6 and that of
`data_03003168` in r5 (`adds r6, r4, #0` at 0x08001258, `ldr r5, [pc, #0x50]` at 0x0800125E); the compile has them the
other way round, and so uses the swapped registers again at 0x08001270, 0x08001276, 0x0800128C and 0x08001292. Extent, loops, store order and the literal pool are identical.
`plausible.py --strict` exits 0. This revision differs from the earlier copy only in comments (the target bytes and
a note that the helper is the text of `src/08001194.c`); both give the same compile.

## Why

Checked against agbcc's `gcse.c` (`hash_expr_1`) in the earlier attempt: the two pseudos are created by GCSE and
rank equally, so the lower-numbered one gets r5. GCSE numbers them in the hash-bucket order of the constant-pool
labels `.LCn` (bucket = the label string's hash modulo a table size of `max_cuid / 2 | 1`, 25 here). Compiled alone,
the labels are `LC0`-`LC4`, and `data_03002F58` (`LC0`, bucket 11) always comes before `data_03003168` (`LC4`, bucket
15); the ROM needs the opposite. Shifting the label counter by k with a throwaway preceding function (a test, not a
candidate): k = 9-12, 16-19, 26-29 and 36-39 reproduce the ROM, every other k in 0..40 does not, and the bucket model
predicts all 41 results.

In its translation unit the function compiles exactly. `src/0800105C.c`, `src/08001194.c` (both as on main) and this
file concatenated into one file, with each later file's conflicting file-scope identifiers renamed by a `#define`
before its text and every body and declaration otherwise unchanged, put the three symbols at `.text` offsets 0x0,
0x138 and 0x1E8 (their ROM spacing) and this function's labels at `LC29`-`LC33`. Linked at 0x0800105C with each
renamed symbol bound to its original's address, all 608 bytes of `[0x0800105C, 0x080012BC)` equal the ROM, and each of
the three functions is identical on its own. (Reported in full, with the list of renamed identifiers, on kit #189;
not re-run for this README.)

So the target is this source compiled in a file that had already used 29 constant labels. A one-file match would
need contrivances (functions or inline helpers that exist only to consume labels), which are not allowed. Verifying
it needs the kit to form the unit: a declared unit of consecutive sources compiled as one file, or a recorded
constant-label offset (kit #189). The unit's real start is not known (`0x08000FC8` is unmatched); `0x0800105C` is a
choice the matching bytes support.

## Source notes

- `HideEntries` is the matched `src/08001194.c` helper verbatim, called twice.
- The count reset is one chained assignment,
  `data_03002F60[data_03002F58] = data_03003168[data_03002F58] = 0;`: the ROM stores one zero register twice
  (`movs r1, #0; str r1, [r0]; str r1, [r2]` before the epilogue).

## Ruled out

From the earlier attempt (same function body):

- Swapped helper parameter order: 45 instructions.
- The local-alias style of `src/08001ED0.c` and `src/08002108.c`: 38/46, 27/45, or 116 bytes.
- `0800105C`'s declarations: the hash table size stays 25.
- Other single-file spellings: the label order is fixed by evaluation order, and changing the table size needs 76-79,
  88-91 or fewer than 36 GCSE instructions.

kit issue: shubshub/fftadecomp-kit#189 (position in the translation unit)
