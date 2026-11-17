# 0x080E2398 - effect setup switch: bytes identical, refused (a stack descriptor passed to func_08005B6C, and a jump table with an interposed data word) (952 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E2398(void *task, Descriptor080E2398 *descriptor, Work080E2398 *work)` is a phase callback. Its function word is in the pools of `0x080D3508` (`0x080D35CC`, the callback for effect id 0x159), `0x0810CCF8`, `0x0811CEC0`, `0x0811E9AC` and `0x0811EAD4`, and in the table at `0x08395298`. Phase 0 decodes the descriptor's code into a kind, a row and a slot, switches on the kind (23 cases) to load the graphics rows for it with `func_080D45D0`, starts a loader with `func_080E03F8` from one of four record arrays (`data_08395720`, `data_08395738`, `data_08395750`, `data_0839575C`), and for most kinds loads one more row set. Phase 0x100 waits for the loader and starts the kind's start-up task from `data_08395840`/`data_0839589C` with `func_080D7A70`. Phase 0x101 waits for it, fills a 28-byte request at `sp + 8` and starts the slot's child task, whose callback and payload size come from the tables `data_08395C1C` and `data_08395C3C`:

```
080E26EE  add  r1, sp, #8              @ request
...
080E2704  ldr  r2, =data_08395C1C
080E2706  ldrb r1, [r5, #1]            @ work->slot
...
080E270C  ldr  r0, [r0]                @ callback from the table
080E270E  ldr  r2, =data_08395C3C
...
080E2714  ldrh r1, [r1]                @ payload size from the table
080E2716  add  r2, sp, #8
080E2718  mov  r3, r8                  @ task
080E271A  bl   0x08005B6C
```

The kind switch dispatches at `0x080E2470`; after the dispatch come a pad halfword, the data word `data_08395720` (`0x080E2474`, loaded at `0x080E245A`) and only then the table pointer (`0x080E2478`, table at `0x080E247C`).

## The index

The index row `080E2398 080E2750 952 476 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (476): the kit's `analyze.refine_function` at 18dcc516 does not close the CFG without options; with `one_object_word_switch=True` it closes at 344 reachable instructions (the earlier entry called the row correct). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`numeric-data-switch-source-v1`, `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1` and 3 more: `complete-owner text reachable instruction count differs`, `numeric-data switch requires exact dual-index instruction counts`).

## Byte identity

`080E2398.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E2398, with every callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 48 `R_ARM_ABS32`). The 952-byte symbol equals the ROM span `[0x080E2398, 0x080E2750)`: SHA-256 `25f2c556733ca16e344620bd57413427571d75874b7534baa8df31bc0c09df8e` for both. `.text` is exactly 952 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This entry refreshes the README of `Parked/080E2398/` (2026-11-16, kit fcdf2d45); the source is unchanged. Every refusal that README quoted reproduces at 18dcc516. In a modified copy of the kit at fcdf2d45 that forced the one-object-word switch option on in owner admission, the owner selectors' next refusal was `named-data buffer caller excludes local BL and word switches` (not re-run).

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08395720": "0x08395720"`) for the runs below: `data_08395720`, `data_08395738`, `data_08395750`, `data_0839575C`, `data_08395840`, `data_0839589C`, `data_08395C1C`, `data_08395C3C`, `data_088E9C60`, `data_088EA66C`, `data_088EA6D0`, `data_088EA6D8`, `data_088EAFB0`, `data_088EB260`. `data_08395C1C` is the table of eight child callbacks (`func_080E0E98` to `func_080E21BC`) and `data_08395C3C` their `u16` payload sizes; the six `data_088E...` words are the row sets passed to `func_080D45D0`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E2398.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `--switch-data-profile u16-scalars-v1`, `--switch-data-profile u16-scalars-v2`, `--switch-data-profile u16-scalars-frame-v1` (4), and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `watched-switch-preservation-v1`, `named-data-buffer-v1`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-root-guarded-switch-v1`, all 25 `conditional-scheduler-*` selectors (29), and 60 other selector values | `structural inventory is not closed` |

The other 119 selector values give 28 other refusals, none of them a match; the most frequent are `addressed ABS32 requires an aligned unique undefined global with its exact type` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

Two things are refused. The request address in R2 at the `func_08005B6C` call is a stack alias crossing a call, which the default path and the switch-data selectors refuse (`stack aliases cannot cross calls in caller-clobbered registers`). The owner selectors that could carry the descriptor (scheduler, named-data buffer, guarded-switch buffer, watched switch) first rebuild the function's structure and cannot close it: the kit's `analyze.refine_function` stops at the dispatch unless its one-object-word switch option is set, and owner admission never sets it (`structural inventory is not closed`). The object-word switch layout with named data is the case kit #74 asks for (see its comment for `0x0806025C`). In the prototype measured for the scheduler issue below, the per-site descriptor rule takes this function past the scheduler call, and it then stops at that switch (not re-run here).

## Source notes

- `count = 2;` is restated in cases 16 and 19 (`movs` at `0x080E258A` and `0x080E25CE`); without it the function is 944 bytes. Each case sets its record array and its count together.
- `u8 first = 0;` is case 0x16's value (`movs r3, #0` at `0x080E2662`).
- `func_080DD47C(work->object)` reuses R0 after the store; the two `func_080E03F8` calls are written as in the sibling `0x080E41E4`; the descriptor and request types follow `0x0811896C`; the locals are declared `request`, `reload`, `entries`, `count`, `code`, the order the frame needs.

kit issue: (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules); the switch part is shubshub/fftadecomp-kit#74
