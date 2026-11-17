# 0x080FE2E8 - motion effect phase callback (effect 0x91): bytes identical, refused (two scheduler calls with local descriptors, three local coordinate outputs through the forwarder 0x080DBD78, and named data) (682 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080FE2E8(void *task, Descriptor080FE2E8 *descriptor, Payload080FE2E8 *payload)` is the phase callback of effect 0x91 in the table `data_083947D8` that `func_080D3508` reads (function word at `0x08394C58`); no `bl` reaches it. Phase 0 starts a first child with `func_080E03F8(actor, &data_0839D844, delay, 0, 0, task)`. 0x100 waits for it, stops when `func_080D3B54(actor)` is set, starts a sprite task, reads the start and end positions into the payload (`func_080DBD5C`, or `func_080D8B7C` when there is no target) and starts the 0x218-byte motion task `func_080FDF90` through `func_08005B6C` with a local 28-byte descriptor at `sp + 0x10` (palette, signed facing byte, and pointers to the two payload positions). 0x101 waits for the motion task to reach state 0x103 and, for a kind-6 target, reads the object's position into three local `s16` outputs and starts `func_080DFA30(target, 0x3D1, 6, x, z, duration, task)`; 0x102 ends the motion and starts a sound; 0x103 starts `func_080FE234` (0x24-byte payload) with a second local descriptor; 0x104 waits for the remaining tasks.

```
080FE41E  add  r1, sp, #0x10          @ motion descriptor
...
080FE42E  ldr  r0, =func_080FDF90
080FE430  movs r1, #0x86
080FE432  lsls r1, r1, #2             @ 0x218
080FE434  add  r2, sp, #0x10
080FE438  bl   0x08005B6C
...
080FE47E  add  r6, sp, #0x2c          @ &x
080FE480  mov  r2, sp
080FE482  adds r2, #0x2e              @ &y
080FE484  add  r5, sp, #0x30          @ &z
080FE48A  bl   0x080DBD78
080FE490  ldrb r3, [r6]               @ x, read back after the call
```

`func_080DBD78` (40 bytes) is a forwarder: it stores `&y` and `&z` into its own outgoing words for `func_0801C9F0`.

## The index

The index row `080FE2E8 080FE592 682 341 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (341): the reachable CFG has 289 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080FE2E8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080FE2E8, with every callee and data symbol bound to its ROM address (33 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 682-byte symbol equals the ROM span `[0x080FE2E8, 0x080FE592)`: SHA-256 `2ca2fb0a952ce0d6be79110cab1d2431ddb55eeac39be1320b79e89d616b2246` for both. `.text` is 684 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_0839D844": "0x0839D844"`) for the runs below: `data_0839D844`, `data_0839D8B8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080FE2E8.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `named-data-buffer-stack-index-v1`, `conditional-scheduler-three-per-path-live-alias-v1`, and 16 other selector values | `buffer callee 0x080DBD78: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2`, and 1 other selector value | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-twenty-four-target-branches-v1`, and 6 other selector values | `scheduler branches exceed the explicit call-site or target bounds` |

The other 183 selector values give 62 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed data requires a mapped object and signed32 addend` (26), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data and function literals, so the default run takes the function-literal path and refuses the first crossing local address (`stack aliases cannot cross calls in caller-clobbered registers`). The plain buffer selectors stop at the forwarder (`buffer callee 0x080DBD78: unsupported buffer pointer use or escape`). `named-data-buffer-stack-index-v2`, the one proof with #183's forwarding rule, gets past it and stops at the first scheduler call's callback thunk (`buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification`). The scheduler selectors bound the shape: the function has 33 call sites with 28 distinct ordinary targets (`scheduler branches exceed the explicit call-site or target bounds`), `conditional-scheduler-three-per-path-calls-v1` refuses the live local aliases (the coordinate pointers stay in R5 and R6 across the wrapper call and are read back after it), and `conditional-scheduler-three-per-path-live-alias-v1` stops at the forwarder. In the prototype measured for the forwarding issue below (not re-run here), the forwarding rule in the plain proof clears the wrapper and the function then stops at `inconsistent stack aliases at control-flow join`.

## Source notes

- The motion descriptor's facing byte is stored as `(s8)direction` (`lsls #24; asrs #24` at `0x080FE424`) after `direction` is narrowed to `u8` (`0x080FE414`), as the source writes it.

kit issue: shubshub/fftadecomp-kit#238
