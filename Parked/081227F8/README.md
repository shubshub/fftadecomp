# 0x081227F8 - script command: project an object's tile to the screen and start a camera move: bytes identical, refused (three local output pointers to func_0801C918; with BIOS summaries, the scheduler inside func_08128898) (220 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321 with the match batches then queued for merge (PRs #200 onward). This entry refreshes the earlier `Parked/081227F8/`, whose README was written before the index row and
`func_0801CC18` were fixed; the source is unchanged (same file). `u32 func_081227F8(context, script)` is a script
command handler. It resolves an object from `script[1]` (`func_081255C8`), computes tile-centre coordinates from the
object's data bytes at 0xF6 and 0xF7 (`* 32 + 16`), gets the height from `func_0801CC18`, projects the three coordinates
in place through `func_0801C918(x, y, z, &x, &y, &z)`, subtracts 120 and 100, and dispatches on `script[2]`:

- 1: `context->result = func_0801BB0C(screen_x, screen_y, script[3])`;
- 2: `context->result = func_0801BA20(screen_x, screen_y, script[3])`;
- 0: the same with `g_table_083A8190[script[3] - 1]`;
- 3: `func_08128898(context, screen_x, screen_y, script[3])` and return 0x115.

Other paths return 0x114. The projection call takes the three output pointers in R3 and the two outgoing words:

```
08122846  str  r4, [sp]           @ &y (sp+10)
08122848  str  r5, [sp, #4]       @ &z (sp+12)
0812284A  add  r3, sp, #8         @ &x
0812284C  bl   0x0801C918
```

## The index

`symbols/functions.txt` has `081227F8 081228D4 220 100 return` and `config/functions.json` the same extent with 100 instructions (`thumb-prologue`). The CFG, closed by the kit's own `analyze.refine_function`, has 100 reachable instructions, so the row is right.

## Byte identity

`081227F8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x081227F8, with every callee bound to its ROM address and every data word to the address its symbol names (6 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 220-byte symbol equals the ROM span `[0x081227F8, 0x081228D4)`: SHA-256 `4d446bc6e6dba92f9aa3f69d626fe6918ba4c079fbc0b7e501c77464d64ee2bb` for both. `.text` is exactly 220 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None: every data symbol the source names is already in `config/data_symbols.json` on main.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/081227F8.c`: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `--signed-quotient-profile positive-constant-frame-v1` and `--unsigned-quotient-profile positive-constant-frame-v1` (3) | `buffer callee 0x0801BA20: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`, `--addressed-runtime-profile compiler-signed-runtime-data-v1`, `--addressed-runtime-profile addressed-native-bios-fill-scalar-control-numeric-mmio-code-image-data-v1` and 26 other addressed-runtime selectors (29) | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `--addressed-runtime-profile addressed-native-bios-fill-buffer-v1`, `--addressed-runtime-profile addressed-native-bios-fill-readonly-two-words-v1`, `--addressed-runtime-profile addressed-native-bios-ordinary-v1` and 10 other addressed-runtime selectors (13) | `addressed signed runtimes exclude data and irregular relocations` |
| `bounded-buffer-runtime-summaries-v1`, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1` and 13 other selectors (16) | `buffer callee 0x0801BA20: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1`, `bounded-buffer-bios-fast-fill-source-v1` and `bounded-buffer-bios-mixed-fast-fill-source-v1` (3) | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `named-data-buffer-finite-small-copy-binding-v1` | `one actual canonical small-copy call required` |
| `named-data-buffer-compiler-copy80-binding-v1` | `compiler copy requires exactly one memcpy call and named data only` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x0801BA20: buffer callee 0x08141898: structural inventory is not closed` |
| `named-data-buffer-stack-index-v1` and `named-data-buffer-stack-index-v2` (2) | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `bounded-buffer-bios-sqrt-scratch-v1` | `buffer callee 0x0801BA20: consumer observes BIOS Sqrt scratch before a killing write` |
| `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1` and `bounded-buffer-bios-fill-overwritten-control-stores-v1` (3) | `BIOS fill requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` and `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires an actual direct call in its closed owner` |
| `bounded-buffer-bios-mixed-cpuset-fast-fill-source-v1` | `mixed CpuSet/CpuFastSet fill requires actual calls to both wrappers` |
| `bios-word-switch-local-buffers-v1` | `BIOS buffer requires one exact one-object-word switch without local BL` |

The other 136 selector values are not listed one by one (none matched); by family: scheduler (25), callback and closure (22), private float and double (15), switch-layout (13), owner (12), descriptor and preservation (12), restoring-owner (9), canonical-integer (8), function-address (6), bounded-buffer (6), arithmetic-runtime (5), control-flow (1), -O0 (1), guarded-switch buffer (1).

## Cause

Kit 18dcc516 accepts the two outgoing-word stores (the earlier refusal) and the call to `func_0801C918`. The
two outgoing words still hold `&y` and `&z` at the later calls, so the walk follows them into the callees of the switch
cases, and the first one it cannot inspect is BIOS Sqrt inside `func_0801BA20`: `buffer callee 0x0801BA20: buffer
callee 0x08141898: non-leaf calls and interrupts require linked CFG verification`. `bounded-buffer-bios-sqrt-scratch-v1`
summarises Sqrt and refuses `consumer observes BIOS Sqrt scratch before a killing write` inside `func_0801BA20`; the
stack-index selectors refuse the pointer-bearing outgoing words (`variable stack indices exclude pointer-bearing or
return-carrying local words`).

The #192 comment reports that with its BIOS summaries in the buffer walk this function passes Sqrt, Div and the Div
remainder in `func_0801BA20` and stops at the scheduler inside case 3's callee: `buffer callee 0x08128898: buffer callee
0x08121B8C: buffer callee 0x08005954: buffer callee 0x08142250: ...`.

## History

- The earlier attempt, at an older kit, was refused with `unsupported stack-alias use or
  escape` at the two outgoing-word stores above; kit 18dcc516 accepts them and stops later.
- That attempt also found `func_0801CC18` missing from the index and added its extent `[0x0801CC18, 0x0801CC38)` and the
  data mapping `g_table_083A8190 = 0x083A8190`; both are on main now, and the row of this function, which then ended at
  0x08122804 inside the first call, is now the full `081227F8 081228D4 220 100`.
- A first candidate used a literal table pointer, which folded the table base to 0x083A818F and placed the table case
  before the others. The source names the ROM table and lists the switch cases in their ROM order.

kit issue: shubshub/fftadecomp-kit#192 (comment) (the issue's own 081227F8: past Sqrt, Div and the Div remainder, then the scheduler in 08128898)
