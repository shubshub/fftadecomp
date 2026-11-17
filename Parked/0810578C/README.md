# 0x0810578C - area-check effect phase callback: bytes identical, refused (two local 8-byte rectangles walked three callees deep to the BIOS Sqrt wrapper, with named data and a copy thunk in the owner) (420 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_0810578C(void *task, Descriptor0810578C *descriptor, Payload0810578C *payload)` is the task callback that `func_08105930` starts (function word `0x0810578D` at `0x08105D0C`); no `bl` reaches it. Phase 0 copies the descriptor's fields into the payload, copies 0x14 bytes of `data_0839FD40` into the payload through the copy callback `data_0836D4BC[0]` (`_call_via_r3`, `0x081057DC`), takes a frame and an optional extra byte from `data_0839FD54`/`data_0839FD5C` by selector, copies the two 8-byte ROM records `data_08149E44` and `data_08149E4C` into the locals `area` and `adjustment`, and calls `func_080DBF90(object, &area, 1, &adjustment)`. 0x100 waits for `func_080D8B4C` and reads the actor's coordinates into the payload; 0x101 starts `func_080DCFE4(actor, payload->unknown_28, 12, 0x28, mode, task, 30)`, a sound (`func_080DFD8C(data_0839FDE8, ...)`) and a coordinate task (`func_080D6098(..., data_0839FD10, task)`); 0x102 counts down, sets `*payload->done`, and waits for the tasks.

```
08105810  ldr  r2, [r1, #4]
08105812  ldr  r1, [r1]
08105814  str  r1, [sp, #0x10]        @ area = data_08149E44
08105816  str  r2, [sp, #0x14]
08105818  ldr  r1, =data_08149E4C
...
0810581E  str  r1, [sp, #0x18]        @ adjustment = data_08149E4C
08105820  str  r2, [sp, #0x1c]
08105822  add  r3, sp, #0x18          @ &adjustment
08105824  add  r1, sp, #0x10          @ &area
08105826  movs r2, #1
08105828  bl   0x080DBF90
```

The walk follows the two pointers from `func_080DBF90` into `func_080D8604` and `func_0801BB94`, which calls the BIOS Sqrt wrapper `func_08141898` (`svc 8`) at `0x0801BC14`.

## The index

The index row `0810578C 08105930 420 210 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (210): the reachable CFG has 179 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-r3-thunk-switch-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`0810578C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0810578C, with every callee and data symbol bound to its ROM address (11 `R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 420-byte symbol equals the ROM span `[0x0810578C, 0x08105930)`: SHA-256 `c2f111584263d2306588d895a10b3bc7fdbc86b171ad2a22a363ee73f7a4d99a` for both. `.text` is exactly 420 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149E44": "0x08149E44"`) for the runs below: `data_08149E44`, `data_08149E4C`, `data_0839FD10`, `data_0839FD40`, `data_0839FD54`, `data_0839FD5C`, `data_0839FDE8`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0810578C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `bounded-buffer-conditional-thunks-v1`, `bounded-buffer-conditional-thunks-selective-scratch-v1` (3), and 4 other selector values | `buffer callee 0x080DBF90: buffer callee 0x080D8604: buffer callee 0x0801BB94: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification` |
| `named-data-buffer-v1`, `bounded-buffer-bios-sqrt-scratch-v1`, `named-data-buffer-stack-index-v2` (3), and 59 other selector values | `acyclic owner excludes arithmetic runtimes and indirect thunks` |

The other 145 selector values give 44 other refusals, none of them a match; the most frequent are `function address requires a canonical addressed function` (43), `private float requires unique undefined pinned helper symbols` (15), `aligned owner requires actual external two-byte Thumb alignment` (12).

## Cause

On the default path the buffer walk enters `func_080DBF90`, `func_080D8604` and `func_0801BB94` and stops at the Sqrt wrapper three callees deep (`buffer callee 0x080DBF90: buffer callee 0x080D8604: buffer callee 0x0801BB94: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification`), the scalar BIOS summary inside the buffer walk asked for on kit #192. The conditional-thunk buffer selectors, which admit the owner's `_call_via_r3` copy call, stop at the same place. The owner selectors (`named-data-buffer-*`, the BIOS selectors, `bounded-buffer-bios-sqrt-scratch-v1` included) refuse the owner first: `acyclic owner excludes arithmetic runtimes and indirect thunks`, because of that thunk call. The function also has named data (eight data words, the two records among them), which the plain path refuses next to a buffer proof. In the prototypes measured for the issue and comment below (not re-run here), it matches with the BIOS summaries inside the buffer walk and named data beside the buffer proof on the plain path together, and with neither alone.

## Source notes

- `area` and `adjustment` are structure assignments from the two ROM records; agbcc copies each 8-byte record with two word loads and stores, as the ROM does.
- The payload copy is the call through `data_0836D4BC[0]`, the copy entry of the callback table (`ldr r3, [r2]` from the literal, then `bl 0x08142250`).

kit issue: (to be filed - match.py: named data and the generic buffer proof never compose, on the plain path (`buffer-call evidence does not support data relocations`) or on the function-literal path (no buffer fallback with data)); shubshub/fftadecomp-kit#192 (comment to be posted)
