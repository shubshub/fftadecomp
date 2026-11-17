# 0x080EFAB0 - three-child effect setup (effect 0x3D): bytes identical, refused (three scheduler calls with one local descriptor, local coordinate outputs through the forwarder 0x080DBDA0, and named data) (526 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080EFAB0(void *task, Command080EFAB0 *command, State080EFAB0 *state)` is the phase callback of effect 0x3D in the table `data_083947D8` that `func_080D3508` reads (function word at `0x083949B8`); `func_0810A4B0` and `func_0810CDDC` also start it (words at `0x0810A558`, `0x0810D318`); no `bl` reaches it. Phase 0 records the mode and object; for selector 0x117 it reads the target's position into three local `s16` outputs (`func_080DBDA0(func_080DD4B4(object, index), &x, &y, &z)`), packs `x - 0x78` and `y - 0x60` into a local 4-byte offset and passes its address as the origin of `func_080E03F8(object, data_08399A98, mode, kind, origin, task)` (selector 0x128 and the others pass a null origin). Phase 0x100 waits for that child, reads the target's coordinates into the payload (`func_080DD748`), and either starts `func_080DD214` (selector 0x117 when `func_08141874(...)` is non-zero) or starts up to three children with one local 28-byte descriptor at `sp + 0x10`: `func_080EF484` (0x24-byte payload), `func_080EF638` (0x2C, unless the effect mode is 2) and `func_080EF970` (0x28). 0x101 waits for the three children, 0x102 for the `func_080DD214` task.

```
080EFB1E  mov  r4, sp
080EFB20  adds r4, #0xa               @ &y
080EFB22  add  r3, sp, #0xc           @ &z
080EFB24  add  r1, sp, #8             @ &x
080EFB26  adds r2, r4, #0
080EFB28  bl   0x080DBDA0
...
080EFB4E  add  r4, sp, #0x2c          @ &offset, passed at 0x080EFB88 as the fifth argument
...
080EFC22  add  r4, sp, #0x10          @ descriptor, kept in R4 across the three scheduler calls
080EFC34  bl   0x08005B6C             @ func_080EF484
080EFC4A  bl   0x08005B6C             @ func_080EF638
080EFC5C  bl   0x08005B6C             @ func_080EF970
```

`func_080DBDA0` (40 bytes) is a forwarder: it keeps `&x` in a register and stores `&y` and `&z` into its own outgoing words (`str r2, [sp]; str r3, [sp, #4]`) for `func_0801C918`.

## The index

The index row `080EFAB0 080EFCBE 526 263 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (263): the reachable CFG has 224 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080EFAB0.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080EFAB0, with every callee and data symbol bound to its ROM address (21 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 526-byte symbol equals the ROM span `[0x080EFAB0, 0x080EFCBE)`: SHA-256 `53ac27184d8f0659c1925d72db071051466eada880aa51d706a11e599ec32a4b` for both. `.text` is 528 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08399A98": "0x08399A98"`) for the runs below: `data_08399A98`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080EFAB0.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `named-data-buffer-stack-index-v1`, `bounded-buffer-guarded-switch-v1`, `named-data-buffer-v1`, `conditional-scheduler-three-per-path-live-alias-v1` (4), and 15 other selector values | `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `bounded-buffer-root-guarded-switch-v1` | `root buffer requires one exact guarded switch and ordinary calls` |
| `conditional-scheduler-three-per-path-calls-v1` | `ordinary branch calls exclude every live local alias and pointer word` |

The other 189 selector values give 61 other refusals, none of them a match; the most frequent are `owner requires sole complete Thumb ELF function` (32), `addressed data requires a mapped object and signed32 addend` (26), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data (`data_08399A98`) and function literals, so the default run takes the function-literal path, which has no buffer proof, and refuses the first local address that crosses a call (`stack aliases cannot cross calls in caller-clobbered registers`). The buffer selectors that walk the coordinate call stop at the forwarder (`buffer callee 0x080DBDA0: unsupported buffer pointer use or escape`), the case #183 admitted only under `named-data-buffer-stack-index-v2`; that selector gets past it and refuses the owner's own local words (`variable stack indices exclude pointer-bearing or return-carrying local words`). The scheduler selectors refuse on the shape: the branch selectors count more scheduler sites than they allow (`scheduler branches exceed the explicit call-site or target bounds`), `conditional-scheduler-three-per-path-calls-v1` refuses the live local aliases (the descriptor in R4 across three calls), and `conditional-scheduler-three-per-path-live-alias-v1` stops at the forwarder. In the prototype measured for the forwarding issue below (not re-run here), the forwarding rule in the plain proof clears the wrapper and the function then stops at `buffer callee 0x080E03F8: unresolved program-counter write`, the jump table inside `func_080E03F8`, which the switch-callee issue does not reach because the function-literal path with named data has no buffer proof.

## Source notes

- The offset is a 4-byte `{s16 x, s16 y}` local whose halves the ROM writes with word read-modify-writes (`ldr r1, [sp, #0x2c]; ands; orrs; str` at `0x080EFB38`-`0x080EFB4C`), and the source's two member stores (`offset.x = x - 0x78; offset.y = y - 0x60;`) reproduce them.
- The descriptor's `object` is written only before the second and third calls (`str r0, [r4, #4]` at `0x080EFC40`, `0x080EFC52`), as in the ROM.

kit issue: (to be filed - match.py: forwarded callee stack arguments are admitted only under named-data-buffer-stack-index-v2; the generic buffer proofs refuse the 080DBDxx coordinate wrappers); (to be filed - match.py: the generic buffer walk cannot inspect a callee that contains a jump table (`buffer callee 0x...: unresolved program-counter write`), although two buffer proofs already decode the layout)
