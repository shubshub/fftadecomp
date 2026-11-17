# 0x08107DA8 - effect launch callback with a stack copy of a 64-byte offset table: bytes identical, refused (a 64-byte func_081443FC copy to the stack; the ROM-table copy summary admits 1 to 15 bytes) (834 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_08107DA8(owner, event, w)` is the phase callback (switch on `event->phase`: 0, 1, 0x100 to 0x104) of a
task created by `func_081080EC`, whose pool holds its function word (0x08108204). It is `0x081074D8` with other
constants: the effect is `func_080D5E80(data_08507114, 0, x, y, z, 0x3F7, 9)`, the target height offset is 0x10, the
sequence is `data_083A0ED4`, and the offsets come from a stack copy of the 64-byte ROM table `data_08149E9C`
(`Position[2][4]`, 8-byte entries) made with `func_081443FC` twice:

```
08107E76  add  r0, sp, #0x18
08107E78  ldr  r1, =data_08149E9C
08107E7A  movs r2, #0x40
08107E7C  bl   0x081443FC        @ second copy at 0x08107F88, same operands
```

read back as `table[part][mode]`, both bytes of the work area. The travel time is computed from two BIOS Sqrt calls
(`func_08141898`) and a Div by 5 (`func_08141870`), clamped to 3..0x3B; phases 0x101 to 0x104 wait on the motion
(`func_080D63C8`, `func_080D6478`, `func_080D6530`) and free the effect (`func_08011428`).

## The index

`symbols/functions.txt` has `08107DA8 081080EA 834 417 return` and `config/functions.json` the same extent with 417 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 378 reachable instructions, so the instruction column is the halfword count (417). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-switch-aligned-v1` and `restoring-owner-switch-cycles-function-words-v1` (2) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`08107DA8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08107DA8, with every callee bound to its ROM address and every data word to the address its symbol names (24 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 834-byte symbol equals the ROM span `[0x08107DA8, 0x081080EA)`: SHA-256 `01ac7ef8a57f439c1cd6541a034bf3b7e5ffef0af2f2876ca0010602ff9224b1` for both. `.text` is 836 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149E9C": "0x08149E9C"`):

`data_08149E9C`, `data_083A0ED4`, `data_08507114`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08107DA8.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 13 other selectors (16) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (3) | `buffer callee 0x081443FC: copy source must be a constant literal and the count an exact constant from 1 to 15` |

The other 190 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

As for `0x081074D8`: the default path enters `func_081443FC` with the destination alias and stops at the
helper's alignment test (`unsupported buffer pointer use or escape`); the ROM-table copy summary used by
`named-data-buffer-rom-table-copy-v1` and both stack-index selectors admits counts from 1 to 15 only, and this copy
is 64 bytes. After the copy, the index `[part][mode]` needs premise rows; `mode` is `func_080DBC88(object)`, the unit
object's facing byte, which is not known to stay below 4.

## Source notes

Recorded by the attempt, not reviewed:

- The helper parameter types differ for the same two values (`create_effect` takes `u16`, `offset_position` `int`,
  `start_motion` `u8`); the choice only decides an `r8`/`r9` swap.
- `length = f(); length >>= 4;` is split in two statements, the square accumulates, and `time += 12` is separate.
- The four `static inline` helpers are inferred from the code shape; the sibling `0x081074D8` (parked) has the same
  helpers with different spellings.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors); shubshub/fftadecomp-kit#200 (comment to be posted) (the ROM-table copy summary, counts above 15)
