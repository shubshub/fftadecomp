# 0x080BDA30 - exchange sort of four-byte records by a two-field score: bytes identical, refused by the verifier (stack temporary passed to func_081443FC) (202 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function sorts `count` four-byte records in place. The
two byte parameters arrive as `u8` (0x080BDA40-0x080BDA46) and are compared as `s8` (0x080BDA54-0x080BDA56,
0x080BDA70-0x080BDA72). For each record `i` below `count - 1` it computes the score
`|records[i].first - first| - |records[i].second - second|` (0x080BDA5A-0x080BDA7E), then for every later record `j`
the same score; when the running score is below record `j`'s, it swaps records `i` and `j` through a four-byte stack
temporary with three calls to `func_081443FC` (`memcpy`, `src/081443FC.c`): `sp` as the destination
(0x080BDAB8-0x080BDABE), `&records[i]` from `&records[j]` (0x080BDAC2-0x080BDAC8), and `sp` as the source
(0x080BDACC-0x080BDAD2). It then takes record `j`'s score as the running score. The index row
`080BDA30 080BDAFA 202 101 return` has the right extent, but its instruction column is wrong: 101 is the halfword
count of the span. The span holds 98 instructions, three of them four-byte `bl`, and no literal pool. No data symbol
is needed.

## Byte identity

`080BDA30.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080BDA30, with the three calls bound to `func_081443FC`
(0x081443FC) (3 `R_ARM_THM_CALL`). The 202-byte symbol equals the ROM span `[0x080BDA30, 0x080BDAFA)`: SHA-256
`a5dc0eb214c0b2eb0b32ce00ce12e6845899b4189e4fb35295e87c48c60e0c02` for both. `.text` is 204 bytes: the symbol and a
trailing `c046` alignment halfword, where the ROM has `0000` before the next function at 0x080BDAFC. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080BDA30.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-root-return-scratch-v1` and 13 other `named-data-buffer-*` / `bounded-buffer-*` selectors, and the nine `static-callback-*-aligned-v1` selectors (28) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` (3) | `buffer callee 0x081443FC: copy source must be a constant literal and the count an exact constant from 1 to 15` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `conditional-known-query-stack-buffer-v1` | `private stack address or saved value passed to a call` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |
| `entry-recursive-ordinary-call-v1` | `refused: entry saved-only owner excludes local frames and stack-address materialization` |
| `canonical-integer-scalar-data-source-v1`, `restoring-owner-acyclic-v1`, `static-callback-buffer-v1`, `descriptor-output-alias-v1` and 28 other owner selectors (canonical-integer data-source, restoring-owner, static-callback, descriptor, output-word and local-table families) (32) | `owner requires sole complete Thumb ELF function` |

The 32 owner selectors in the last row refuse the trailing `c046` alignment halfword (a 202-byte symbol in 204 bytes
of `.text`); the aligned static-callback variants accept it and stop on the buffer walk instead. The other 146
selector values stop on requirements this function does not meet: an arithmetic, float or double runtime, a switch, a
BIOS wrapper call, a scheduler, known-query or callback-closure contract, a function-address thunk, a finite or
counted loop shape, a palette bundle, or the -O0 toolchain.

## Cause

`sp` is passed to `func_081443FC` twice, as the destination (r0, 0x080BDAB8) and as the source (r1, 0x080BDACE), so
the buffer walk follows the stack alias into `memcpy`'s body. There it reaches the alignment test
`adds r0, r3, #0; orrs r0, r5` at 0x08144408-0x0814440A, which ORs the destination pointer (an alias of the caller's
stack slot, copied into r5 at 0x081443FE) with the source pointer. The walk admits an alias register only in the forms
it tracks (a memory base, an alias copy) and refuses this read (`match.py:3626-3627`). The test sits on the word-copy
path, which `memcpy` takes only when the size exceeds 15 (`cmp r2, #0xf; bls` at 0x08144404-0x08144406); every call
here passes 4 (`movs r2, #4`), so at run time the byte loop at 0x08144448-0x08144454 is the only path taken, but the
walk does not use the constant size to drop the other branch. `rom_table_copy_profile.py:1-24` describes this refusal
and summarises a copy only when R1 is a constant read from a code literal (a ROM table), R2 an exact constant from 1
to 15 and R0 the only stack alias passed. No call here copies from a ROM table: the first copies from `&records[i]`, a
RAM pointer derived from an argument, and the third passes the stack temporary in R1, so
`named-data-buffer-rom-table-copy-v1` and the two stack-index selectors refuse the copy.

## Source notes

- `last = count - 1` is a local ahead of the loop, with a comment: the ROM computes `count - 1` once (`subs r1, #1` at
  0x080BDA4A) before `i = 0` (`movs r5, #0` at 0x080BDA4E), keeps it at `sp+0x10` (0x080BDA4C) and reloads it for the
  outer bottom test (0x080BDAE4). Written as `i < count - 1` in the loop condition, the function grows to 208 bytes
  (below).
- Each absolute value is taken right after its subtraction (0x080BDA64-0x080BDA6A, then 0x080BDA74-0x080BDA7C; the
  inner loop has the same order at 0x080BDA9C-0x080BDAB0). Computing both differences first and then both absolute
  values gives 200 bytes (below).
- `Record080BDA30` names only the two bytes the function reads (`ldrb` at 0x080BDA60 and 0x080BDA6C); bytes 2-3 are
  moved only by the copies and stay `unknown_02`. The score is the difference of the two distances, as the ROM
  computes it (`subs r2, r3, r0` at 0x080BDA7E); it is not a sum.
- The swap is three `memcpy` calls of `sizeof(temp)` (4). A struct assignment was not tried.

## Ruled out

All results below are from this attempt's runs, hand-linked as above.

- The previous revision of this entry (`index < count - 1` in the outer loop condition, both differences computed
  before both absolute values): a 204-byte symbol, with 173 of the 202 bytes differing from 0x080BDA3A on. Its README
  recorded the same `unsupported buffer pointer use or escape` refusal and claimed no byte match.
- This source with only the loop condition changed to `i < count - 1`: 208 bytes, 139 bytes differ from 0x080BDA3E.
- This source with only the absolute values grouped after both subtractions: 200 bytes, 165 bytes differ from
  0x080BDA3A.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
