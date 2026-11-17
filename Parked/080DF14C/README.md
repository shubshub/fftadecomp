# 0x080DF14C - effect phase callback with a facing-offset marker: bytes identical, refused (local copies of two ROM tables through func_081443FC, and stack outputs passed to the coordinate wrappers) (462 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080DF14C(void *task, Descriptor080DF14C *descriptor, Payload080DF14C *payload)` is the phase callback of an effect task; its only reference is the function word at `0x080DFA6C`, in the pool of `func_080DFA30`. Phase 0 copies the descriptor's object, palette, priority, target `x`/`y` and delay into the payload and looks up the object's state (`func_080DD4C4`). Phase 0x100 counts the delay down, then reads the state's tile (`func_080DBD78` with three local `s16` outputs), turns it to face the target (`func_0809D6BC`, `func_080DE12C`) and starts a child effect (`func_080DE4B0`). Phase 0x101 copies the two 4-byte `s8` offset tables `data_08149B77` (-6, -10, 0, -4) and `data_08149B7B` (4, 0, 0, 4) to the frame with `func_081443FC`, waits for the child's flag, reads the screen position with `func_080DBDC8` (two local `u16` outputs) and places a marker sprite (`func_080D5CC0(data_084FF654, ...)`) at the position plus the offsets for the current facing; it then starts `data_08395624` with `func_080DFD8C`. Phases 0x102 and 0x103 wait for the marker and the child, restore the facing (`func_080DDDA0`) and finish after ten frames.

```
080DF226  add  r0, sp, #0x18         @ s8 dx[4]
080DF228  mov  r8, r0
080DF22A  ldr  r1, =data_08149B77
080DF22C  movs r2, #4
080DF22E  bl   0x081443FC
080DF232  add  r1, sp, #0x1c         @ s8 dy[4]
080DF234  mov  sb, r1
080DF236  ldr  r1, =data_08149B7B
080DF238  mov  r0, sb
080DF23A  movs r2, #4
080DF23C  bl   0x081443FC
...
080DF248  add  r4, sp, #0x20         @ &sx
080DF24A  mov  r5, sp
080DF24C  adds r5, #0x22             @ &sy
080DF24E  adds r1, r4, #0
080DF250  adds r2, r5, #0
080DF252  bl   0x080DBDC8
```

## The index

The index row `080DF14C 080DF31A 462 231 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (231): the reachable CFG has 206 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080DF14C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080DF14C, with every callee and data symbol bound to its ROM address (17 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 462-byte symbol equals the ROM span `[0x080DF14C, 0x080DF31A)`: SHA-256 `fc68d6423507ac3eb6f9d6e16634cc01d7ee2a6dbef7c21fd47bd2279c06d433` for both. `.text` is 464 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149B77": "0x08149B77"`) for the runs below: `data_08149B77`, `data_08149B7B`, `data_08395624`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080DF14C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 18 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x0809D6BC: signed quotient requires its canonical positive-constant proof` |

The other 192 selector values give 60 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Three kinds of local address reach calls: the two copy destinations (`func_081443FC`, count 4 each, a constant ROM source), the three tile outputs passed to `func_080DBD78` (`0x080DF1C8`), and the two position outputs passed to `func_080DBDC8` (`0x080DF252`). On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. The ROM-table-copy and stack-index-v1 selectors summarise the copies and stop at `func_080DBDC8`, which passes the second output pointer to its own callee as a stack argument. `named-data-buffer-stack-index-v2`, which has kit #183's forwarding rule, gets past it and walks `func_0809D6BC`, because `&tile_z` is still in R4 at that call (`0x080DF1EA`), and stops at that callee's signed division. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the forwarding wrapper `func_080DBDC8` (not re-run here).

## Source notes

- The two tables are named ROM objects at their literals' addresses; the copies are written as the calls the ROM makes, and both are made before the flag test, as the ROM orders them.
- The tables are indexed by the facing byte, `dx[func_080DBC88(state)]` (`0x080DF266`, `0x080DF274`). A stack-index proof would need a premise that the facing is 0 to 3, and none is established: this function's own phase 0x100 passes `func_0809D6BC`'s result, which is -1 for coincident tiles, unchecked to `func_080DE12C` as the new facing (`0x080DF1F8`). The same open question holds the stack-index premise of 0x080FDB98.

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
