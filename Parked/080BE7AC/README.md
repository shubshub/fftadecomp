# 0x080BE7AC - scored position list: bytes identical, refused (a local swap record passed to the copy callback through _call_via_r3, with named data) (308 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `s32 func_080BE7AC(Actor080BE7AC *actor, u8 x, u8 y, Tile080BE7AC *tiles, Result080BE7AC *results)` is called once, from `0x080BEF28`. It asks `func_0812F0D8` for the actor's entries (a local `u16 entries[2]` at `sp + 8`), fills a range request at `sp + 0xC` and has `func_080B4A1C(&request, 0, 1, tiles)` list the positions reachable from (x, y). It returns -1 when there are none, scores each with `func_080BE5F4`, keeps those with a positive score in `results[]`, and sorts the 8-byte results by score, highest first. Each swap goes through the copy callback `data_0836D4BC[0]` (`_call_via_r3`) and a local 8-byte temporary at `sp + 0x18`, which is the destination of the first copy and the source of the third:

```
080BE890  mov  r1, sb                 @ sb = &data_0836D4BC
080BE892  ldr  r3, [r1]
080BE894  adds r0, r7, #0             @ r7 = sp + 0x18 (swap)
080BE896  adds r1, r6, #0             @ &results[i]
080BE898  movs r2, #8
080BE89A  bl   0x08142250             @ _call_via_r3
...
080BE8B0  adds r0, r4, #0             @ &results[j]
080BE8B2  adds r1, r7, #0             @ swap
080BE8B4  movs r2, #8
080BE8B6  bl   0x08142250
```

It returns the number of results.

## The index

The index row `080BE7AC 080BE8E0 308 154 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (154): the reachable CFG has 146 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent; the earlier entry called the row correct). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-r3-thunk-switch-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080BE7AC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080BE7AC, with every callee and data symbol bound to its ROM address (6 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 308-byte symbol equals the ROM span `[0x080BE7AC, 0x080BE8E0)`: SHA-256 `406ed81d18ea6ba94374b60ab40603b53a6079a5a689e28b8e189c1169654a0d` for both. `.text` is exactly 308 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This entry refreshes `Parked/080BE7AC/`. The earlier copy there (2026-11-14) gives the same bytes and the same SHA-256; this revision takes its types and names from the siblings `0x080BE8E0` and `0x080BE5F4` (`Actor080BE7AC`, `RangeRequest`, `Tile080BE7AC`) and comments the `found <= 1` test. The refusals the earlier README listed at kit fcdf2d45 (default, `bounded-buffer-conditional-thunks-v1`, `canonical-thunks-interposed-pool-v1`) are unchanged at 18dcc516.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080BE7AC.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-v1`, `static-callback-buffer-v1`, and 60 other selector values | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `bounded-buffer-conditional-thunks-v1`, `bounded-buffer-conditional-thunks-discarded-scratch-v1`, `bounded-buffer-conditional-thunks-selective-scratch-v1`, `bounded-buffer-conditional-thunks-root-return-scratch-v1` (4) | `buffer callee 0x0812F0D8: buffer callee 0x0812E55C: buffer callee 0x0812E4F4: inconsistent possible pointer offsets at control-flow join` |
| `--function-address-profile canonical-thunks-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |

The other 144 selector values give 43 other refusals, none of them a match; the most frequent are `function address requires a canonical addressed function` (43), `private float requires unique undefined pinned helper symbols` (15), `aligned owner requires actual external two-byte Thumb alignment` (12).

## Cause

The walk follows the local addresses into the callees and refuses at the first indirect call it cannot link, the copy callback's `_call_via_r3` (default). The conditional-thunk selectors, which do admit a thunk call, stop earlier inside `func_0812F0D8` (`0x0812F0D8` -> `0x0812E55C` -> `0x0812E4F4`) at a join, because their proofs do not replay bounded loops (kit #153). In a scratch copy of the kit with loop replay enabled for those proofs (2026-11-14, not re-run), the next refusal was `conditional indirect call excludes local argument aliases and pointer words`: the swap temporary is an argument of the thunk call.

The copy callback is entry 0 of a ROM table whose words point into the code image installed at `0x03005E78`; the #190 comment below proposes a contract tied to that table entry. In the prototype measured for it, this function gets past the copier and then needs named data next to the buffer proof on the plain path (the table reference `data_0836D4BC` is a data relocation). With both rules it gives `MATCH - byte identical` (not re-run here).

## Source notes

- `if (found <= 1) return found;` is in the ROM (`cmp r1, #1; ble` at `0x080BE858`), ahead of the sort's own entry test at `0x080BE864`; the earlier entry had listed it as a choice made for the register allocation.
- `last = found - 1` has its own frame word in the ROM (stored at `0x080BE860`, reloaded at `0x080BE8C4`). With the bound written as `i < found - 1` the function is 316 bytes (33 halfwords differ). Whether a named bound counts as allocation-only steering is a reviewer's call; it is recorded here as a doubt, not settled.

kit issue: shubshub/fftadecomp-kit#190 (comment to be posted)
kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data))
