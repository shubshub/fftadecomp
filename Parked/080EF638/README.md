# 0x080EF638 - BG2 rise effect child callback: bytes identical, refused (local halfword outputs passed to func_080DC224, whose callee chain reaches a jump table; every selector run stops at the volatile check's decision bound) (822 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080EF638(void *context, Message *message, State *state)` is the second child task of the effect `func_080EFAB0` (also parked), which starts it through `func_08005B6C` with a 0x2C-byte payload (function word `0x080EF639` at `0x080EFC6C`); no `bl` reaches it. Phase 0 takes the target from the message; 0x100 counts down and starts a VRAM loader (`func_080DC1E8`, `data_0600EE40` to `data_06005800`); 0x101 waits for it, sets the BG2 control word, enables BG2, reads the object's position into the payload (`func_080DBDC8`), converts it into two local `s16` offsets with `func_080DC224` and writes them as the BG2 offsets, then starts an interpolation of the vertical offset and the fade script `func_080D3E9C(data_0894D810, context)`; 0x102 and 0x105 follow the interpolation, converting each value through `func_080DC224` into one local output; 0x103 either starts a 0xA0-entry scanline overlay (`func_080D9914`, filled in a loop) or a second interpolation; 0x104 ripples the overlay entries in a loop whose exit depends on `state->timer`; 0x106 waits for the script and the overlay.

The locals are four `s16` outputs at `sp + 0xC` to `sp + 0x12`, each passed to `func_080DC224`, the last argument through the outgoing word:

```
080EF73E  mov  r4, sp
080EF740  adds r4, #0xe               @ &b, kept in R4
080EF742  str  r4, [sp]               @ fifth argument
080EF744  add  r3, sp, #0xc           @ &a
080EF746  bl   0x080DC224
...
080EF7AC  add  r4, sp, #0x10          @ &c (phase 0x102)
080EF7AE  str  r4, [sp]
080EF7B0  movs r3, #0
080EF7B2  bl   0x080DC224
```

`func_080DC224` (68 bytes) keeps the fifth-argument pointer in R4 across its call to `func_080DD6E0`, which reaches the jump table of `func_080C7EA4`.

## The index

The index row `080EF638 080EF96E 822 411 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (411): the reachable CFG has 354 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. None of the refusals below is an instruction-count check.

## Byte identity

`080EF638.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080EF638, with every callee and data symbol bound to its ROM address (35 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 822-byte symbol equals the ROM span `[0x080EF638, 0x080EF96E)`: SHA-256 `c76908f7ac493554d38cd7c4f841a66ac368a4e0aa41426eb51002ce68899b0c` for both. `.text` is 824 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_0600EE40": "0x0600EE40"`) for the runs below: `data_0600EE40`, `data_0894D810`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080EF638.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`. 192 selector runs print `source IMPLAUSIBLE` and `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding quoted under Cause; the others print `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `buffer callee 0x080DC224: buffer callee 0x080DD6E0: buffer callee 0x080C7EA4: unresolved program-counter write` |
| `bounded-buffer-guarded-switch-v1`, `bounded-buffer-root-guarded-switch-v1`, `named-data-buffer-v1`, `bounded-buffer-nested-halfword-output-selective-scratch-v1`, `bounded-buffer-guarded-callee-aliases-v1`, all 25 `conditional-scheduler-*` selectors (30), and 162 other selector values | `verdict NOT VERIFIED - the selector was not run` |
| `--control-flow-profile mixed-return-inert-spin-v1` | `unsupported stack-alias use or escape` |

The other 18 selector values give 9 other refusals, none of them a match; the most frequent are `u16 switch-data requires a mapped local switch without other runtimes; function literals require and are required by a function-literal selector` (8), `unsigned thunks require actual canonical runtime and thunk calls, without other composition` (2), `switch thunks require a complete local switch, objects and no other runtime` (2).

## Cause

The default run walks the first output pointer into `func_080DC224` → `func_080DD6E0` → `func_080C7EA4` and refuses at the jump table (`unresolved program-counter write`), the case of the switch-callee issue below; the prototype measured for it (not re-run here) then stops at the scheduler inside `func_080D3E9C`, which the per-site scheduler summary does not reach (it covers the owner's own calls). 192 of the 213 selector runs (every owner and addressed-runtime selector, the switch-constant selectors and the runtime selectors) stop earlier, before their proof runs: `verdict NOT VERIFIED - the selector was not run`, with the plausibility finding `allowlisted volatile semantic check: real compile of func_080EF638: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` (189 of them; the three BIOS-fill selectors report `allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner`). The loops in phases 0x103 and 0x104 and the source's `control_flags.h` member stores put this function in the kit #137 family as well: once the walk is admitted, that bound is still in front of it.

## Source notes

- The source includes `control_flags.h`. The display updates in phase 0x101 go through a `u32` temporary (`display |= mask;`); 0x104 and 0x105 clear the bit with a member compound assignment.
- `func_080DC224` is called with a null first output in phases 0x102 and 0x105 (`movs r3, #0` at `0x080EF7B0`), as the ROM passes it.

kit issue: (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout); (to be filed - match.py: a scheduler call with a local descriptor verifies only under shape-bound owner selectors; a per-site summary admits 7 byte-identical functions alone and 14 with companion rules); shubshub/fftadecomp-kit#137 (comment to be posted) (named there: 192 of its 213 selector runs stop at the decision bound; not in its table)
