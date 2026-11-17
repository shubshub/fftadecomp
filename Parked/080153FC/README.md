# 0x080153FC - marked text entry draw: bytes identical, refused (a local copy of a 3-byte mark through func_081443FC) (218 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_080153FC(drawing, unused, text, palette)` copies the
3-byte mark `data_08149868` to the stack with `func_081443FC` (0x0801541A), reads the entry kind from `text[2] &
0xF0`, and draws the mark and the entry's two strings with `func_08015110` (four calls, the mark from `add r2, sp,
#4`), moving the cursor with `func_08013728` between them. It returns the number of bytes consumed. Its caller is
0x080120F0.

The index row `080153FC 080154D6 218 109 return` has the right extent; 109 is half the byte count, and the reachable
count is 97 (the kit's own refinement and an independent CFG walk agree). No refusal below depends on it.

## Byte identity

`080153FC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080153FC, with every callee and data symbol bound to its
ROM address (10 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 218-byte symbol equals the ROM span `[0x080153FC,
0x080154D6)`: SHA-256 `d5c4c237cd5aa35fe20b68ab2a0d59c0753a0dcbfd267651d11a4ed832974530` for both. `.text` is 220
bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison
(below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080153FC.c` and `data_08149868` added to
`config/data_symbols.json` (each at the address its name gives): the default run and the selectors the kit issue and
the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `unsupported copy prefix instruction: lsrs` |

## Cause

The buffer walk enters the copy helper `func_081443FC` (98 bytes) with a local address in R0 and stops inside it: past
the count test the helper combines the two pointers as numbers to test their alignment (`adds r0, r3, #0; orrs r0, r5`
at 0x08144408-0x0814440A). The kit summarises this helper only in its ROM-table-copy proof, which needs a constant ROM
source, a count from 1 to 15 and a destination alias with no stack-passed pointer, under the ROM-table-copy and
stack-index selectors. `named-data-buffer-finite-small-copy-binding-v1`, which binds this kind of copy, stops at the
`u8` narrowing of the `palette` parameter before the call (`lsrs r7, r3, #0x18` at 0x0801540E): `unsupported copy
prefix instruction: lsrs`. Behind the copy, the mark is passed to `func_08015110`, which dispatches through a jump
table (Parked/08015110).

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors); (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
