# 0x081074D8 - effect launch callback with a stack copy of a 64-byte offset table: bytes identical, refused (a 64-byte func_081443FC copy to the stack; the ROM-table copy summary admits 1 to 15 bytes) (834 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_081074D8(task, event, state)` is the phase callback (switch on `event->phase`: 0, 1, 0x100 to
0x104) of a task created by `func_0810781C`, whose pool holds its function word (0x08107934). Phase 0 records the actor,
its unit object (`func_080DD47C`), the object's position (`func_080DBD5C`) and facing (`func_080DBC88`) and the target
position (`func_080D8B7C`). Phase 0x100 creates the effect object (`func_080D5E80(data_08507114, ...)`, then
`func_08010884`, `func_0801115C`, `func_0801121C`) at the actor's position plus an offset from a table, computes a
travel time from the distance (two BIOS Sqrt calls through `func_08141898`, one Div by 5 through `func_08141870`,
clamped to 3..0x3B) and starts the motion with `func_080D6238`. Phases 0x101 to 0x104 wait on the motion
(`func_080D63C8`, `func_080D6478`, `func_080D6530`), hand a status byte to the creator and free the object
(`func_08011428`).

The offset comes from a stack copy of the 64-byte ROM table `data_08149E5C` (eight 8-byte `{x, y, z, pad}` entries,
`[variant][facing]`), made with `func_081443FC` twice, once per position computed:

```
081075A6  add  r0, sp, #0x18
081075A8  ldr  r1, =data_08149E5C
081075AA  movs r2, #0x40
081075AC  bl   0x081443FC        @ second copy at 0x081076B8, same operands
```

and read back with a variable index (`variant` and `facing` are bytes of the state). The sibling `0x08107DA8` is the
same function with other constants and table.

## The index

`symbols/functions.txt` has `081074D8 0810781A 834 417 return` and `config/functions.json` the same extent with 417 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 378 reachable instructions, so the instruction column is the halfword count (417). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-switch-aligned-v1` and `restoring-owner-switch-cycles-function-words-v1` (2) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`081074D8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081074D8, with every callee bound to its ROM address and every data word to the address its symbol names (24 `R_ARM_THM_CALL`, 3 `R_ARM_ABS32`). The 834-byte symbol equals the ROM span `[0x081074D8, 0x0810781A)`: SHA-256 `84b7f994b605bf59bc6e953ea11f492900a17b6b574018dd4027655ba04579c1` for both. `.text` is 836 bytes: the symbol and the assembler's `c0 46` alignment halfword. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149E5C": "0x08149E5C"`):

`data_08149E5C`, `data_083A0D20`, `data_08507114`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081074D8.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 13 other selectors (16) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (3) | `buffer callee 0x081443FC: copy source must be a constant literal and the count an exact constant from 1 to 15` |

The other 190 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), callback and closure (23), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default path follows the destination alias into `func_081443FC` and stops at the helper's alignment test
(`orrs r0, r5` at 0x0814440A), where the alias is used as a number: `unsupported buffer pointer use or escape`. The only
proof that summarises this helper, the ROM-table copy summary of `named-data-buffer-rom-table-copy-v1` and the two
stack-index selectors, requires a count from 1 to 15; this copy is 64 bytes (`movs r2, #0x40`), so those three
selectors refuse at the same call with `copy source must be a constant literal and the count an exact constant from 1
to 15`. A 64-byte copy takes the helper's word path, which needs a stronger helper proof than the byte path the kit
authenticates.

Once the copy is admitted, the stack index `table[variant][facing]` needs premise rows (`variant` < 2, `facing` < 4).
`facing` is `func_080DBC88(object)`, the signed facing byte at unit object +0x1F, and that byte is not known to stay
below 4 (a zero direction vector stores -1 on several ROM paths). So the function would not ship on a premise for
it either until that is settled.

## Source notes

Recorded by the attempt, not reviewed:

- `dx` and `dz` are `s32` and `dy` is `s16`; the choice only decides an `r8`/`r9` assignment.
- The position fields are `u16` with `(s16 *)` casts at the `func_080DBD5C` call.
- The four `static inline` helpers (`place`, `launch`, `travel`, `create`) are inferred from the code shape; each does a
  domain operation (a table offset, a motion start, a distance, an object creation), but no matched sibling shares the
  text (the sibling `0x08107DA8` is parked too, with its own spellings).
- The square accumulation is three statements.

kit issue: shubshub/fftadecomp-kit#240; shubshub/fftadecomp-kit#200 (comment) (the ROM-table copy summary, counts above 15)
