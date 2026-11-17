# 0x0811CA70 - scaling effect callback: a stack copy of an offset table and a BIOS BgAffineSet pair: bytes identical, refused (the stack-index selectors admit the table copy and stop at BgAffineSet; the BgAffineSet selectors stop at the copy) (556 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `u32 func_0811CA70(task, descriptor, payload)` is a phase callback (switch on `descriptor->phase`: 0, 1, 0x100 to
0x103) registered by its function word at 0x083953C8 in the ROM callback table. Phase 0 copies the 8-byte ROM table
`data_08149FA4` (four `u16` offsets) to the stack, reads the unit's position (`func_080DBDC8`) and facing
(`func_080DBC88`), adds `offsets[facing]` to x, starts an animation (`func_080D7A70(data_083A6D04, 2, task)`) and clears
16 bytes of `0x0600FFC0` (`func_08000B68`); 0x100 and 0x101 set up a BG sprite and a timeline (`func_080D49FC`,
`func_080D4B64(0, data_088F104C, 0xBA, 6)`, `func_080D3E9C(data_0894DB48)`, `func_080D4704(data_08949F18)`) and an
interpolation; 0x102 fills a local `BgAffineSrc` from the interpolation and the scale table `data_083A6D1C`, calls BIOS
BgAffineSet through `func_08141864(&src, &dst, 1)` and passes the local `dst` to `func_080032F8(&dst, 2)`; 0x103 waits
and cleans up.

```
0811CAAA  ldr  r1, =data_08149FA4
0811CAAC  add  r0, sp, #4
0811CAAE  movs r2, #8
0811CAB0  bl   0x081443FC        @ offsets
...
0811CC20  add  r4, sp, #0x20      @ dst (src is at sp+0x10)
0811CC22  adds r1, r4, #0
0811CC24  movs r2, #1
0811CC26  bl   0x08141864         @ BgAffineSet
0811CC2A  adds r0, r4, #0
0811CC2C  movs r1, #2
0811CC2E  bl   0x080032F8
```

## The index

`symbols/functions.txt` has `0811CA70 0811CC9C 556 278 return` and `config/functions.json` the same extent with 278 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 225 reachable instructions, so the instruction column is the halfword count (278). The selectors that compare it with the CFG are outside the families that fit this function: `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 other selectors (6) give `complete-owner text reachable instruction count differs`; `conditional-finite-local-word-loops-v1` and `conditional-finite-spilled-scalar-loops-v1` (2) give `finite loop exact instruction counts differ`.

## Byte identity

`0811CA70.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0811CA70, with every callee bound to its ROM address and every data word to the address its symbol names (28 `R_ARM_THM_CALL`, 11 `R_ARM_ABS32`). The 556-byte symbol equals the ROM span `[0x0811CA70, 0x0811CC9C)`: SHA-256 `3021e9f378b728c9014abccb9ea39ea09833a0e017c1bb947e8962f5cd7ee5c5` for both. `.text` is exactly 556 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149FA4": "0x08149FA4"`):

`data_08149FA4`, `data_083A6D04`, `data_083A6D1C`, `data_083A6D54`, `data_083A6D5C`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0811CA70.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 26 other addressed-runtime selectors (29) | `addressed data overflows or aliases indexed code` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-known-query-callee-v1` and 27 other selectors (30) | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `small-copy prefix excludes ordinary memory accesses` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 126 selector values are not listed one by one (none matched); by family: scheduler (25), callback and closure (21), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (4), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run (named data, direct calls) walks the copy destination into `func_081443FC` and stops at the
helper's alignment test: `buffer callee 0x081443FC: unsupported buffer pointer use or escape`. The two stack-index
selectors summarise this copy (an 8-byte constant copy into the frame is inside the ROM-table copy summary's limits)
and stop later, at the BIOS wrapper: `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG
verification`. The three BgAffineSet selectors summarise that wrapper but not the copy, and stop at `func_081443FC`.
No selector has both summaries.

The memcpy issue lists this function with the 15 stack-index callers whose next refusal, with its `memcpy` summary
on the plain path, is the register index into the copied table. Under the stack-index selectors the copy is already
admitted, and what stops it is BgAffineSet (#192's scalar-wrapper side). Once both are admitted, the index
`offsets[facing]` needs a premise row (bound 4) on `func_080DBC88(unit)`, the unit's facing byte, which is not known
to stay below 4.

## Source notes

From the attempt, not reviewed: `struct BgAffineSrc` and `struct BgAffineDst` are the SDK layouts; the copy
is the explicit `func_081443FC(offsets, data_08149FA4, sizeof(offsets))` at the top of phase 0, where the ROM performs
it.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors) (with BgAffineSet, kit #192, next under the stack-index selectors)
