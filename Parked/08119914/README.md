# 0x08119914 - ability animation task with a facing-indexed offset table: bytes identical, held on evidence (stack-index premise unproven) (882 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_08119914(task, descriptor, payload)` is an
animation task callback: a switch on `descriptor->phase` (0, 1, 0x100-0x106) that spawns and polls child tasks,
sprites, windows and timelines for one ability effect and sets the phase to 2 to finish. In phase 0x101 it
copies a 16-byte table of four `{s16 x, s16 y}` offsets from the ROM at 0x08149F78 to the stack (`ldm`/`stm` at
0x081199F8-0x08119A02) and indexes it with the actor's facing, `func_080DBC88(payload->object)` (`ldrb [r0, #0x1F]`,
sign-extended; `bl` at 0x08119A0E, index scaled at 0x08119A14-0x08119A16, loads at 0x08119A1C and 0x08119A26). The
only word in the ROM that points at the function is at 0x08395228 (task-table entry 330, id 0x14B, as identified in the earlier attempt). The index row
`08119914 08119C86 882 441 return` is right as to extent, but its instruction count is the halfword count
(882 / 2); the function has 361 reachable instructions (39 `bl`) and 19 literal words. It needs 11 data symbols that
are not in `config/data_symbols.json` on main: `data_083A6410`, `data_083A6458`, `data_083A6488`, `data_083A649C`,
`data_083A64A0`, `data_083A64A4`, `data_083A64AC`, `data_083A64B4`, `data_088F58E0`, `data_0894BE84` and
`data_0894BEAC`, each at the address its name gives.

## Byte identity

`08119914.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08119914, with every callee and data symbol bound to
its ROM address (39 `R_ARM_THM_CALL`, 19 `R_ARM_ABS32`) and the source's 16-byte `.rodata` (the offset table
initialiser) placed at 0x08149F78, the address the ROM's pool word at 0x08119A78 loads. The compiled `.rodata` equals
the ROM's 16 bytes there (`0400feff0400fefffcfffefffcfffeff`, i.e. `{4, -2}, {4, -2}, {-4, -2}, {-4, -2}`). The
882-byte symbol equals the ROM span `[0x08119914, 0x08119C86)`: SHA-256
`2dda2c38b4be5ff35180c8d53ac5fe593b632c1b47fb3c907f1ec5996fdbdb7f` for both. `.text` is 884 bytes, the symbol plus
the `c046` alignment pad. `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08119914.c`. Only the default run and the
two stack-index selectors, the ones that apply, were run on this attempt.

| Run | Result |
|---|---|
| default, main's `config/data_symbols.json` | `compile failed: unexpected nonempty allocated section` |
| `--owner-runtime-profile named-data-buffer-stack-index-v1` or `-v2`, main's data symbols | `unmapped or non-object owner literal` |
| default, with the 11 data symbols added | `compile failed: unexpected nonempty allocated section` |
| `--owner-runtime-profile named-data-buffer-stack-index-v1`, with the 11 data symbols | `stack index: index range is not 2-byte aligned on every path; index is not provably 2-byte aligned` |
| `--owner-runtime-profile named-data-buffer-stack-index-v2`, with the 11 data symbols | `stack index: the premise rows of 0x08119914 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)` |
| `-v2`, with the 11 data symbols and an entry for exactly those rows in a local copy of the tree | `MATCH - byte identical` (the volatile `g_control_flags_03000940` semantics check agrees on 26 paths) |

The rows the v2 selector generates for the entry are:

- site `0x08119A1C`, expression `(u32)((ret(0x08119A0E) << 24) >>s 22)`, bound 15
- site `0x08119A26`, the same expression, bound 13

The entry used for that last run was not kept. `config/stack_index_premises.json` holds one entry per function with
a written review that every execution keeps each index below its bound (kit README, "A premise admits nothing until
it is reviewed"); no such review can be written here.

## Cause

The bounds hold only if the facing byte is 0..3 whenever phase 0x101 runs, and that is not shown; it is
contradicted. `func_0809D6BC` (the direction of a tile difference) returns -1 for a zero vector: none of its four
direction tests (0x0809D73E-0x0809D788) matches (0, 0), and it falls through to `movs r0, #1; rsbs r0, r0, #0` at
0x0809D78A. Four writers store its result into a facing field with no guard against coincident positions:

- `func_08109990` at 0x08109A56: `func_080DBC90(target, (s8)func_080DBCD4(actor, target))`, where `func_080DBCD4`
  ends in `func_0809D6BC` (0x080DBD1A) and `func_080DBC90` is `strb r1, [r0, #0x1f]`;
- `func_080DF14C` at 0x080DF1F8: `func_080DE12C(unit, 0x3C, (s8)func_0809D6BC(...))` (call at 0x080DF1EA);
- `func_080F9B14` at 0x080F9F0E: `func_080DBC90` with a byte from a 4-byte stack table indexed by the
  `func_0809D6BC` result, so -1 reads outside that table;
- `func_080B55CC` at 0x080B56DA: `strb` of the `func_0809D6BC` result (0x080B56D2) to record `+0xF8`, a facing field
  that feeds the unit's `+0x1F`.

Many other writers of `+0x1F` are bounded (event-script data, the zero fill at allocation, wrap-around steps) and
several more feeding sources (record `+0xF8`, actor `+0x3E`, task-payload bytes) are not traced to the end, but these
four paths alone depend on whether the game can ever run them with both positions on one tile, which the ROM's code does not
decide. With facing -1 the two loads here would read `sp+0x10` and `sp+0x12`, the outgoing-argument word below the
table (written only in phase 0x100, at 0x081199D8). The same premise, at their own sites, holds back `0x080F7720`
(sites 0x080F7858/0x080F7862) and `0x080FDB98` (sites 0x080FDCB4/0x080FDCBE; both site pairs from the earlier
attempt).

## Source notes

- `.rodata`: the table is a local initialiser, `Offset08119914 offsets[4] = { {4, -2}, {4, -2}, {-4, -2}, {-4, -2} };`,
  which agbcc places in `.rodata` and copies with `ldm`/`stm`. The same 16 bytes also occur at 0x08149D4C; the pool
  word fixes 0x08149F78 as the one this function copies.
- `func_080035A8` is declared `u16 (u8)`; it is used as a display-bit mask for `g_control_flags_03000940.display`.
- The operand order `payload->x + offsets[facing].x` is not pinned by the bytes (`adds r3, r3, r4` at 0x08119A20 is
  commutative).
- `func_080DD748`'s fourth parameter (`s16 *`) is copied from `src/081171CC.c`; this function passes 0.
- The structs are local offset views (`Descriptor08119914`, `Payload08119914`); their full extents are unknown.

## Ruled out

Nothing beyond the source above was needed for byte identity: the C body is unchanged from main's previous revision,
which only lacked the target bytes in its header comment. The hold is on evidence, not on the source: the next step is
a proof (or a ROM-data argument) that abilities 0x117, 0x7C and 0x142, the `func_080DF14C` task and `func_080B55CC`
never run with coincident positions, or a kit profile that does not need the 0..3 bound.

kit issue: none (not a verifier gap; the stack-index premise needs evidence)
