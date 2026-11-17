# 0x080E0824 - palette fade effect phase callback: bytes identical, refused (the volatile semantic check's decision bound, after a CpuSet call with a dead local alias in R3) (616 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E0824(void *task, Command080E0824 *command, State080E0824 *state)` is the phase callback of effect 0x156, the first entry of the table `data_08395280` that `func_080D3508` reads (function word `0x080E0825` at `0x08395280`); no `bl` reaches it. Phase 0 takes a buffer from `func_080D3904`, saves the mode and copies 0x5F halfwords of `data_03003862` into it with CpuSet (`func_0814186C`). Phase 0x100 queues two VRAM fills (`func_08000B68` at `0x0600FFA0`, `func_08000B20` with tile 0x63FD at `0x06005800`). Phase 0x101 starts a palette fade (`func_08147D94`) and, in mode 1, sets up BG2, the blend registers in `g_control_flags_03000940` and two line interpolators (`func_080075CC`). Phase 0x102 steps the interpolators into BLDALPHA, waits for the fade, ends it, and in mode 1 recolours one palette block: `func_0801DD00(&count, &x, &y, &source)` fills four locals (`sp + 8` to `sp + 0x10`), CpuSet copies `count` halfwords from `source`, `func_08147830` blends each entry in a loop bounded by the local `count`, and `func_0801DD34` writes the block back. It then calls `func_080D3A14` and sets phase 2.

The four local addresses reach only `func_0801DD00` (`0x080E09FA`), a 52-byte leaf that stores through R0-R3 and does not write R2 or R3. So at the following CpuSet call R3 still holds `&source`, an alias nobody reads:

```
080E09F2  add  r3, sp, #0x10          @ &source
080E09F4  add  r0, sp, #8             @ &count
080E09FA  bl   0x0801DD00
080E09FE  ldr  r0, [sp, #0x10]        @ source
080E0A00  ldr  r1, [r6, #0xc]         @ state->palette
080E0A02  add  r2, sp, #8
080E0A04  ldrh r2, [r2]               @ count
080E0A06  bl   0x0814186C             @ CpuSet, R3 = sp + 0x10 (dead)
```

## The index

The index row `080E0824 080E0A8C 616 253 return` is right: the kit's `analyze.refine_function` at 18dcc516 closes the CFG at 253 reachable instructions over the indexed extent, and `config/functions.json` agrees.

## Byte identity

`080E0824.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E0824, with every callee and data symbol bound to its ROM address (30 `R_ARM_THM_CALL`, 9 `R_ARM_ABS32`). The 616-byte symbol equals the ROM span `[0x080E0824, 0x080E0A8C)`: SHA-256 `6eb82866dec0a44a3b67c607b0ab36cbdebcd21301882aa65fe0b3c23ac12953` for both. `.text` is exactly 616 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

`data_0600FFA0` is not in `config/data_symbols.json` on main at edc8e8f321; an open match batch maps it with its address as the value, and the runs below had that entry. Until that batch lands, add it the same way (`"data_0600FFA0": "0x0600FFA0"`). Every other data symbol the source names is already mapped.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E0824.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`. 192 selector runs print `source IMPLAUSIBLE` and `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding quoted under Cause; the others print `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `bounded-buffer-bios-fill-source-v1`, `bounded-buffer-bios-fill-local-source-semantics-v1`, `bounded-buffer-bios-fill-overwritten-control-stores-v1`, `--addressed-signed-runtime-profile addressed-native-bios-fill-buffer-data-v1` (5), and 187 other selector values | `verdict NOT VERIFIED - the selector was not run` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |

The other 18 selector values give 9 other refusals, none of them a match; the most frequent are `u16 switch-data requires a mapped local switch without other runtimes; function literals require and are required by a function-literal selector` (8), `unsigned thunks require actual canonical runtime and thunk calls, without other composition` (2), `switch thunks require a complete local switch, objects and no other runtime` (2).

## Cause

Two checks stand in front of this function. On the default path the buffer walk follows the dead R3 alias into the CpuSet wrapper and refuses there (`buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`). Every owner and addressed-runtime selector stops earlier, at the allowlisted volatile semantic check on `g_control_flags_03000940`, and prints `verdict NOT VERIFIED - the selector was not run`: for 189 of them the finding is `allowlisted volatile semantic check: real compile of func_080E0824: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` (the recolouring loop's count is a value read from the stack), and for the three BIOS-fill source selectors it is `allowlisted volatile semantic check: BIOS fill requires only a local R0 source and an external destination`. `plausible.py --strict`, the static check, exits 0. In the prototypes measured for the comments below (not re-run here), the BIOS memory-wrapper summary with the dead R3 alias admitted and named data beside the buffer proof take the function past the walk, and it is then refused by the decision bound of kit #137 alone.

## Source notes

- `tile = 0x63FD;` stands between the two `func_080D3AF8` calls because the ROM loads the constant into R4 there (`0x080E088C`), after the first VRAM request and before the second `func_080D3AF8` call.
- `data_0600FFA0` (the fill destination at `0x080E08A8`) is the only data symbol the source names that `config/data_symbols.json` on main lacks; see Data symbols.
- The source includes `control_flags.h`; the blend and display writes are member stores into its `g_control_flags_03000940`.

kit issue: shubshub/fftadecomp-kit#192 (comment to be posted); shubshub/fftadecomp-kit#137 (comment to be posted)
