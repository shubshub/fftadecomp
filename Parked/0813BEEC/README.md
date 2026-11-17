# 0x0813BEEC - title screen load: BIOS CpuSet copy and fill, a tile map build and a palette copy through a callback: bytes identical, refused (a stack halfword as a CpuSet fill source) (112 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). `void func_0813BEEC(void)` loads a screen; its caller is `func_0813BCF0` (0x0813BD32). It copies 0x4D6 halfwords
of tiles from `data_089569F8` to `0x06000000` with BIOS CpuSet (`func_0814186C`, 0x0813BEF8), clears 0x400 halfwords of
the map buffer at `data_0200F3B4 + 1` with CpuSet in fill mode from a zero halfword on the stack (0x0813BF0C), builds the
map with `func_08135FA0(data_089564FC, data_0200F3B4 + 1, 600, 0x1E, 0)`, and copies 0x20 bytes of palette from
`data_089569AC` to `0x03003860` through the first callback of `data_0836D4BC` with `_call_via_r3` (`func_08142250`,
0x0813BF2E).

## The index

`symbols/functions.txt` has `0813BEEC 0813BF5C 112 35 return` and `config/functions.json` the same extent with 35 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 35 reachable instructions, so the row is right.

## Byte identity

`0813BEEC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0813BEEC, with every callee bound to its ROM address and every data word to the address its symbol names (4 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 112-byte symbol equals the ROM span `[0x0813BEEC, 0x0813BF5C)`: SHA-256 `984ab3cd19d86db95f346c57d9c15d212263283d2fa089a5bbf7d896f87004f7` for both. `.text` is exactly 112 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_089564FC": "0x089564FC"`):

`data_089564FC`, `data_089569AC`, `data_089569F8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0813BEEC.c` and the data symbols above added: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `bounded-buffer-runtime-summaries-v1` and 152 other selectors (155) | `function-address evidence does not support runtime call thunks` |

The other 56 selector values are not listed one by one (none matched); by family: private float and double (15), switch-layout (13), callback and closure (9), function-address (6), arithmetic-runtime (5), owner (3), restoring-owner (2), control-flow (1), -O0 (1), canonical-integer (1).

## Cause

The default run (named data, direct calls, and a `_call_via_r3` call that carries no local alias) walks the fill
source into the BIOS CpuSet wrapper and stops there: `buffer callee 0x0814186C: non-leaf calls and interrupts require
linked CFG verification`. The buffer selectors, the BIOS fill selectors and the addressed BIOS runtimes refuse the
callback call first: `function-address evidence does not support runtime call
thunks`.

Two routes are reported for it. With the BIOS summary in the buffer walk, the default path then meets its own data
gate (`buffer-call evidence does not support data relocations`, `tools/match.py:6043-6044`), so it needs named data
beside the buffer proof (the named-data issue's part a). With the fill summarised at the root call site instead, no
callee is inspected and the data gate is not met: the #192 comment lists it among the six that then give `MATCH - byte
identical` with no data composition.

## Source notes

From the attempt, not reviewed: the fill source is a nested block with a pointer local (`u16 zero; u16
*source = &zero; *source = 0;`); with a plain `zero = 0;` and `&zero` 12 halfwords differ, so the pointer is
load-bearing. Whether it stands for the SDK's fill macro or only steers registers is a review question; the source
rules refuse a temporary that only moves registers.

kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data)) (part a; or none with the root fill summary); shubshub/fftadecomp-kit#192 (comment to be posted) (the fill summary at root call sites)
