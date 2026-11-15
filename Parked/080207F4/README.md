# 080207F4: byte-identical; a void root returns with an expired frame address in R1

Target: `[0x080207F4, 0x08020A68)`, 628 bytes. `void f(MapWindow *window)`. It clips a window (`x`, `y`, two dimensions) against the position from `func_0801E700` and the sizes from `func_0801E674` and `func_0801E680`, all taken in units of 8, and copies it from the buffer `func_0801AD1C(layer)` returns, 64 entries to a row, to the address `func_0801E6B4(layer)` returns, 32 entries to a row. Each row is one DMA0 transfer (`0x040000B0`) with a poll for completion. When the width is 64, the part of the window at column 32 and beyond is a second copy, written `0x400` entries further on.

The ROM has one direct call of this function, at `0x08020D3A` in `08020BA0`, and no aligned word holding `0x080207F4` or `0x080207F5`.

## Byte identity

`080207F4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 628 bytes, and every byte outside a relocation field equals the ROM;
- the five `R_ARM_THM_CALL` relocations and the one `R_ARM_ABS32` (`data_040000B0`), read back from the ROM bytes, give the address in each symbol's name.

`match.py` does not reach its own byte comparison (below). `plausible.py --strict` exits 0; the DMA registers are accessed through a `volatile` pointer with a `plausible:` justification.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root. No new data symbol is needed: `data_040000B0` is in `config/data_symbols.json` on main.

```sh
cp Parked/080207F4/080207F4.c src/080207F4.c
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x080207F4
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x080207F4
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-v1`, `named-data-buffer-dead-argument-aliases-v1`, `named-data-buffer-known-query-callee-v1`, `bounded-buffer-root-return-scratch-v1` | `local stack pointer escapes through a return register` |
| `bounded-buffer-discarded-return-scratch-v1` | `buffer callee 0x0801AD1C: consumer observes discarded return scratch before a killing write` |

## Cause

The function keeps two flag bytes, `u8 pending[2]`, at `sp + 0x10`, and tests them through a register:

```
08020984  mov  r1, sb           @ sb = sp + 0x10
0802098A  beq  0x080209E6       @ pending[0] == 0: skip the first copy
080209EC  beq  0x08020A52       @ pending[1] == 0: skip the second copy, to the epilogue
```

Each copy overwrites R1. On the path that skips both, R1 still holds `sp + 0x10`, which is entry SP - 52, at the only return, `pop {r0}; bx r0` at `0x08020A5E`. R0 holds the return address there, so R1 is the only result register with an expired frame address, and the function returns nothing. The kit's own alias state at `0x08020A60` is R1 and R2 at entry SP - 52 on the default path, and R1 alone under `bounded-buffer-root-return-scratch-v1`, which projects R2 and R3 only.

In the source every arm that sets the flags sets at least one of them, so the path that skips both copies is not taken. The alias rule does not follow the values of the two bytes.

The return is not the only obstacle. In a scratch copy of the kit that also projects R1 there (a probe, not a proposed rule), the walk stops next at `inconsistent possible pointer offsets at control-flow join`, at `0x08020974`: R3 holds `sp + 0x10` on the arm through `0x08020960` and `sp` on another. R3 is written before it is read on every path from there, but the two calls in between are not looked through.

## Source notes

- The row addresses are assigned to the locals `source` and `destination` before each `copy_rows` call. With the two expressions written as the call arguments the function is 632 bytes.
- `end_x` is declared before `map_width`. Declared after it, 4 bytes differ.
- The row copy is a `static inline` helper, `copy_rows(source, destination, u16 width, u16 rows)`, expanded twice. With `u8 rows` the function is 628 bytes of which 99 differ. With the helper's loop written out in both places (same `source` and `destination` locals, a `u16 row` counter), the function is 644 bytes with `u16` locals for the width and the row count, 632 bytes with `u8` locals, and 628 bytes of which 171 differ with the `copy[]` fields read directly in the loop. No out-of-line copy of the helper has been shown, so it remains an open doubt about the source, separate from the verifier refusal.
- Each row reads the DMA control word back once before polling it (`(void)dma->control`), as the matched `src/08147A44.c` does. Without that read the function is 624 bytes.

kit issue: (to be filed)
