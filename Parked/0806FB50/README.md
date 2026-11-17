# 0x0806FB50 - item ability panel draw: bytes identical, refused (CpuSet fills from stack zeros and a local list from a jump-table callee) (708 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `func_0806FB50(panel, item)` draws the abilities an item
grants into a tile panel. It clears 0x1A halfwords of the panel with CpuSet from a stack zero (`func_0814186C` at
0x0806FB7E), draws the frame with `func_0802AB64`, and gets up to three granted abilities from `func_080C8D14(item,
&granted)` into a local (0x0806FBB6; none for items of kind 0x1B). For each it draws two rows and, for the matching
entry of the item's table in `g_table_08520080`, the ability's cost (`func_080CD480(func_080C8570(...), ability)`,
capped at 999) with `func_0802ACA0` and `func_08029730`. The last ability's type selects one of four labels, and when
fewer than three abilities were drawn the rest of the panel is cleared with a second CpuSet from a stack zero
(0x0806FDFA). Callers: the matched `src/0806F7B8.c` and `src/0806F8DC.c`.

The index row `0806FB50 0806FE14 708 319 return` is right (319 reachable instructions).

## Byte identity

`0806FB50.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0806FB50, with every callee and data symbol bound to its
ROM address (17 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 708-byte symbol equals the ROM span `[0x0806FB50,
0x0806FE14)`: SHA-256 `125d57fd907a3ee9b837fdc2f9426a5d673d4226555c5515130e93bbb4d1f011` for both. `.text` is exactly
708 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0806FB50.c` (no data symbol to add): the
default run and the selectors the kit issue and the earlier notes discuss.

| Selector | Result |
|---|---|
| default, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1` | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-fill-source-v1` | `buffer callee 0x080C8D14: unresolved program-counter write` |

## Cause

The default walk enters the CpuSet wrapper `func_0814186C` and refuses its `svc`. Under
`bounded-buffer-bios-fill-source-v1`, which summarises the fills, the walk gets past them and stops at the local
`granted` list passed to `func_080C8D14` (matched): that callee dispatches through a jump table loaded before its
guard and refuses at its `mov pc` (`unresolved program-counter write`).

## Source notes

Open questions from the attempt, for a reviewer: the spelling `(g_table_0851D180 + item)->abilities` beside
`g_table_0851D180[item].kind`; one `p` pointer shared by the cost and label draws; `info = 0` before the loop (read by
the label switch when no entry matched); the grouping `i * 4 * width`; and the tile array at +0x8C of the panel.

kit issue: shubshub/fftadecomp-kit#192 (comment to be posted); (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
