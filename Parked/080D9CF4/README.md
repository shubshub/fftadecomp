# 0x080D9CF4 - swing effect phase callback: bytes identical, refused (a 12-byte local point set walked three callees deep, refused at the indexing helper 0x080DA2D4) (618 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080D9CF4(void *task, SwingDescriptor *descriptor, SwingPayload *payload)` is the task callback that `func_080DAD94` starts through `func_08005B6C` (function word `0x080D9CF5` at `0x080DADB8`). It switches on `descriptor->phase`: phase 0 copies the position and mode from the descriptor; 0x100 starts two child tasks with `func_080DAB84` and sets the angles; 0x101 advances both angles, computes four offsets from `func_08007A60`/`func_08007A4C` (sine and cosine of the angle, scaled by 160 in mode 0 or 192 in mode 1, then divided by 0x100 through the Div wrapper `func_08141870`) and moves each child with `func_080DAD74(child, &points)`; 0x102 waits for both children to end (`func_080D9B64`) and sets phase 2.

The local is a 12-byte `SwingPoints` (three `s16` x/y pairs) at `sp + 0`, filled before each of the two calls:

```
080D9EAC  mov  r0, sp
...                                   @ points = {x, y, x - dx1, y - dy1, x - dx2, y - dy2}
080D9ECE  ldr  r0, [r4, #0xc]         @ first child
080D9ED0  bl   0x080DAD74             @ R1 still holds sp
...
080D9EF0  ldr  r0, [r4, #0x10]        @ second child
080D9EF2  mov  r1, sp
080D9EF4  bl   0x080DAD74
```

The walk follows the pointer down three callees. `func_080DAD74` (30 bytes) passes it on in R0 to `func_080DA77C(points, 3, ...)`, which keeps it in its own frame (`str r0, [sp, #8]`, `0x080DA788`), passes the address of its own local at `sp + 4` in R2 to `func_080DA2D4(points, 3, &start)`, and later reads `points[start]` and `points[(start + i) % 3]` through the Div remainder wrapper `func_08141874`. `func_080DA2D4` stores the R2 pointer into its own `[sp]` (`0x080DA2E2`), so it sits in the outgoing word at each of its `bl 0x08141874` calls, scans the three points with a computed index (`lsls r0, r4, #2; adds r0, r0, r7` at `0x080DA336`) and writes the result through it (`strh r2, [r1]`, `0x080DA332`).

## The index

The index row `080D9CF4 080D9F5E 618 309 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (309): the reachable CFG has 279 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-switch-aligned-v1`, `restoring-owner-switch-cycles-function-words-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080D9CF4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D9CF4, with every callee and data symbol bound to its ROM address (27 `R_ARM_THM_CALL`). The 618-byte symbol equals the ROM span `[0x080D9CF4, 0x080D9F5E)`: SHA-256 `604d13388be68e382769e21ab7a29ef43211f522398d594ff4174e361fb55007` for both. `.text` is 620 bytes: the symbol and the assembler's 2-byte alignment padding. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D9CF4.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-stack-index-v1`, `named-data-buffer-v1`, `bounded-buffer-guarded-bios-division-v1` (4), and 17 other selector values | `buffer callee 0x080DAD74: buffer callee 0x080DA77C: buffer callee 0x080DA2D4: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x080DAD74: buffer callee 0x080DA77C: buffer callee 0x080DA2D4: buffer callee 0x08141874: non-leaf calls and interrupts require linked CFG verification` |

The other 192 selector values give 61 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (42), `owner requires sole complete Thumb ELF function` (32), `private float alignment cannot have code or data references` (12).

## Cause

The default run and every buffer selector whose walk reaches the point set stop inside `func_080DA2D4` with `unsupported buffer pointer use or escape` (the `static-callback-*` selectors stop earlier, in `func_080DADFC`). Only `named-data-buffer-stack-index-v2`, the one proof with #183's forwarded-stack-argument rule, gets further: past that point and on to the Div remainder wrapper `func_08141874` called from the same callee, where it refuses (`non-leaf calls and interrupts require linked CFG verification`, the BIOS-wrapper summaries of kit #192). This agrees with what the kit issue below reports for its prototype, the forwarding flag turned on in the plain proof (not re-run here): the function gets past the forwarder and stops at `08141874`, and with a scalar BIOS summary as well at `buffer callee 0x080DAD74: buffer callee 0x080DA77C: local stack pointer escapes through a return register`. So it needs at least the forwarding rule and the Div remainder summary; no data symbols are involved.

## Source notes

- Three spellings are load-bearing, and each is the ROM's own arithmetic: the scaling as `v <<= 5; v += v * 4;` (`asrs r0, r0, #0xb` after the `lsls #0x10`, then `lsls r0, r0, #2; add sl, r0`; written `v *= 160` the function is 636 bytes), the mirrored angle as `~angle + 1` (`mvns; adds #1` at `0x080D9DC2`; with `-angle` it is 614 bytes), and `payload->countdown--;` as its own statement before the test (with `if (--payload->countdown == 0)` 17 halfwords differ).
- Descriptor and payload layouts follow the loads and stores (`descriptor` +0x14/+0x16/+0x18 in phase 0; payload words at +0xC and +0x10 for the children).

kit issue: shubshub/fftadecomp-kit#238
