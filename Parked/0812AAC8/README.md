# 0x0812AAC8 - name entry: add or delete a glyph, saving and restoring the name through a stack buffer with BIOS CpuSet: bytes identical, refused (a stack buffer as the CpuSet destination and then as the source; with a BIOS summary, named data beside the buffer proof) (320 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_0812AAC8(state)` handles the buttons of the name-entry screen; its caller is `func_0812A91C`
(0x0812AAA8). On A (`data_03000000.pressed & 1`) it calls `func_080023D0(&data_03000000)` and `func_08141540(0x64)`,
saves the 20-byte name at `state + 0x312` into a local buffer with BIOS CpuSet in copy
mode (`func_0814186C(state->name, saved, 10)`, ten halfwords), appends the glyph `func_0812B538(...)`, measures the name
with `func_0812B184` and, if it is too wide (`> 0x57`), copies the saved name back (`func_0814186C(saved, state->name,
10)` at 0x0812AB4A), else grows the length (at most 8); then it redraws (`func_0812AE8C`). On B (`pressed & 2`) it makes the
same two calls with 0x68, deletes the last glyph (or rewrites the terminator `0x40 0x73`) and redraws.

```
0812AAE6  ldr  r0, =0x312
0812AAE8  adds r6, r5, r0         @ state->name
0812AAEA  adds r0, r6, #0
0812AAEC  mov  r1, sp             @ saved
0812AAEE  movs r2, #0xa
0812AAF0  bl   0x0814186C         @ CpuSet copy: name -> stack
...
0812AB44  mov  r0, sp
0812AB46  adds r1, r6, #0
0812AB48  movs r2, #0xa
0812AB4A  bl   0x0814186C         @ CpuSet copy: stack -> name
```

## The index

`symbols/functions.txt` has `0812AAC8 0812AC08 320 130 return` and `config/functions.json` the same extent with 130 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 130 reachable instructions, so the row is right.

## Byte identity

`0812AAC8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0812AAC8, with every callee bound to its ROM address and every data word to the address its symbol names (10 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 320-byte symbol equals the ROM span `[0x0812AAC8, 0x0812AC08)`: SHA-256 `b7f886b9039b93e3fafaa11dfa66be1c4153e7a54c5877d28b015859649433eb` for both. `.text` is exactly 320 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0812AAC8.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and 10 other selectors (13) | `BIOS fill requires only a local R0 source and an external destination` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 18 other selectors (21) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1`, `descriptor-output-alias-v1`, `descriptor-single-store-v1` and 7 other selectors (10) | `buffer callee 0x0814186C: structural inventory is not closed` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `BIOS Sqrt requires exact complete svc #8; bx lr wrapper` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 143 selector values are not listed one by one (none matched); by family: scheduler (25), callback and closure (21), addressed-runtime (19), private float and double (15), switch-layout (13), owner (12), restoring-owner (9), canonical-integer (8), function-address (6), arithmetic-runtime (5), bounded-buffer (5), descriptor and preservation (2), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

The default run walks `saved` into the CpuSet wrapper and stops there: `buffer callee 0x0814186C: non-leaf calls
and interrupts require linked CFG verification`. The selectors that summarise CpuSet model a fill with a local source
and an external destination; here the first call copies into the stack buffer and the second copies out of it, and
they refuse: `BIOS fill requires only a local R0 source and an external destination` (the three BIOS fill selectors and
ten addressed BIOS runtimes).

The #192 comment's buffer-walk summary covers memory wrappers with a local destination or copy source; with it the
default path then meets its data gate (`buffer-call evidence does not support data relocations`,
`tools/match.py:6043-6044`), because the function reads the named `data_03000000`. The named-data issue reports `MATCH -
byte identical` with both, and this function is one of the six that need part (a) whichever way the BIOS summary is
placed. The #192 comment also cites it for the R0/R1-after-call question: after the second copy the branch target
writes R0 (`adds r0, r5, #0`) before its call, and R1 carried the external destination.

kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data)) (part a); shubshub/fftadecomp-kit#192 (comment to be posted)
