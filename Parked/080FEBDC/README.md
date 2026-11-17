# 0x080FEBDC - beam effect phase callback: bytes identical, refused (a local copy of a ROM table through func_081443FC, and stack coordinates passed to the coordinate wrappers and the path builder) (644 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080FEBDC(void *task, Descriptor080FEBDC *descriptor, Payload080FEBDC *payload)` is the phase callback of a beam drawn between two objects; its only reference is the function word at `0x080FF0B0`, in the pool of `func_080FEE60`. Phase 0 stores the three objects and the flag and sets a 62-frame counter. Phase 0x100 reads both endpoints with `func_080DBDA0`, each into a local `{x, y}` pair and a local depth, and builds the path with `func_080D62CC(&payload->marker, &from, &to, -28, -28, 60, payload->x, payload->y, 0, task)`. Phase 0x101 waits for the counter, creates the beam sprite (`func_080D5DD4(data_084FBA40, 2, ...)`) and an overlay (`data_08949ADC`) and starts the path. Phase 0x102 copies the 3-byte step table `data_08149DCC` (15, 30, 45) to the frame with `func_081443FC`, starts a spark at each step that matches the path position, and advances the path; at its end it reads the second object's screen position into two locals (`func_080DBDC8`), starts the coordinate task with `data_0839E0FC` and, for flag 1, the third object's animation `data_0839E194`. Phase 0x103 waits for the overlay, the sparks, the coordinate task and the animation.

```
080FECFC  add  r4, sp, #0x1c         @ u8 steps[3]
080FECFE  ldr  r1, =data_08149DCC
080FED00  adds r0, r4, #0
080FED02  movs r2, #3
080FED04  bl   0x081443FC
080FED08  movs r5, #0                @ i
...
080FED14  adds r0, r4, r5
080FED16  ldrb r0, [r0]              @ steps[i]
```

## The index

The index row `080FEBDC 080FEE60 644 322 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (322): the reachable CFG has 288 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080FEBDC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FEBDC, with every callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 644-byte symbol equals the ROM span `[0x080FEBDC, 0x080FEE60)`: SHA-256 `5c8df8fb20c27cd422a10fbade5616b4d274acb382d44f17929f1d4511d7a664` for both. `.text` is exactly 644 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149DCC": "0x08149DCC"`) for the runs below: `data_08149DCC`, `data_0839E0FC`, `data_0839E194`, `data_084FBA40`, `data_08949ADC`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080FEBDC.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 19 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x080D62CC: stack aliases cannot be stored or spilled` |

The other 191 selector values give 66 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Local addresses reach calls in two phases: the four coordinate outputs of the two `func_080DBDA0` calls and `&from`/`&to` passed to `func_080D62CC` (`0x080FEC82`), then the copy destination `steps` (`func_081443FC`, count 3, a constant ROM source), kept in R4 across the spark calls of the loop, and the two position outputs of `func_080DBDC8` (`0x080FED90`). On the default path the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` summarises the copy and refuses the loop's register index `steps[i]`; `named-data-buffer-stack-index-v1` stops at `func_080DBDC8`, which passes the second output pointer to its own callee as a stack argument; `-v2`, which has kit #183's forwarding rule, gets past the wrappers and stops inside `func_080D62CC`, the path builder that receives `&from` and `&to`. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the owner's register index into the copied table (not re-run here).

## Source notes

- `data_08149DCC` is a named ROM object at its literal's address (`0x080FEDF0`), and the copy is written as the call the ROM makes. The loop bound is the constant 3, so the index stays inside the copy.
- `func_080D62CC` is declared here with `s16` offset arguments, and the matched `src/080D62CC.c` declares them `u16`. The ROM passes -28 sign-extended, which a `u16` parameter does not produce: with the matched prototype the function is 648 bytes (14 halfwords differ). The prototypes need reconciling at integration (whether the callee compiles the same with a signed type was not tested).
- The empty `case 1: break;` has no compare of its own in the ROM (phases below 0x100 other than 0 go straight to the exit at `0x080FEBFE`), but it shapes agbcc's compare tree: without it the function is 652 bytes (17 halfwords differ). The matched phase callbacks of this family write the same empty case.
- 0x080E6B10 is the same beam with a different sprite and table (`data_08149CA0`).

kit issue: shubshub/fftadecomp-kit#240
