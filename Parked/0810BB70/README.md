# 0x0810BB70 - projectile child callback with four stack copies of 3-byte ROM tables: bytes identical, refused (func_081443FC copies to the stack; the ROM-table copy summary refuses a dead second alias in R3) (816 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0810BB70(task, descriptor, state)` is the child callback that `0x0810BEA0` starts three times with
`func_08005B6C(func_0810BB70, 0xCC, &child, task)` (its function word is at 0x0810C08C). Phase 0 copies the start and end
points and the flag pointer out of the descriptor; 0x100 computes the direction with BIOS ArcTan2 (`func_08141860`) and
creates the projectile object (`func_080D5DD4(data_084FBE7C, 2, ...)`); 0x101 copies four 3-byte ROM tables to the
stack, computes the distance with BIOS Sqrt (`func_08141898`), indexes the four tables with `state->speed` and starts
the motion (`func_080D6334(&state->object, &start, &end, ..., x_values, y_values, ..., table_a[speed], value, task)`);
0x102 to 0x105 wait for it, spawn up to three trail objects at the projectile's position (`func_08011040(object, &x,
&y, &z)`, `func_080D5DD4(data_084FBA40, 3, ...)`) on the frames listed in `data_083A22E0`, and free everything.

```
0810BC78  ldr  r1, =data_08149F14
0810BC7A  add  r0, sp, #0x20
0810BC7C  movs r2, #3
0810BC7E  bl   0x081443FC        @ table_a
0810BC82  add  r4, sp, #0x24
0810BC84  ldr  r1, =data_08149F17
0810BC86  adds r0, r4, #0
0810BC88  movs r2, #3
0810BC8A  bl   0x081443FC        @ table_b, address kept in r4
0810BC8E  add  r3, sp, #0x28
0810BC90  mov  sl, r3            @ table_c, kept in r10
...
0810BCA4  bl   0x081443FC        @ table_d (0x0810BC98 for table_c), address in r8
```

`0x0810D728` is the same function for another effect.

## The index

`symbols/functions.txt` has `0810BB70 0810BEA0 816 408 return` and `config/functions.json` the same extent with 408 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 363 reachable instructions, so the instruction column is the halfword count (408). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0810BB70.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0810BB70, with every callee bound to its ROM address and every data word to the address its symbol names (21 `R_ARM_THM_CALL`, 7 `R_ARM_ABS32`). The 816-byte symbol equals the ROM span `[0x0810BB70, 0x0810BEA0)`: SHA-256 `82da0e430cecc084af1caac666bad58ae62a8b259bf1534aa2348cbbb505989a` for both. `.text` is exactly 816 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149F14": "0x08149F14"`):

`data_08149F14`, `data_08149F17`, `data_08149F1A`, `data_08149F1D`, `data_083A22E0`, `data_084FBA40`, `data_084FBE7C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0810BB70.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 14 other selectors (17) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (3) | `buffer callee 0x081443FC: copy helper receives only a destination alias and no stack-passed pointers` |

The other 189 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), callback and closure (22), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run (named data, direct calls) walks each destination alias into `func_081443FC` and stops at
the helper's alignment test: `buffer callee 0x081443FC: unsupported buffer pointer use or escape`. The ROM-table copy
summary, used by `named-data-buffer-rom-table-copy-v1` and both stack-index selectors, refuses the third copy:
`copy helper receives only a destination alias and no stack-passed pointers`. Instrumenting the summary's check (`tools/rom_table_copy_profile.py:168-169`) shows what it sees at each call:
the first two copies pass with the destination in R0 alone, and at the third (0x0810BC98) the destination
address is in R0 and in R3, because the compiler formed it in R3 (`add r3, sp, #0x28; mov sl, r3; mov r0, sl`).
No incoming or outgoing pointer word is live. The R3 copy is dead: the helper writes R3 before it reads it
(`adds r3, r1, #0` at 0x08144402). So what the copy summary refuses is the dead R3 alias, which the memcpy issue's
caller-side rule admits, not a pointer-bearing word.

The tables are then indexed with `state->speed`, a byte of the payload copied from the creator's descriptor, so a
stack-index proof also needs premise rows for that index (bound 3).

## Source notes

From the attempt, not reviewed: the four copies are explicit `func_081443FC(table, data_..., 3)` calls,
as in the matched siblings that copy ROM tables; the distance expression is written in full inside the
`func_08141898` call.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors); shubshub/fftadecomp-kit#200 (comment to be posted) (the ROM-table copy summary)
