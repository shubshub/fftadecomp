# 0x08003A98 - serial interrupt enable and link state reset: bytes identical, admitted by one selector, held by source policy (a spare pointer temporary) (132 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_08003A98()` sets bit 7 (serial) of the interrupt mask
with IME held off: it saves REG_IME, writes 0 to it, ORs 0x80 into the mask at `data_03000EA0 + 6`, copies the mask to
`data_03000E50` and to REG_IE, and restores REG_IME. It then clears one word at `data_03000870` and one at
`data_03002780` with CpuSet from stack zeros (`func_0814186C(&zero, dst, 0x05000001)` at 0x08003ACE and 0x08003ADC,
sources sp and sp+4) and sets the bytes at `data_030028A0 + 9` and `+ 0x124` to 1. Its caller is 0x080C5908.

The index row `08003A98 08003B1C 132 47 return` is right (47 reachable instructions). All five data symbols are
already in `config/data_symbols.json`.

## Byte identity

`08003A98.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08003A98, with every callee and data symbol bound to its
ROM address (2 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 132-byte symbol equals the ROM span `[0x08003A98, 0x08003B1C)`:
SHA-256 `98f77b6266154a18c08d0f0219f7451a2adf5b4a2f09ccc7dbb45cb7d22735dd` for both. `.text` is exactly 132 bytes.
`match.py` refuses on the default path but gives `verdict MATCH - byte identical` under one selector (below).
`plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08003A98.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `named-data-buffer-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `--addressed-signed-runtime-profile addressed-native-bios-fill-saved-scalar-control-numeric-mmio-data-v1` | `verdict MATCH - byte identical` |
| `bounded-buffer-bios-fill-source-v1` | `owner address literals require exact typed object/function coverage` |

The admitting selector is one of the addressed BIOS-fill selectors (numeric MMIO words, named data). So the verifier
is not what holds this function.

## Why it does not ship

`u16 *shadow = &data_03000E50;` is a spare temporary. It is assigned before the mask update and used once (`*shadow =
data_03000EA0.interrupt_mask;`). The address load is in the ROM with or without it; the local only moves it ahead of
the update (`ldr r6, =0x03000E50` at 0x08003AA8, before `ldr r4, =0x03000EA0`), so the fill zero goes to R8, which
costs the `mov r6, r8; push {r6}` save and three moves through R8. Every instruction that differs without it is a
register-allocation consequence. From the review of this source (not re-run here):

- the plain form (`data_03000E50 = data_03000EA0.interrupt_mask;`) emits 40 instructions against 47;
- the closest natural spelling, `data_03000E50 = data_03000EA0.interrupt_mask |= 0x80; REG_IE = ...;`, emits 48, with
  the early address load and the R6/R8 allocation but the stored value in R1 and one extra move;
- no merged sibling needs such a local: `src/0800337C.c` writes `shadow = &g_control_flags_03000940;` and compiles to
  the same code without it. The merged siblings `src/080316D0.c`, `src/08089C4C.c`, `src/08004C40.c` and
  `src/08004CD4.c` use a value local, which gives 21 of 47 instructions in order here.

It stays parked until a natural spelling gives the R6/R8 allocation.

## Source notes

- The REG_IME accesses (0x04000208) are volatile and needed: without `volatile` agbcc deletes the zero store at
  0x08003AA6, which the ROM keeps before the restore.
- The two fills are `func_0814186C(&zero, dst, 0x05000001)`, as in the matched `src/08004C40.c`.

kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data)) (cited there as matchable today, which holds for the verifier only); shubshub/fftadecomp-kit#192 (comment to be posted) (the same caveat)
