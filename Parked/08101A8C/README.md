# 0x08101A8C - effect 0xD3 phase callback with a direction-indexed sprite: bytes identical, refused (local copies of two ROM tables through func_081443FC, indexed by a direction whose bound is not established) (576 bytes)

## Status 2026-11-27: admitted with premise rows, held

At kit main a3aa0e653 this source (237 instructions by match.py's count) is `MATCH - byte identical`
on the default path (`default-stack-index-retry-v1`), with the seven data symbols `data_08149DD8`,
`data_08149DDC`, `data_0839ED34`, `data_0839ED64`, `data_0839ED7C`, `data_0839ED90` and `data_0839ED98` and
these rows in `config/stack_index_premises.json` (with a review paragraph tracing `payload+4` to
`func_080DBCD4`, which is -1 only when the first target stands on the actor's tile):

| site | expression | bound |
|---|---|---|
| `0x08101B8E` | `(u32)u8[(entry_R2 + 4)]@0x08101B88` | 4 |
| `0x08101BCC` | `(u32)u8[(entry_R2 + 4)]@0x08101BC8` | 4 |

It is held because that bound is not established. `func_08099494` scans every unit, the actor included,
filtering on `+0xEA` bit 3 and `+0xE6` == the target's `+0x104`. It is unproved that the actor fails these
filters, or that battle-state `+0xD0` bit 1 is never set for ability 0xD6, when `func_080A433C` replaces the
first target and `func_080A21B4` swaps the two units' tiles (`0x080A4724`..`0x080A47A0`). The dynamic effect
site at `0x080BBCCA` is untraced. If the actor can be chosen, `kinds[255]` and `enables[255]` read past the
stack copies: a latent original bug, which would need the bug-case standard. The rows' review paragraph also leaves one
premise unstated: that the first target record exists. `func_080A8810` returns `ctx+0x20` even when the target
count is 0 (it branches away only for count < index), so a zero-target action would read a cleared record (word 0
is NULL) here. The refusal table below is from 2026-11-17 and is obsolete.

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_08101A8C(void *task, Descriptor08101A8C *descriptor, Payload08101A8C *payload)` is the phase callback of effect 0xD3: its function word is entry 0xD2 of the effect table `data_083947D8` (`0x08394E68`) that 0x080D3508 reads. Phase 0 starts the actor's first animation (`func_080E03F8(actor, data_0839ED34, ...)`); phase 0x100 waits for it and starts the status child `func_08102B48(actor, 2, &payload->status, task)`. Phase 0x101 copies the two 4-byte tables `data_08149DD8` (sprite kinds 1, 0, 0, 1) and `data_08149DDC` (1, 0, 1, 0) to the frame with `func_081443FC`, waits for the status (2 skips to phase 0x103), reads the selected object's position into the payload (`func_080DD748`), stores the direction `func_080DBCD4(position, actor object)` as `payload->index`, and creates two sprites, the first with kind `kinds[index]` and the `func_08011118` argument `enables[index]` (`func_080D5CC0(data_08502560, ...)`, `func_080D5CC0(data_08502ED8, 6, ...)`). Phases 0x102 and 0x103 start the coordinate task `data_0839ED64`, two records and the object's animation `data_0839ED7C`, and wait for them.

```
08101B26  ldr  r1, =data_08149DD8
08101B28  add  r0, sp, #0x10         @ u8 kinds[4]
08101B2A  movs r2, #4
08101B2C  bl   0x081443FC
08101B30  add  r1, sp, #0x14
08101B32  mov  sb, r1                @ u8 enables[4], kept in R9
08101B34  ldr  r1, =data_08149DDC
08101B36  mov  r0, sb
08101B38  movs r2, #4
08101B3A  bl   0x081443FC
...
08101B7E  bl   0x080DBCD4
08101B84  strb r0, [r6, #4]          @ payload->index
08101B86  ldr  r0, =data_08502560
08101B88  ldrb r1, [r6, #4]
08101B8A  add  r1, sp, r1
08101B8C  adds r1, #0x10
08101B8E  ldrb r1, [r1]              @ kinds[payload->index]
```

## The index

The index row `08101A8C 08101CCC 576 288 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (288): the reachable CFG has 237 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`08101A8C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08101A8C, with every callee and data symbol bound to its ROM address (24 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 576-byte symbol equals the ROM span `[0x08101A8C, 0x08101CCC)`: SHA-256 `97e5235dfb8f4a78ddcfc083eeefd5415b2f948e660bd3cd8dec2ee96f912852` for both. `.text` is exactly 576 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149DD8": "0x08149DD8"`) for the runs below: `data_08149DD8`, `data_08149DDC`, `data_0839ED34`, `data_0839ED64`, `data_0839ED7C`, `data_0839ED90`, `data_0839ED98`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08101A8C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 20 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-address materialization` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` | `stack index: the premise rows of 0x08101A8C need a reviewed entry in config/stack_index_premises.json that repeats them exactly (none found); after checking every caller, add:` (followed by the premise entry to add) |

The other 190 selector values give 66 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The only local addresses that reach calls are the two copy destinations (`func_081443FC`, count 4 each, a constant ROM source); the second stays in R9 until `enables[index]` is read. On the default path and under the buffer selectors without a copy summary, the walk stops inside `func_081443FC` at its alignment test. `named-data-buffer-rom-table-copy-v1` summarises the copies and refuses the owner's register-formed table address, `add r1, sp, r1` at `0x08101B8A` (`unsupported stack-address materialization`). **The two stack-index selectors get through the whole function** and stop only at the premise ledger: they ask for a reviewed entry in `config/stack_index_premises.json` that bounds `payload->index` (`u8[(entry_R2 + 4)]`, loaded at `0x08101B88` and `0x08101BC8`) below 4 at the two table reads `0x08101B8E` and `0x08101BCC`. So on today's kit this function needs no new rule, only that premise, and the premise is not established (below). In the prototype measured for the `func_081443FC` issue below, a summary for local buffers takes this function past the helper on the default path, and it then stops at `unsupported stack-address materialization` (not re-run here).

## Source notes

- **No premise can be written yet.** `payload->index` is `(u8)func_080DBCD4(...)`, which returns `func_0809D6BC`'s direction: 0 to 3, or -1 (0xFF) when the two tiles coincide. Bound 4 holds only if `func_08102B48` (mode 2) never selects the actor's own tile, which would need tracing effect 0xD3's spawners (it is started through `func_080D3508`'s table, 48 `bl` sites, with ids from ability data). With a throwaway entry holding exactly those rows, `named-data-buffer-stack-index-v1` gives `verdict MATCH - byte identical` (checked in a scratch copy, entry removed again); that entry is not justified, and this function does not ship on it.
- The rows the stack-index selectors print after `add:` (`-v1`; `-v2` writes each expression with a `(u32)` cast):

  ```
  "0x08101A8C": {
    "review": "<why every execution of each site keeps its index below the bound>",
    "rows": [
      {"site": "0x08101B8E", "expression": "u8[(entry_R2 + 4)]@0x08101B88", "bound": 4},
      {"site": "0x08101BCC", "expression": "u8[(entry_R2 + 4)]@0x08101BC8", "bound": 4}
    ]
  }
  ```
- Both tables are named ROM objects at their literals' addresses (`0x08101B50`, `0x08101B54`), and the copies are written as the calls the ROM makes, before the status test, as the ROM orders them.

kit issue: shubshub/fftadecomp-kit#240
