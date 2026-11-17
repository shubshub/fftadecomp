# 0x080F8E3C - effect phase callback for effects 0x71-0x73: bytes identical, refused (local copies of two ROM tables through func_081443FC, indexed by the facing, in a callback with a `_call_via_r3` copy) (600 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080F8E3C(void *task, Descriptor080F8E3C *descriptor, Payload080F8E3C *payload)` is the phase callback of effects 0x71, 0x72 and 0x73: its function word is in entries 0x70 to 0x72 of the effect table `data_083947D8` that 0x080D3508 reads (`0x08394B58`, `0x08394B60`, `0x08394B68`), and `payload->index` is `kind - 0x71`. Phase 0 starts the source's first animation (`func_080E03F8(source, data_0839C354[index], ...)`). Phase 0x100 copies the two 4-byte tables `data_08149D64` (0, 1, 1, 0) and `data_08149D68` (0, 3, 0, 3) to the frame with `func_081443FC`, waits for the animation (`func_080E05DC`), starts the scene child `func_080DDF68`, reads the object's position into the payload (`func_080DBDC8`) and its facing (`func_080DBC88`), and creates a sprite with frame `first[facing]` and palette `second[facing]`; it also starts an animation and a record. Phase 0x101 copies the settings record `data_0839C36C` into the payload through the copy callback `data_0836D4BC[0]` (`_call_via_r3`), patches one field from `data_0839C380[index]` and starts `func_080DCFE4` with it; phase 0x102 waits for the children.

```
080F8EBE  ldr  r1, =data_08149D64
080F8EC0  add  r0, sp, #0x14         @ u8 first[4]
080F8EC2  movs r2, #4
080F8EC4  bl   0x081443FC
080F8EC8  mov  r4, sp
080F8ECA  adds r4, #0x18             @ u8 second[4]
080F8ECC  str  r4, [sp, #0x1c]       @ its address, kept in the frame
080F8ECE  ldr  r1, =data_08149D68
080F8ED0  adds r0, r4, #0
080F8ED2  movs r2, #4
080F8ED4  bl   0x081443FC
080F8ED8  ldr  r0, [r7, #0x18]
080F8EDA  bl   0x080E05DC            @ its walk reaches func_08005B58
```

## The index

The index row `080F8E3C 080F9094 600 300 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (300): the reachable CFG has 251 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-r3-thunk-switch-v1`: `complete-owner text reachable instruction count differs`).

## Byte identity

`080F8E3C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080F8E3C, with every callee and data symbol bound to its ROM address (22 `R_ARM_THM_CALL`, 11 `R_ARM_ABS32`). The 600-byte symbol equals the ROM span `[0x080F8E3C, 0x080F9094)`: SHA-256 `4db4fff04ed35889edb68b2a8a379efabbb74d0acd3ac864e2553fbd125364ec` for both. `.text` is exactly 600 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08149D64": "0x08149D64"`) for the runs below: `data_08149D64`, `data_08149D68`, `data_0839C354`, `data_0839C360`, `data_0839C36C`, `data_0839C380`, `data_0839C388`, `data_0839C394`, `data_0839C39C`, `data_0839C3A0`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080F8E3C.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 6 other selector values | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 4 others (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1`, `named-data-buffer-stack-index-v2` (3), and 59 other selector values | `acyclic owner excludes arithmetic runtimes and indirect thunks` |

The other 120 selector values give 33 other refusals, none of them a match; the most frequent are `function address requires a canonical addressed function` (30), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The only local addresses that reach calls are the two copy destinations (`func_081443FC`, count 4 each, a constant ROM source); the second one is also stored in the frame at `sp + 0x1c` and stays live across the rest of the phase. On the default path the walk stops inside `func_081443FC` at its alignment test. 62 owner selectors, among them the buffer-walking `named-data-buffer-*` ones (ROM-table-copy and stack-index included), refuse earlier, on the owner: the phase-0x101 copy is an indirect call through `_call_via_r3` (`bl 0x08142250` at `0x080F900C`, with no local argument), which the acyclic owner rule excludes. The function makes no direct `func_08005B6C` call, so the `conditional-scheduler-*` selectors refuse on their own contracts; the scheduler is reached only inside callees (`func_080E05DC` at `0x080F8EDA` calls `func_08005B58`, which runs a task's stored callback through `func_080058A4`). In the prototype measured for the `func_081443FC` issue below, a summary for local buffers takes this function past the helper, and it then stops at that dynamic task callback (`08005B58` -> `080058A4` -> `_call_via_r3`; not re-run here).

## Source notes

- Both tables are named ROM objects at their literals' addresses (`0x080F8F00`, `0x080F8F04`), and the copies are written as the calls the ROM makes, before the animation test, as the ROM orders them.
- The tables are indexed by the facing, `(s8)func_080DBC88(object)` (`0x080F8F48`-`0x080F8F52`). A stack-index proof would need it to be 0 to 3, and the facing byte is not established to be: `func_0809D6BC`'s -1 for coincident tiles reaches it unchecked through several writers (see 0x080DF14C and 0x080FDB98).

kit issue: shubshub/fftadecomp-kit#240
kit issue: shubshub/fftadecomp-kit#237 - listed there under the entries it does not cover (`func_08005B58` -> `func_080058A4`)
