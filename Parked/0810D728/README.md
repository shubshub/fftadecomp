# 0x0810D728 - ring child callback with four stack copies of 3-byte ROM tables: bytes identical, refused (func_081443FC copies to the stack; the ROM-table copy summary refuses a dead second alias in R3) (816 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0810D728(task, command, state)` is the child callback that `0x0810DA58` starts three times in a loop
with `func_08005B6C(func_0810D728, 0xCC, &child, task)` (its function word is at 0x0810DC90). It is `0x0810BB70` for
another effect: phase 0x100 computes the direction with BIOS ArcTan2 (`func_08141860`) and creates the sprite
(`func_080D5DD4(data_0850873C, 0, ..., 0x3FD, 6, 0)`); phase 0x101 copies the 3-byte ROM tables `data_08149F24`,
`data_08149F27`, `data_08149F2A` and `data_08149F2D` to the stack, computes the distance with BIOS Sqrt
(`func_08141898`), indexes the tables with `state->value` and starts the motion with `func_080D6334`; phases 0x102 to
0x105 wait, spawn up to three rings at the sprite's position (`func_08011040(sprite, &x, &y, &z)`) on the frames listed
in `data_083A2920`, and free everything.

```
0810D830  ldr  r1, =data_08149F24
0810D832  add  r0, sp, #0x20
0810D834  movs r2, #3
0810D836  bl   0x081443FC        @ a
0810D83A  add  r4, sp, #0x24
0810D83E  adds r0, r4, #0
0810D842  bl   0x081443FC        @ b, address kept in r4
0810D846  add  r3, sp, #0x28
0810D848  mov  sl, r3
0810D850  bl   0x081443FC        @ c, address kept in r10
0810D854  add  r0, sp, #0x2c
0810D856  mov  r8, r0
0810D85C  bl   0x081443FC        @ d, address in r8
```

## The index

`symbols/functions.txt` has `0810D728 0810DA58 816 408 return` and `config/functions.json` the same extent with 408 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 362 reachable instructions, so the instruction column is the halfword count (408). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0810D728.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0810D728, with every callee bound to its ROM address and every data word to the address its symbol names (21 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 816-byte symbol equals the ROM span `[0x0810D728, 0x0810DA58)`: SHA-256 `dd248fd08ac6fb6efff19eba5f29a308937ae21d308c9a7e9626f33343563e82` for both. `.text` is exactly 816 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149F24": "0x08149F24"`):

`data_08149F24`, `data_08149F27`, `data_08149F2A`, `data_08149F2D`, `data_083A2920`, `data_0850873C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0810D728.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 14 other selectors (17) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (3) | `buffer callee 0x081443FC: copy helper receives only a destination alias and no stack-passed pointers` |

The other 189 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

As for `0x0810BB70`: the default run stops inside `func_081443FC` at the helper's alignment test
(`unsupported buffer pointer use or escape`), and the ROM-table copy summary of `named-data-buffer-rom-table-copy-v1`
and both stack-index selectors refuses the third copy with `copy helper receives only a destination alias and no
stack-passed pointers`. Instrumenting the summary's check (`tools/rom_table_copy_profile.py:168-169`) shows what it sees at each call:
the first two copies pass with the destination in R0 alone, and at the third (0x0810D850) the destination
address is in R0 and in R3, because the compiler formed it in R3 (`add r3, sp, #0x28; mov sl, r3; mov r0, sl`).
No incoming or outgoing pointer word is live. The R3 copy is dead: the helper writes R3 before it reads it
(`adds r3, r1, #0` at 0x08144402). So what the copy summary refuses is the dead R3 alias, which the memcpy issue's
caller-side rule admits, not a pointer-bearing word. The tables are indexed with `state->value`, a byte copied from the creator's
descriptor, so a stack-index proof also needs premise rows for it (bound 3).

## Source notes

From the attempt, not reviewed: the four copies are explicit `func_081443FC(a, data_..., 3)` calls; in
phase 0x105 the freed sprite pointer is cleared with the motion task's zero result (`state->sprite = next`), which is
what the ROM stores there.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors); shubshub/fftadecomp-kit#200 (comment to be posted) (the ROM-table copy summary)
