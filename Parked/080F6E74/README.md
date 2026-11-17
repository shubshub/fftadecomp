# 0x080F6E74 - facing-offset effect phase callback (effects 0x64 and 0x149): bytes identical, refused (a 16-byte ROM table copied to the stack and indexed by the facing byte, local outputs through the forwarder 0x080DBDA0, and a looped scheduler call) (748 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F6E74(void *task, Descriptor *descriptor, Payload *payload)` is the phase callback of effects 0x64 and 0x149 in the table `data_083947D8` that `func_080D3508` reads (function words at `0x08394AF0` and `0x08395218`; effect 0x149 sets `payload->mode`); no `bl` reaches it. Phase 0 copies the 16-byte table `data_08149D3C` (four `{u16 x, u16 y}` offsets) to the stack as a structure assignment (`ldm`/`stm`, `0x080F6ED4`), stores the facing byte of the object (`func_080DBC88`) as `payload->index`, reads the object's position into three local `u16` outputs with `func_080DBDA0(object, &x, &y, &z)`, subtracts `table.points[payload->index]` and passes the local result's address to `func_080E03F8(payload->data, data_0839BA10, animation, 6, &position, task)`. 0x100 waits for that child and starts a scene (`func_080D45D0`, `func_080DDF68(..., data_0839BA50, ...)`); 0x101 starts an output task and `func_080DFD8C(data_0839BA58, ...)` and counts the targets with `func_080D8924`; 0x103 starts one `func_080F6C48` child per target every 40 frames, in the first free of four slots, through `func_08005B6C` with a local 28-byte descriptor; 0x104 waits for everything.

```
080F6ED0  add  r1, sp, #0x14          @ table
080F6ED2  ldr  r0, =data_08149D3C
080F6ED4  ldm  r0!, {r3, r4, r5}
080F6ED6  stm  r1!, {r3, r4, r5}
...
080F6F0E  bl   0x080DBC88             @ facing byte
080F6F12  strb r0, [r7, #8]           @ payload->index
080F6F14  add  r5, sp, #0x24          @ &x
080F6F16  mov  r6, sp
080F6F18  adds r6, #0x26              @ &y
080F6F1A  add  r3, sp, #0x28          @ &z
080F6F22  bl   0x080DBDA0
080F6F26  movs r0, #8
080F6F28  ldrsb r0, [r7, r0]          @ (s8)payload->index
080F6F2A  lsls r0, r0, #2
080F6F2C  mov  r1, sp
080F6F2E  adds r1, r1, r0
080F6F30  adds r1, #0x14              @ &table.points[index]
```

`func_080DBDA0` (40 bytes) is a forwarder: it stores `&y` and `&z` into its own outgoing words for `func_0801C918`.

## The index

The index row `080F6E74 080F7160 748 374 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (374): the reachable CFG has 329 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F6E74.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F6E74, with every callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 6 `R_ARM_ABS32`). The 748-byte symbol equals the ROM span `[0x080F6E74, 0x080F7160)`: SHA-256 `7ca8399e6b24b94317fd13e883c47195c0af5e52a7e53abdc8a1a3db4a295a64` for both. `.text` is exactly 748 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D3C": "0x08149D3C"`) for the runs below: `data_08149D3C`, `data_0839BA10`, `data_0839BA50`, `data_0839BA58`, `data_088EAA30`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F6E74.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-rom-table-copy-v1`, and 16 other selector values | `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape` |
| `named-data-buffer-stack-index-v2` | `variable stack indices exclude pointer-bearing or return-carrying local words` |
| `conditional-scheduler-three-per-path-calls-v1`, and 7 other selector values | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `counted loop latch must be an unsigned lower or lower-or-same branch` |

The other 182 selector values give 67 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has named data and function literals, so the default run takes the function-literal path and refuses the first crossing local address (`stack aliases cannot cross calls in caller-clobbered registers`). The buffer selectors that walk the coordinate call stop at the forwarder (`buffer callee 0x080DBDA0: unsupported buffer pointer use or escape`), `named-data-buffer-stack-index-v1` included. `named-data-buffer-stack-index-v2`, which has #183's forwarding rule, gets past it and refuses the owner's stack words (`variable stack indices exclude pointer-bearing or return-carrying local words`): the outgoing word that carries `&position` to `func_080E03F8` is pointer-bearing, and the table is indexed by a variable. This is the v1/v2 split kit #200's comment reports. The scheduler selectors refuse the free-slot loop (`predicate composition excludes CFG cycles`, `counted scheduler loop requires a complete bounded instruction graph`, `counted loop latch must be an unsigned lower or lower-or-same branch`).

## Source notes

- The table index is `(s8)payload->index`, the facing byte `func_080DBC88` returns, the same index source as `0x080FDB98`. A stack-index proof needs it in 0..3. That bound is not proven: the facing byte can be -1 (`func_0809D6BC` returns -1 for coincident positions, and four writers store that unchecked), so even a selector that admitted the composition would need a premise that the evidence contradicts. This entry does not ship on a stack-index premise.
- `PointTable table = data_08149D3C;` is a structure assignment, which agbcc copies inline with `ldm`/`stm` as the ROM does; no copy helper is called. The literal at `0x080F6F7C` is the only aligned ROM word with the table's address.

kit issue: shubshub/fftadecomp-kit#238; shubshub/fftadecomp-kit#200 (comment)
