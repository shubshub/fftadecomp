# 0x080DCFE4 - effect or delay task starter: bytes identical, refused (two local descriptors with local payload words at one scheduler call, and no ordinary call) (184 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `void *func_080DCFE4(Object080DCFE4 *object, void *second_value, u8 kind, u16 first, u16 second, void *parent, u16 amount)` is called from 196 `bl` sites in about 190 effect functions (`0x080E3AC8` to `0x0811A97C`). When bit 7 of the halfword at `object + 0xC` is set, it returns 0 for a null `second_value`, and otherwise builds a 12-byte parameter block at `sp + 0` (`object`, `kind`, the bytes 6, 4, 6, `second_value`) and starts `func_080DC55C` (payload size 0x38) with a 28-byte descriptor at `sp + 0xC` whose word +4 points at the block (`first` at +0x14, `second` at +0x16). Otherwise it returns 0 when `(s16)amount == -1`, and starts `func_080DCAD4` (payload size 0xC) with a descriptor at `sp + 0x28` whose word +4 points at a 10-byte payload at `sp + 0x44` (the word at `*object`, then 0x15, 0x1E, 0 and `amount`; `second` at descriptor +0x14). The compiler merges the two calls into one:

```
080DD03E  add  r2, sp, #0xc           @ first descriptor
...
080DD046  mov  r1, sp
080DD048  str  r1, [sp, #0x10]        @ descriptor +4 = parameter block
080DD04A  ldr  r0, =func_080DC55C
080DD04C  movs r1, #0x38
080DD04E  b    0x080DD080
...
080DD06A  add  r0, sp, #0x44          @ payload
...
080DD074  add  r2, sp, #0x28          @ second descriptor
...
080DD07A  str  r0, [r2, #4]           @ descriptor +4 = payload
080DD07C  ldr  r0, =func_080DCAD4
080DD07E  movs r1, #0xc
080DD080  ldr  r3, [sp, #0x70]        @ parent
080DD082  bl   0x08005B6C
```

There is no other call.

## The index

The index row `080DCFE4 080DD09C 184 92 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (92): the reachable CFG has 87 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080DCFE4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080DCFE4, with every callee and data symbol bound to its ROM address (1 `R_ARM_THM_CALL`, 2 `R_ARM_ABS32`). The 184-byte symbol equals the ROM span `[0x080DCFE4, 0x080DD09C)`: SHA-256 `cf24b04613eba38ece78d32295519ad93004a5fd55a1d3671e7db7c12f82a28d` for both. `.text` is exactly 184 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080DCFE4.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `unsupported stack-alias use or escape; function-buffer proof: buffer callee 0x08005B6C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1` | `scheduler contract excludes additional register or pointer-word aliases` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1`, `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1` and 4 others (10) | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `guarded scheduler requires predicates and exactly one scheduler site` |
| `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1` | `scheduler payload contract requires a frame of exactly the descriptor and one adjacent nonempty payload` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-two-payload-calls-v1` | `two payloads require exactly descriptor+4 and descriptor+8 pointer words` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |

The other 186 selector values give 58 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` (16), `private float requires an authentic zero-addend pinned data literal` (15).

## Cause

The function has no named data, so the default run tries the function-literal path and the function-buffer fallback: the walk refuses the stored stack addresses (`unsupported stack-alias use or escape`) and the fallback stops in the scheduler at its `_call_via_r3` thunk. `conditional-scheduler-descriptor-calls-v1`, the one-call selector this function fits, refuses the pointer words in the descriptors (`scheduler contract excludes additional register or pointer-word aliases`); the payload selectors want a frame of exactly one descriptor and one adjacent payload (this frame has two of each kind of record) or payload words at exactly +4 and +8. The branch selectors require at least one ordinary call target besides the scheduler, and this function has none, so they report `scheduler branches exceed the explicit call-site or target bounds`. The per-site rule the kit issue below asks for takes this function past the scheduler site in the prototype measured for that issue, to `stack aliases cannot be stored or spilled` (not re-run here); so it needs one more rule after that one.

## Source notes

- `start_task` and `start_delay` are `static inline` helpers for the two arms; the ROM has one call site for both (`0x080DD082`), which is what inlining them gives. `object_enabled` keeps the ROM's 0/1 re-normalisation of the flag bit (`cmp r0, #1; bne; movs r2, #1` at `0x080DD014`).
- The second arm's descriptor and payload are wrapped in one local struct (`Frame080DCFE4`). The wrapper is not needed: two separate locals, the descriptor declared first, give the same bytes (declared the other way round, 3 halfwords differ). The published file keeps the wrapper.
- `payload->unknown_06 = 0` is stored from R5, which holds the zero flag result on that path (`strh r5, [r0, #6]` at `0x080DD06E`).

kit issue: shubshub/fftadecomp-kit#237
