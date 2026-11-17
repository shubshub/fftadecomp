# 0x080E6B10 - beam effect phase callback: bytes identical, refused (a local copy of a ROM table through func_081443FC, and stack coordinates passed to the coordinate wrappers and the path builder) (580 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E6B10(void *parent, Command080E6B10 *command, Work080E6B10 *work)` is the phase callback of a beam drawn from a source object to a target; its only reference is the function word at `0x080E6F0C`, in the pool of `func_080E6E10`. Phase 0 looks up both objects' states (`func_080DD4C4`). Phase 0x100 reads both positions with `func_080DBDA0`, each into a local `{x, y}` pair and a local depth, and builds the path with `func_080D62CC(&work->beam, &from, &to, -28, -28, 60, work->xs, work->ys, 0, parent)`. Phase 0x101 waits for the timer, creates the beam sprite (`func_080D5DD4(data_084FBA40, 2, ...)`), starts one of two overlays (`data_08949764` or `data_0894A384`, by variant), reads the target's position into three more locals and shakes the screen there (`func_0801BB0C`). Phase 0x102 copies the 3-byte step table `data_08149CA0` (15, 30, 45) to the frame with `func_081443FC`, starts a spark at each step that matches the path position, and advances the path; phase 0x103 waits for the sparks and the overlay.

```
080E6C78  add  r4, sp, #0x24         @ u8 steps[3]
080E6C7A  ldr  r1, =data_08149CA0
080E6C7C  adds r0, r4, #0
080E6C7E  movs r2, #3
080E6C80  bl   0x081443FC
080E6C84  movs r5, #0                @ i
...
080E6C90  adds r0, r4, r5
080E6C92  ldrb r0, [r0]              @ steps[i]
```

## The index

The index row `080E6B10 080E6D54 580 290 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (290): the reachable CFG has 256 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080E6B10.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E6B10, with every callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). The 580-byte symbol equals the ROM span `[0x080E6B10, 0x080E6D54)`: SHA-256 `2402a9d80ddc501c92ba5a9fb38e003868b4b7a2122db55b734997f029e2c374` for both. `.text` is exactly 580 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149CA0": "0x08149CA0"`) for the runs below: `data_08149CA0`, `data_084FBA40`, `data_08949764`, `data_0894A384`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E6B10.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 23 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x080D62CC: stack aliases cannot be stored or spilled` |

The other 187 selector values give 64 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Local addresses reach calls in three phases: the six coordinate outputs of the three `func_080DBDA0` calls, `&from` and `&to` passed to `func_080D62CC` (`0x080E6BB2`), and the copy destination `steps` (`func_081443FC`, count 3, a constant ROM source), whose address stays in R4 across the spark calls of the loop. On the default path the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` summarises the copy and refuses the loop's register index `steps[i]`; `named-data-buffer-stack-index-v1` stops at `func_080DBDA0`, which passes the second and third output pointers to its own callee `func_0801C918` as stack arguments; `-v2`, which has kit #183's forwarding rule, gets past it and stops inside `func_080D62CC`, the path builder that receives `&from` and `&to`. In the prototype measured for the kit issue below, a `func_081443FC` summary for local buffers takes this function past the helper, and it then stops at the owner's register index into the copied table (not re-run here).

## Source notes

- `data_08149CA0` is a named ROM object at its literal's address (`0x080E6D04`), and the copy is written as the call the ROM makes. The loop bound is the constant 2 (`i <= 2`), so the index stays inside the copy.
- `func_080D62CC` is declared here with `s32` offset arguments, and the matched `src/080D62CC.c` declares them `u16`. The ROM passes -28 sign-extended (`movs r3, #0x1c; rsbs r3, r3, #0` at `0x080E6B94`), which a `u16` parameter does not produce: with the matched prototype the function is 584 bytes (16 halfwords differ). The prototypes need reconciling at integration (the callee's `u16` is the one the callers contradict; whether that file compiles the same with a signed type was not tested).
- 0x080FEBDC is the same beam with a different sprite and table (`data_08149DCC`).

kit issue: (to be filed - match.py: a local buffer passed to the pinned copy helper func_081443FC is refused in every buffer walk outside the ROM-table-copy selectors)
