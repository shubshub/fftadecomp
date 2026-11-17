# 0x08123398 - script command: resolve a coordinate pair, then queue the argument record: bytes identical, refused by the verifier (callback reached deep in a buffer callee chain) (96 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function handles one script command. It builds an
eight-byte argument record on the stack at `sp+4` (selector and mode bytes, signed halfwords `x` and `y`, an unsigned
halfword value): `script[1]` goes into the selector byte by a read-modify-write of the record's first word
(0x081233A4-0x081233AE). It calls `func_08124E74(selector, (s8)script[2], (s8)script[3], &x, &y)` (0x081233C6), with
`&x` = `sp+6` in r3 and `&y` = `sp+8` in the outgoing stack word (`add r4, sp, #8; str r4, [sp]` at
0x081233C2-0x081233C4); that callee resolves the two coordinates in place. It then stores `script[4]` as the mode
(0x081233CC) and `script[5] | script[6] << 8` as the value (0x081233D6), passes the record by value in r1/r2 to
`func_08127B80(context, record)` (0x081233DE) and returns 0x115. The matched `src/08123320.c` builds the same record
from other script bytes and makes the same call. The index row `08123398 081233F8 96 42 return` is right (42
instructions; literal words 0xFFFFFF00 at 0x081233F0 and 0x115 at 0x081233F4). The previous revision of this entry
recorded an index row covering only 48 bytes; main's row is now the full 96. No data symbol is needed.

## Byte identity

`08123398.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08123398, with `func_08124E74` and `func_08127B80` bound
to their ROM addresses (2 `R_ARM_THM_CALL`). The 96-byte symbol equals the ROM span `[0x08123398, 0x081233F8)`,
literal pool included: SHA-256 `70622af84b4851aedd5b5cfef65bf6b9c9bdb19076742da693eee592fd84ae5d` for both. `.text` is
exactly 96 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08123398.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-rom-table-copy-v1` and 13 other `named-data-buffer-*` / `bounded-buffer-*` selectors (19) | `buffer callee 0x08124E74: buffer callee 0x08099560: buffer callee 0x080C7CC0: buffer callee 0x0814225C: non-leaf indirect control flow requires linked CFG verification` |
| `static-callback-buffer-v1` | `buffer callee 0x08124E74: buffer callee 0x08099560: buffer callee 0x080C7CC0: static callback target register is not an exact Thumb function pointer` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08124E74: buffer callee 0x08099560: stack-passed pointer words cannot reach a pinned list-query family` |
| `static-callback-unwritten-r7-v1`, `static-callback-restoring-r6-v1`, `static-callback-restoring-r6-target-v1`, `descriptor-output-alias-v1` and 7 other descriptor / preservation selectors (11) | `buffer callee 0x08124E74: descriptor call does not prove preservation of a live alias register` |
| `descriptor-disjunctive-restoring-callee-alias-v1`, `bounded-disjunctive-restoring-callee-scratch-v1`, `descriptor-restoring-callee-constant-v1` (3) | `callee alias saves permit only private PUSH/POP stack access` |
| `--control-flow-profile mixed-return-inert-spin-v1`, `restoring-owner-acyclic-v1`, `restoring-owner-ignored-leaf-alias-v1` (3) | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `ordinary-formal-output-spill-v1`, `ordinary-formal-output-spill-bios-remainder-v1` (2) | `formal output caller cannot create pointer descriptors` |
| `canonical-integer-two-words-aligned-data-source-v1`, `restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1` and the nine `static-callback-*-aligned-v1` selectors (12) | `aligned owner requires actual external two-byte Thumb alignment` |

The twelve aligned selectors in the last row require a trailing `c046` halfword, and this `.text` has none (it is
exactly 96 bytes). The other 160 selector values stop on requirements this function does not meet: an arithmetic,
float or double runtime, a switch, a BIOS wrapper call, a scheduler, known-query or callback-closure contract, a
function-address thunk, a canonical-integer data source, a finite or counted loop shape, a palette bundle, or the -O0
toolchain.

## Cause

The two coordinate pointers are addresses in the caller's frame, so the buffer walk follows them into `func_08124E74`
(matched, `src/08124E74.c`). That function keeps them in callee-saved registers (`&x` in r7 at 0x08124E7A, `&y` in r8
at 0x08124E7E) across its calls to `func_08121CB4`, `func_080C83CC`, `func_08096D7C` and `func_08099560`
(0x08124ED4-0x08124EEC); the refusal shows the walk descending from there into `func_08099560`. `func_08099560`
(`src/08099560.c`) passes its own local search record and the fixed callback `func_0809AB5C` (the literal at
0x0809957C) to `func_080C7CC0` (`src/080C7CC0.c`), a list walk that copies the callback into r6 (0x080C7CC2) and calls
it through `_call_via_r6` (`bl 0x0814225C` at 0x080C7CD4). The thunk is `bx r6`, an indirect jump, and the walk
refuses any indirect jump in a non-leaf callee (`match.py:4837-4838`). The target is fixed two calls up, by
`func_08099560`, but the walk examines `func_080C7CC0` on its own and does not carry that binding down; the
`static-callback-buffer-v1` run says as much
(`static callback target register is not an exact Thumb function pointer`, at `func_080C7CC0`, where r6 is a copy of
its second parameter). None of the calls below `func_08124E74` is passed the caller's two pointers.

## Source notes

- `selector` and `mode` are `u32 : 8` bit-fields, as in `src/08123320.c`. The bytes do not pin that: with plain
  `u8 selector; u8 mode;` members the function compiles to the same 96 bytes, including the read-modify-write of the
  uninitialised first word at 0x081233A8-0x081233AE.
- `x` and `y` are plain `s16` members because their addresses are taken; `src/08123320.c` declares the same halfwords
  as `s32 : 16` bit-fields. The layout is the same. `src/08127B80.c` calls the record `Args08127B80` and declares its
  first parameter as `Owner08127B80 *`; here it is `void *context`.
- The `func_08124E74` prototype matches `src/08124E74.c`.
- This revision differs from the previous one on main only in names (`ScriptArguments`, `value`, following
  `src/08123320.c`) and the header comment; both compile to the same bytes (same SHA-256).

## Ruled out

- Earlier attempt (previous revision, earlier kit; not re-run here): the refusal was
  `unsupported stack-alias use or escape`, at the outgoing-argument store `str r4, [sp]` (0x081233C4). Kit 18dcc516
  accepts that store and stops later, in the callee chain above.
- No alternative spelling was needed for byte identity; the only variant compiled in this attempt is the plain-`u8`
  selector/mode layout above, which is also identical.

kit issue: (to be filed - buffer walk does not resolve a callback fixed by an intermediate buffer callee, 0x08099560 -> 0x080C7CC0 -> _call_via_r6)
