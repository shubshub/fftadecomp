# 0x080CD2C4 - ability-range points test: bytes identical, refused by the verifier (stack outputs of an inlined accessor, no buffer call) (158 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function takes a unit record and an id. It gets the
first and last index of the id's range with two calls `func_080C8570(id, id, 0x25)` and `func_080C8570(id, id, 0x26)`
(0x080CD2E4, 0x080CD2F4), writes both bytes to the stack slots `sp` and `sp+1` (0x080CD2FE, 0x080CD302), and loads the
table row `g_table_0851BA84[unit[6]]` (0x080CD304-0x080CD30A): this is the body of the matched `func_080CD428`,
inlined, with the two slots as its output arguments. It then walks the index from first to last: when the type byte of
8-byte entry `i` (offset 6, 0x080CD31C) is nonzero and the unit's byte at `0x40 + i` masked with 0x7F
(0x080CD322-0x080CD336) is below the entry's required byte (offset 7, read through a fresh `g_table_0851BA84[unit[6]]`
lookup at 0x080CD32C-0x080CD338, the body of the matched `func_080CD480`), it returns 0; after the last index it
returns 1. The index row `080CD2C4 080CD362 158 79 return` has the right extent, but its instruction column is wrong:
79 is the halfword count of the span. The span holds 74 instructions (two of them `bl`), one `0000` alignment halfword
at 0x080CD342 and the literal word at 0x080CD344. `g_table_0851BA84` is already in `config/data_symbols.json`; no new
data symbol is needed.

## Byte identity

`080CD2C4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080CD2C4, with both calls bound to `func_080C8570`
(0x080C8570) and the pool word to `g_table_0851BA84` (0x0851BA84) (2 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 158-byte
symbol equals the ROM span `[0x080CD2C4, 0x080CD362)`: SHA-256
`7f4ce92e51fa418f0630001ef7745f40d23a0345c4a88bde9cbf5fbd91405dff` for both. `.text` is 160 bytes: the symbol and a
trailing `c046` alignment halfword, where the ROM has `0000` before the next function at 0x080CD364. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080CD2C4.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default | `stack-buffer evidence requires an inspected buffer call` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `inconsistent stack aliases at control-flow join` |
| `named-data-buffer-v1`, `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-rom-table-copy-v1` and 15 other `named-data-buffer-*` / `bounded-buffer-*` selectors (18) | `named-data buffer profile requires exact inspected buffer calls` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` (2) | `stack index: no variable stack index access to prove` |
| `conditional-known-query-stack-buffer-v1` | `known-query caller private access must be an aligned word` |
| the nine `static-callback-*-aligned-v1` selectors (9) | `structural inventory is not closed` |
| `entry-recursive-ordinary-call-v1` | `refused: entry saved-only owner excludes local frames and stack-address materialization` |
| `canonical-integer-two-words-aligned-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` |
| `canonical-integer-scalar-data-source-v1`, `canonical-integer-private-locals-data-source-v1`, `canonical-integer-six-words-data-source-v1`, `canonical-integer-two-words-data-source-v1` and 28 other owner selectors (restoring-owner, static-callback, descriptor, output-word and local-table families) (32) | `owner requires sole complete Thumb ELF function` |

The 32 owner selectors in the last row refuse the trailing `c046` alignment halfword: the symbol is 158 bytes and
`.text` 160, and `owner_admission_profile.py:1047-1053` admits that pad only for its alignment-aware selectors. The
aligned variants (the static-callback `*-aligned-v1` selectors and
`canonical-integer-two-words-aligned-data-source-v1`) accept it and stop on their own contracts. The other 148
selector values stop on requirements this function does not meet: an arithmetic, float or double runtime, a switch, a
BIOS wrapper call, a scheduler, known-query or callback-closure contract, a function-address thunk, a finite or
counted loop shape, a palette bundle, or the -O0 toolchain.

## Cause

`match.py` first verifies the function on the ordinary call path (`verify_leaf_instructions`, `match.py:6017-6021`).
That pass fails at the join 0x080CD348 with `inconsistent stack aliases at control-flow join` (`match.py:5085-5092`),
which the default run does not print (the `--control-flow-profile mixed-return-inert-spin-v1` run stops with the same
message): on the path from the `beq` at 0x080CD320 in the first iteration, r1 still holds `sp` (`mov r1, sp` at
0x080CD30C, used by `ldrb r3, [r1]` to read the first index), and on the path from 0x080CD33C it holds 0x7F
(0x080CD32A). r1 is dead there: every path from 0x080CD348 writes it before reading it (`movs r1, #0x7f` at 0x080CD32A
in the loop, `pop {r1}` at 0x080CD35E on exit). The kill proof `stack_alias_overwritten_before_use` (`match.py:3033`)
cannot show that, because the path 0x080CD348 -> 0x080CD350 -> 0x080CD318 -> 0x080CD320 -> 0x080CD348 is a cycle that
neither reads nor writes r1, and the proof deliberately does not accept such cycles (`match.py:3078`). `match.py` then
retries with a stack-argument buffer proof (`match.py:6022-6028`), under which the join check does not apply
(`match.py:5085`), but that evidence is only admitted when it has inspected a buffer call (`match.py:6041-6042`). No
call here receives a stack address: the two slots are written directly by the inlined accessor, so the run ends with
`stack-buffer evidence requires an inspected buffer call`.

## Source notes

- `ability_range` is an inlined copy of `func_080CD428` (`src/080CD428.c`), statement for statement. It declares
  `func_080C8570` as returning `u32`, as `src/080C8570.c` defines it, and narrows each result to `u8` by assignment;
  `src/080CD428.c` declares the same callee as returning `u8` with an `int` third parameter. That declaration gives
  the same 158 bytes here (the `lsls`/`lsrs #24` pairs at 0x080CD2EA-0x080CD2EC and 0x080CD2F8-0x080CD2FA either way),
  so the bytes do not choose between them.
- `ability_info` is not a verbatim copy of `func_080CD480` (`src/080CD480.c`), which returns
  `g_table_0851BA84[first] + second * 8` on a `const u8 *`. Here it indexes 8-byte `AbilityInfo` entries. Spelling it
  the way `src/080CD480.c` does (byte pointer plus `second * 8`, cast to `AbilityInfo *`) gives the same 158 bytes, so
  the bytes do not choose between the two.
- The second table lookup is in the ROM: the required-points byte is read through a row reloaded every iteration
  (0x080CD32C-0x080CD332), while the type byte uses the row loaded once after the calls (r6). Reading
  `abilities[i].required_points` instead gives a 146-byte symbol with 80 bytes differing from 0x080CD304.
- `AbilityInfo *info = &abilities[i];` is used once. Without it (`abilities[i].type`) one byte differs: the ROM adds
  row plus offset, `adds r0, r6, r4` at 0x080CD31A, and the variant emits `adds r0, r4, r6`. AGENTS.md does not ship a
  spare temporary, so before this could ship the pointer needs that ROM evidence in a comment at the declaration; the
  source has none.
- The return type is not pinned: `u8` and `u32` give the same bytes (the ROM returns the constants 0 and 1).
- `Unit` names only the job byte (offset 6) and the points bytes from offset 0x40; `ability_points` is a zero-length
  array because its length is not recovered.

## Ruled out

- The previous revision of this entry (a `const u8 *` object and the second table access written inline as
  `g_table_0851BA84[object[6]][index * 8 + 7]`) is not byte-identical: a 154-byte symbol, with 66 bytes differing from
  0x080CD304 on (this attempt's run). Its README called it byte-identical, but `match.py` had refused before comparing
  and no hand link was reported.
- Reusing the hoisted row for the required-points byte: 146 bytes, 80 differ (above).
- Dropping the `info` pointer: one byte differs at 0x080CD31A (above).

kit issue: (to be filed - stack outputs of an inlined accessor: join alias kill proof across a loop cycle, and stack evidence without a buffer call)
