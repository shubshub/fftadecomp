# 0x08024A24 - move the view to the selected cell: bytes identical, refused (pointer arguments of a leaf callee still live in R2/R3 at the next call) (150 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. Unless `func_0801BDB0()` returns nonzero (0x08024A2A-0x08024A32),
the function takes the state's current cell (`u16` column at +0xC, `u16` row at +0x10) and builds a point in three
`s16` stack locals. Those are `x = (column << 5) + 16` at sp+8, `depth = (row << 5) + 16` at sp+0xC, and
`y = func_0801CC18(column, row) << 4` at sp+0xA (0x08024A34-0x08024A5C). It projects the point in place with
`func_0801C918(x, y, depth, &x, &y, &depth)` (0x08024A72). It then calls `func_0801C960(x, y, &x, &y)` (0x08024A84),
a 36-byte leaf that subtracts the halfwords at 0x02007F40+0x24/+0x26 and stores the results through R2 and R3.
Next it calls `func_0801B938(x - 120, y - 96)` (0x08024A9A, matched `src/0801B938.c`), which starts a motion of the
state at 0x02007F40 toward that position and calls the BIOS Sqrt wrapper `func_08141898` (`svc 8`). Last, it copies
the 8-byte cell to `previous` at +0x14 (two words, 0x08024A9E-0x08024AA4) and calls `func_08025238(state)` when the
mode byte at +4 is 4 (0x08024AA6-0x08024AAE). The index row `08024A24 08024ABA 150 69 call` is right: 69 reachable
instructions, no literal pool, ending with `bx r0` at 0x08024AB8. No data symbol is needed.

## Byte identity

`08024A24.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08024A24. `func_0801BDB0`, `func_0801CC18`,
`func_0801C918`, `func_0801C960`, `func_0801B938` and `func_08025238` were bound to their ROM addresses
(6 `R_ARM_THM_CALL`, no data relocations). The 150-byte symbol equals the ROM span `[0x08024A24, 0x08024ABA)`:
SHA-256 `1638c39650fb45920c0e439ec7941fe8912bbf287fff4d9c6888b1e12550e6f3` for both. `.text` is 152 bytes: the symbol
and then the assembler's 2-byte `c046` alignment pad, which lies outside the indexed span. `match.py` refuses before
its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08024A24.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-root-return-scratch-v1`, `bounded-buffer-guarded-bios-division-v1` and five other buffer selectors (12) | `buffer callee 0x0801B938: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-sqrt-scratch-v1`, `bounded-buffer-discarded-return-scratch-v1`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-v1`, `bounded-buffer-direct-halfword-output-v1`, `bounded-buffer-three-halfword-output-v1`, `bounded-buffer-named-three-halfword-output-v1` (7) | `buffer callee 0x0801C960: consumer observes discarded return scratch before a killing write` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x0801B938: buffer callee 0x08141898: structural inventory is not closed` |
| `static-callback-restoring-r6-target-aligned-v1` | `buffer callee 0x0801C918: descriptor call does not prove preservation of a live alias register` |
| `static-callback-restoring-r6-target-leaf-alias-aligned-v1` and five other `static-callback-restoring-r6-target-*-aligned-v1` values (6) | `leaf alias saves permit only private PUSH/POP stack access` |
| `static-callback-restoring-entry-aliases-aligned-v1`, `static-callback-restoring-scratch-prefix-aligned-v1` | `entry alias saves permit only private PUSH/POP stack access` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `unsupported stack-alias use or escape` |
| `static-callback-buffer-v1`, `restoring-owner-runtime-v1`, `restoring-owner-acyclic-v1`, `descriptor-output-alias-v1`, `canonical-integer-scalar-data-source-v1` and 27 other owner selectors (32) | `owner requires sole complete Thumb ELF function` (these owners do not admit the assembler's 2-byte `c046` pad after the 150-byte symbol, `tools/owner_admission_profile.py:1047-1053`) |
| all 42 `--addressed-signed-runtime-profile` values | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |

The other 108 selector values stop on requirements this function does not meet: a scheduler, manager or
state-iterator contract; a switch or switch-data layout; a known-query, closure or finite-loop form; a runtime or BIOS
helper it does not call (division, software float or double, CpuSet, CpuFastSet, BgAffineSet, fill, memcpy); function
thunks; integer-source identities; the -O0 toolchain; or a palette bundle.

## Cause

R2 and R3 are set to sp+8 and sp+0xA as the third and fourth arguments of `func_0801C960` (0x08024A80-0x08024A82).
`func_0801C960` stores through them and returns without writing either register. Between that return and the next
call, `bl func_0801B938` at 0x08024A9A, the caller writes only R0 and R1 (0x08024A88-0x08024A98). So at that call R2
and R3 still hold the addresses of two of the caller's stack locals, although `func_0801B938` takes two arguments.

The default buffer walk treats the two live stack addresses as buffers passed to `func_0801B938`. It follows them into
that function and stops at its BIOS Sqrt wrapper (`buffer callee 0x08141898: non-leaf calls and interrupts require
linked CFG verification`). `bounded-buffer-bios-sqrt-scratch-v1` is the selector for that wrapper. Under it, a
callee's return may leave stack aliases in R2/R3 only if every path in the caller kills them before observing them.
Its walk from the return of `func_0801C960` (`normal_return_aliases`, `tools/named_data_buffer_profile.py:552-601` at
18dcc516) reaches the call at 0x08024A9A with R2 and R3 still live. The base `check_scratch_call` (lines 603-604),
which `BiosSqrtScratchProof` (line 816) does not override, refuses any call reached in that state. The prototype of
the callee is not consulted. No filed kit issue covers this case.

## Source notes

- `state->previous = state->cell;` is a structure copy. The ROM copies the 8-byte cell as two words
  (0x08024A9E-0x08024AA4), so the cell is an 8-byte member whose `u16` column and row sit at +0 and +4 of it. The
  bytes at +2 and +6 are unknown. Copying the two members one by one gives other code (below).
- The column and row are read from the state at each use and passed straight to `func_0801CC18`. The ROM narrows the
  two halfwords already loaded for the shifts (0x08024A48-0x08024A4E), as in `src/08025238.c`. Holding them in `u16`
  locals gives other code (below).
- `x`, `y` and `depth` are the three `s16` locals whose addresses are passed, at sp+8, sp+0xA and sp+0xC. Other
  declaration orders were not tried.
- The callee prototypes are those of their own sources (`src/0801BDB0.c`, `src/0801CC18.c`, `src/0801C918.c`,
  `src/0801C960.c`, `src/0801B938.c`). `func_0801B938`'s `u16` result is ignored. `func_08025238` is declared here
  taking `State08024A24 *`. `src/08025238.c` types the same object as `State08025238`, and the two views agree on the
  members they share (pointer at +0, column at +0xC, row at +0x10). The `mode` byte at +4 is not named in that view.

## Ruled out

- `previous.column = cell.column; previous.row = cell.row;` instead of the structure copy: 150 bytes, 8 differ, first
  at 0x08024A9E.
- `u16 column` / `u16 row` locals read once at the top: 150 bytes, 10 differ, first at 0x08024A36.
- The previously parked copy (the cell and `previous` as four `u32` words, `u16` column/row locals) gives 150 bytes,
  15 differ, first at 0x08024A36.

kit issue: (to be filed - BIOS Sqrt scratch selector refuses a call reached while a leaf callee's pointer arguments are still in R2/R3); shubshub/fftadecomp-kit#192 (comment)
