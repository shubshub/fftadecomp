# 0x0811E618 - three-unit effect callback with three stack copies of small ROM tables: bytes identical, refused (func_081443FC copies to the stack) (456 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811E618(parent, task, state)` is a phase callback (switch on `task->phase`: 0, 1, 0x100 to 0x102)
registered by its function word at 0x08395458 in the ROM callback table. Phase 0 starts an animation
(`func_080D7A70(data_083A734C, 2, parent)`) and gets three unit objects in a `u8` loop (`func_080DD34C`); 0x100 waits for
the animation; 0x101 copies three small ROM tables to the stack, `start[3]` from `data_08149FC4`, `finish[3]` from
`data_08149FC7` and `values[3]` (`u16`, 6 bytes) from `data_08149FCA`, with `func_081443FC` (0x0811E6B2, 0x0811E6BE,
0x0811E6CA), then in a `u8` loop over the three units, on the frame `start[i]` reads the unit's position into local
outputs (`func_080DBDC8(units[i], &x, &y)`) and creates an effect there (`func_080D5CC0(data_084FAAA4, ...)`,
`func_08011198`, `func_080DFD8C(data_083A7364, ...)`), and on the frame `finish[i]` stores `values[i]` into the unit
record (`func_080DD350(...)->value`) and calls `func_080DE390`; 0x102 waits for the effects (`func_080D5F24`). The
tables are indexed by the loop counter.

## The index

`symbols/functions.txt` has `0811E618 0811E7E0 456 228 return` and `config/functions.json` the same extent with 228 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 197 reachable instructions, so the instruction column is the halfword count (228). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0811E618.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811E618, with every callee bound to its ROM address and every data word to the address its symbol names (14 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 456-byte symbol equals the ROM span `[0x0811E618, 0x0811E7E0)`: SHA-256 `178ecd644b9453b9ff461d9ca7fe5495283f214f2b3883c2a1a95cd2ac2b01e9` for both. `.text` is exactly 456 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149FC4": "0x08149FC4"`):

`data_08149FC4`, `data_08149FC7`, `data_08149FCA`, `data_083A734C`, `data_083A7364`, `data_084FAAA4`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811E618.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1`, `named-data-buffer-dead-argument-aliases-v1` and 24 other selectors (27) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `inconsistent possible pointer offsets at control-flow join` |

The other 179 selector values are not listed one by one (none matched); by family: addressed-runtime (40), scheduler (25), callback and closure (21), private float and double (15), BIOS buffer (13), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (4), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run (named data, direct calls) walks the first copy's destination into `func_081443FC` and stops at
the helper's alignment test: `buffer callee 0x081443FC: unsupported buffer pointer use or escape`. The stack-index
selectors summarise the three copies (constant counts of 3, 3 and 6 into the frame are within the ROM-table copy
summary's limits) and stop later: `named-data-buffer-stack-index-v1` at the coordinate wrapper
(`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`, the wrapper forwards one pointer as its
callee's stack argument), `-v2`, which forwards, at `inconsistent possible pointer offsets at control-flow join`.

So the copies are not what stops the stack-index selectors here; the memcpy issue lists this function with the 15
stack-index callers whose copy the ROM-table summary should host, which agrees. The table indices are the loop
counter, bounded by the loop.

## Source notes

From the attempt, not reviewed: the three copies are explicit `func_081443FC` calls with literal counts
(3, 3, 6); the attempt did not try natural initialised local arrays (`u8 start[3] = {...}`), which would make the
compiler emit the copies from `.rodata` instead.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
