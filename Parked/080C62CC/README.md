# 0x080C62CC - history state and display set-up: bytes identical, refused (the allowlisted volatile check's decision bound on a data-dependent copy loop) (436 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `void func_080C62CC(State080C62CC *state, const u32 *items, s32 count, u8 mode)` is called from `0x080C6858` and `0x080C7484`. It clears the 0xB4-byte state through `g_callbacks_0836D4B8[0]` (`_call_via_r2`), copies `count` words from `items` (an `ldm`/`stm` loop whose trip count is the argument, `0x080C62F4`-`0x080C62FC`), pushes a mode-dependent sequence of states onto the state's history (15, 11, 9, 8 and 5 when `mode` is set, 15, 11, 9 and 12 otherwise, then 7 and 14), copies 0x20 bytes from `func_080CBA3C(0)` to `data_03003A60` through `data_0836D4BC` (`_call_via_r3`), requests animation 1 on `data_02015744` (the statements of the matched `src/080C71B4.c`, inlined), and finally saves the display and blend-control fields of `g_control_flags_03000940` in the state and updates them:

```
080C6448  ldr  r2, =g_control_flags_03000940
080C644A  ldrh r3, [r2]               @ display
...
080C6452  adds r4, r2, #0
080C6454  adds r4, #0x4a              @ bldcnt_lo
080C6456  ldrb r1, [r4]
080C645A  strh r1, [r0]               @ state->saved_attributes
080C645C  movs r1, #0x80
080C645E  lsls r1, r1, #5
080C6460  adds r0, r1, #0
080C6462  orrs r0, r3
080C6464  strh r0, [r2]               @ display |= 0x1000
080C6466  ldrb r1, [r4]
080C6468  movs r0, #0xef
080C646A  ands r0, r1
080C646C  ldrb r1, [r4]               @ the second read
080C646E  strb r0, [r4]               @ bldcnt_lo &= 0xEF
```

## The index

The index row `080C62CC 080C6480 436 199 return` is right: the kit's `analyze.refine_function` at 18dcc516 closes the CFG at 199 reachable instructions over the indexed extent, and `config/functions.json` agrees.

## Byte identity

`080C62CC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080C62CC, with every callee and data symbol bound to its ROM address (5 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 436-byte symbol equals the ROM span `[0x080C62CC, 0x080C6480)`: SHA-256 `fc3923578566eaecaea0d819834e6d979e433cfb36f733d6746fb8cf201f8aa1` for both. `.text` is exactly 436 bytes. `match.py` compiles it, compares all 436 bytes and reports them identical, then refuses on plausibility (below). `plausible.py --strict` exits 0.

This entry refreshes `Parked/080C62CC/`, which held a 432-byte near miss (2026-10-28). That attempt isolated the last difference to the final byte update: the ROM reads `bldcnt_lo` again (`0x080C646C`) before the store, and the candidate did not. It ruled out a single-bit field, unsigned byte-width bitfields with byte and word base types, and a packed register-union view; it added no discarded-value expression, `volatile`, assembly, flag change or forced inline. This revision includes `control_flags.h`, whose allowlisted volatile view of `bldcnt_lo` gives exactly that second read, and is byte-identical. The state-history, word-copy, callback and animation sequences recovered then are kept.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080C62CC.c`: the default run and all 213 selector values. None matched. The default run reaches the byte comparison and prints a verdict; a selector run stops before the selector is applied.

| Selector | Refusal |
|---|---|
| default, and 1 other selector value | `verdict HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x080C62CC is not on the hand-asm allow list; park it, and only the maintainer may add it` |

The other 212 selector values give 11 other refusals, none of them a match; the most frequent are `verdict NOT VERIFIED - the selector was not run` (192), `u16 switch-data requires a mapped local switch without other runtimes; function literals require and are required by a function-literal selector` (8), `function address requires a canonical addressed function` (2).

## Cause

The bytes are identical and the default run says so (`199/199 instructions identical (436/436 bytes)`), but it records the source as `IMPLAUSIBLE (not on the allow list)` because the allowlisted volatile semantic check gives up: `allowlisted volatile semantic check: real compile of func_080C62CC: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)`. The loop with an unknown exit is the word copy, whose count is the third argument. The verdict then reads `HAND-ASM REQUIRED BUT NOT ALLOWED`, although the function needs no hand assembly. With a selector, the same finding stops the run first (`verdict NOT VERIFIED - the selector was not run`, 192 selector values). Nothing else in the function is refused on the default path: the two callback calls carry no stack address, and the function has no frame. Kit #137 is about this bound; the comment below adds this function as one for which it is the only refusal.

## Source notes

- `request_animation` has the statements of the matched `func_080C71B4` (`src/080C71B4.c`), which the ROM has inlined here (`0x080C641C`-`0x080C6446`), but its own type and member names (`Animation080C62CC`: `index`, `requested_index`, `s16 x`, `y`, `state`) where that file has `State` with `current`, `pending`, `u16 x`, `y`, `active`.
- `push_state` is a `static inline` helper for the repeated history push; each use is in the ROM.
- `plausible.py --strict` on the file exits 0; the finding above is from `match.py`'s own semantic check of the allowlisted volatile accesses.

This address is held only by that bound: no source policy question is open, and it is ready to ship once the volatile check can bound this loop.

kit issue: shubshub/fftadecomp-kit#137 (comment to be posted)
