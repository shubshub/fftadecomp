# 0x080FDB98 - flash effect phase callback (facing offset table): bytes identical, refused (local outputs through the forwarder 0x080DBDC8 and a facing-indexed stack table whose premise is contradicted) (702 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `s32 func_080FDB98(void *task, Descriptor080FDB98 *descriptor, Payload080FDB98 *payload)` is the task callback that `func_080FDE58` starts (function word `0x080FDB99` at `0x080FDE8C`); no `bl` reaches it. Phase 0 saves 0x10 palette halfwords of `data_03003920` into the payload with CpuSet (`func_0814186C`) and starts a first child with `func_080E03F8(actor, data_0839D7E4, 2, 7, 0, task)`; 0x100 waits for it and starts a motion script (`func_080DDF68(..., data_0839D7FC, ...)`). 0x101, once the script is ready, copies the 16-byte table `data_08149D94` (four `{s16 x, s16 y}` offsets: (4, -4), (4, -4), (-4, -4), (-4, -4)) to the stack as a structure assignment, reads the object's position into two local `s16` outputs with `func_080DBDC8(object, &x, &y)`, adds the offset selected by the object's facing byte (`func_080DBC88`) and passes the result to `func_080D7220(data_088F58E0, 1, 3, ...)`, then starts a flash (`func_080D3E9C(data_0894D69C, task)`) and two effects (`data_0894A028`/`data_0894A050`, or `data_0894BE84`/`data_0894BEAC` for variant 6). 0x102 waits, clears BG3 in `g_control_flags_03000940`, restores the palette and starts a second motion (`data_0839D800`); 0x103 and 0x104 start a sound, wait for `func_080D8B4C` and write the result; 0x105 waits for the object.

```
080FDC84  ldm  r0!, {r2, r3, r4}      @ table = data_08149D94 (to sp + 0x14)
080FDC86  stm  r1!, {r2, r3, r4}
...
080FDC96  add  r4, sp, #0x24          @ &x
080FDC98  mov  r5, sp
080FDC9A  adds r5, #0x26              @ &y
080FDCA0  bl   0x080DBDC8
080FDCA6  bl   0x080DBC88             @ facing byte
080FDCAC  lsls r0, r0, #0x18
080FDCAE  asrs r0, r0, #0x16          @ (s8)index * 4
080FDCB0  add  r0, sp, r0
080FDCB2  adds r0, #0x14
080FDCB4  ldrh r3, [r0]               @ table.offsets[index].x
080FDCBE  ldrh r0, [r0, #2]           @ table.offsets[index].y
```

`func_080DBDC8` (36 bytes) is a forwarder: it passes `&x` on in R3 and stores `&y` into its own outgoing word (`str r2, [sp]`) for `func_0801C984`. The literal at `0x080FDD00` is the only aligned ROM word with the table's address.

## The index

The index row `080FDB98 080FDE56 702 351 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (351): the reachable CFG has 285 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080FDB98.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FDB98, with every callee and data symbol bound to its ROM address (27 `R_ARM_THM_CALL`, 15 `R_ARM_ABS32`). The 702-byte symbol equals the ROM span `[0x080FDB98, 0x080FDE56)`: SHA-256 `8527501ea17bd5cf5f925548ec0f3c27aa82594b623e87da2fa4b20bb63e0784` for both. `.text` is 704 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D94": "0x08149D94"`) for the runs below: `data_08149D94`, `data_0839D7E4`, `data_0839D7FC`, `data_0839D800`, `data_0839D804`, `data_0839D80C`, `data_088F58E0`, `data_0894A028`, `data_0894A050`, `data_0894BE84`, `data_0894BEAC`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080FDB98.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-stack-index-v1`, and 27 other selector values | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `stack index: the premise rows of 0x080FDB98 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found); after checking every caller, add:` (followed by the premise entry to add) |

The other 184 selector values give 64 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (13), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The default run and the plain buffer selectors stop at the forwarder (`buffer callee 0x080DBDC8: unsupported buffer pointer use or escape`), the case #183 admitted only under `named-data-buffer-stack-index-v2`. That selector gets past it and then needs a premise for the two table reads, which it prints as a `PremiseRefusal`: `stack index: the premise rows of 0x080FDB98 need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found)`, with the rows `0x080FDCB4`, `(u32)((ret(0x080FDCA6) << 24) >>s 22)`, bound 15, and `0x080FDCBE`, the same expression, bound 13. In the prototype measured for the forwarding issue below (not re-run here), the forwarding rule in the plain proof clears the wrapper and the function then stops at `unsupported stack-address materialization`.

The premise is that the facing byte `func_080DBC88` returns is in 0..3. It is not proven, and the evidence contradicts it: `func_0809D6BC` returns -1 for coincident positions, and four writers store that value unchecked (`func_08109990` at `0x08109A56`, `func_080DF14C` at `0x080DF1F8`, `func_080F9B14` at `0x080F9F0E`, which indexes a 4-byte stack table with it, and `func_080B55CC` at `0x080B56DA`); the earlier search also left unbounded writers (a script command, task payload bytes and raw parameters reaching `func_080975DC`/`func_0809A27C`). On 2026-11-14 this source gave `MATCH - byte identical` under `named-data-buffer-stack-index-v2` with a throwaway premise entry for those two rows. That match does not ship: no premise entry can honestly be written, so the function stays parked unless the kit gains a route that does not need the 0..3 bound.

## Source notes

- `Offsets080FDB98 table = data_08149D94;` is a structure assignment, which agbcc copies inline with `ldm`/`stm` as the ROM does.
- The offset is added as `x + table.offsets[index].x` (`ldrh r3, [r0]; ldrh r4, [r4]; adds r3, r3, r4`); with the operands swapped (`table.offsets[index].x + x`), 12 halfwords differ, so the order is the ROM's.
- The source includes `control_flags.h`; the BG3 clear in phase 0x102 is a member store.

kit issue: (to be filed - match.py: forwarded callee stack arguments are admitted only under named-data-buffer-stack-index-v2; the generic buffer proofs refuse the 080DBDxx coordinate wrappers)
