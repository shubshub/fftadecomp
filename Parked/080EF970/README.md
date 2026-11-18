# 080EF970 effect callback

The C reproduces all 318 bytes in the original function, including its literal pool. The body has 138 reachable instructions and 13 direct calls. It stays Parked because two ordinary initialization paths leave its first child handle null and the subsequent scheduler update dereferences that handle.

## Original registration and phase zero

The registrar at `080EFAB0` loads the callback word `080EF971` from `080EFC70`, supplies a 40-byte payload and calls `08005B6C` at `080EFC5C`. The scheduler allocates 68 bytes, clears them, supplies the payload at task +24, and invokes the callback with phase zero. The source uses the scheduler's three-pointer callback signature and the shared `effect_task.h` declaration for `080DCFE4`.

| Object +12 bit 7 | Object +20 bit 0 | Mode | 20-byte record | Duration | Populated handle offsets in payload |
| --- | --- | --- | --- | --- | --- |
| Clear | Unused | 2 | `08399B04` | 236 | +32 |
| Set | Set | 0 | `08399B04` | 236 | +28, +32 |
| Set | Clear | 1 | `08399B18` | 180 | +24, +32, +36 |

The ROM halfwords at `08149D0C` are copied to the four bytes at entry SP −32 through −29. The branch at `080EFA24` tests the same mode just copied to R3 and replaces 2 with zero. The halfword index is therefore 0 or 1. Mode 1 passes separate output halfwords at entry SP −28 and −26 to `080DBDC8`. That wrapper forwards the second pointer on its own stack to `0801C984`. The two coordinates are immediately read back and passed by value. The three persistent output pointers instead occupy payload bytes [12,24). The timing records at `08399ABC` have stride 24 and count 3. The sequence at `08399B34` has one eight-byte event. Both function indexes carry the 138-instruction count, and the data index names all four literals.

## Normal scheduler update

A CPU replay executed the original registration suffix, scheduler zero and copy routines, all child constructors and their phase-zero callbacks, and the manager update at `08005A24`. It supplied distinct writable heap blocks at the allocator boundary, a valid parent and entity, and a mapped camera. Phase zero wrote 224 to the payload. The scheduler set the task's own phase to 256 at `08005A10` and subsequently delivered that phase through `08005A70`.

In mode 1, entity coordinates (−11, −4, 9) and camera halfwords (5, 6, 7, 8) produced (−12, −1). The first phase-256 poll returned the live child. In modes 0 and 2 the handle at payload +24 was still zero. The first poll at `080EFA7A` called `080D6134`, which called `08005BB0` unconditionally. Its `ldrh r0, [r0, #0x14]` at `08005BB4` attempted a two-byte read at physical `00000014`. This occurred with the scheduler's actual initialization and ordinary nonnull input objects. The subsequent polls of +28 and +32 guard null; +36 is never polled here. If all three polled handles return zero, the descriptor advances to phase 2.

The replay stopped at the unmapped BIOS address. The actual GBA BIOS protection/open-bus read value and its dependence on hardware state remain unresolved. Granting an always-readable task object at this site would exclude two observed modes. The private-frame and table bounds can be proved independently of that read. No canonical match report accompanies this source.

## Earlier attempt

The following notes record the November 17 source, maps and verifier behavior.

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `s32 func_080EF970(void *context, Event080EF970 *event, State080EF970 *state)` is an effect phase callback; its only reference is the function word at `0x080EFC70`, in the pool of 0x080EFAB0. Phase 0 copies the two-halfword table `data_08149D0C` (236, 180) to the frame with `func_081443FC`, looks up the object's entity, and picks a mode: 2 by default, 0 or 1 from `func_080DD580` and `func_080DD670`. In mode 1 it reads the entity's screen position with `func_080DBDC8` into two local `s16` words and starts the coordinate task `func_080D6098(x, y, 0, 1, 3, state->result, data_08399ABC, context)` and the record `data_08399B34`. It then starts the animation `func_080DCFE4(object, &data_08399B04[index], 12, values[index], 4, context, 216)`, where `index` is the mode with 2 mapped to 0, and in mode 0 also `func_080DF8E8`. Phase 0x100 waits for the three children.

```
080EF99A  ldr  r1, =data_08149D0C
080EF99C  add  r0, sp, #0x10         @ u16 values[2]
080EF99E  movs r2, #4
080EF9A0  bl   0x081443FC
...
080EF9DC  add  r4, sp, #0x14         @ &x
080EF9DE  mov  r5, sp
080EF9E0  adds r5, #0x16             @ &y
080EF9E2  adds r1, r4, #0
080EF9E4  adds r2, r5, #0
080EF9E6  bl   0x080DBDC8
...
080EFA20  adds r3, r7, #0            @ index = mode
080EFA22  cmp  r7, #2
080EFA24  bne  0x080EFA28
080EFA26  movs r3, #0
...
080EFA34  lsls r2, r3, #1
080EFA36  add  r2, sp, r2
080EFA38  adds r2, #0x10
080EFA3A  ldrh r3, [r2]              @ values[index]
```

### The index

The index row `080EF970 080EFAAE 318 159 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (159): the reachable CFG has 138 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

### Byte identity

`080EF970.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080EF970, with every callee and data symbol bound to its ROM address (13 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 318-byte symbol equals the ROM span `[0x080EF970, 0x080EFAAE)`: SHA-256 `1a73dc8e275d02a7f13a0dcea8e9b09169dac4efbb3734d7653fae62397464e6` for both. `.text` is 320 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

### Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D0C": "0x08149D0C"`) for the runs below: `data_08149D0C`, `data_08399ABC`, `data_08399B04`, `data_08399B34`.

### Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080EF970.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 27 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `stack index: index range reads uninitialised local bytes in [-32, -26); index has no defined source (no premise can be stated)` |

The other 183 selector values give 58 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `addressed signed runtimes exclude data and irregular relocations` (13).

### Cause

Two local addresses reach calls: the copy destination `values` (`func_081443FC`, count 4, a constant ROM source) and the position outputs passed to `func_080DBDC8` (`0x080EF9E6`). On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. The ROM-table-copy and stack-index-v1 selectors summarise the copy and stop at `func_080DBDC8`, which passes the second output pointer to its own callee as a stack argument. `named-data-buffer-stack-index-v2`, which has kit #183's forwarding rule, gets past the wrapper and refuses the index: its range for `values[index]` includes 2, which reads two bytes past the copy, although the CFG maps mode 2 to index 0 before the load (`0x080EFA20`-`0x080EFA26`), so the index is 0 or 1. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the forwarding wrapper `func_080DBDC8` (not re-run here).

### Source notes

- `data_08149D0C` is a named ROM object at its literal's address (`0x080EFA68`), and the copy is written as the call the ROM makes, at the top of phase 0 as the ROM orders it.
- `state->entity = func_080DD4C4(state->object);` appears twice because the ROM calls it twice (`0x080EF9A8`, `0x080EF9B0`), storing the result both times.
- `index` is a separate variable (`adds r3, r7, #0` at `0x080EFA20`); the mode stays in R7 for the later `mode == 0` test.

kit issue: shubshub/fftadecomp-kit#240
