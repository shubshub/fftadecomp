# 0x080D8924 - delayed tile effect starter: bytes identical, refused (a local three-halfword position passed through a scheduler descriptor) (172 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u8 func_080D8924(void *object, u16 flags, u16 delay, void *parent)` has 17 callers (19 `bl` sites; among them `0x080F6A40`, `0x080F7F70`, `0x081086D0` and `0x0811872C`). With `delay == 0` it returns `func_080D8858(object, flags)`; when `func_080DD698(object, 0x20)` is zero it returns `func_080DD494(object)`. Otherwise it reads the object's tile (the `s8` bytes at +0xA and +0xB of `func_080A880C(object)`) into two `s16` locals, takes the height from `func_0801CC18(x, y)`, converts the three with `func_0801CA78(x, height, y, &position[0], &position[1], &position[2])` into a local `s16 position[3]` at `sp + 0x28`, and starts a task through the scheduler with a 28-byte descriptor at `sp + 8` whose word +4 points at `position`. It returns 0 on that path.

```
080D8986  add  r4, sp, #0x28          @ &position[0]; R4 keeps it across both calls
080D8988  mov  r3, sp
080D898A  adds r3, #0x2a
080D898C  str  r3, [sp]               @ &position[1], fifth argument
080D898E  add  r3, sp, #0x2c
080D8990  str  r3, [sp, #4]           @ &position[2], sixth argument
080D8992  adds r3, r4, #0
080D8994  bl   0x0801CA78
080D8998  str  r4, [sp, #0xc]         @ descriptor +4 = position
...
080D89A2  ldr  r0, =func_080D82E0     @ callback literal
080D89A4  movs r1, #0xc               @ payload size
080D89A6  add  r2, sp, #8             @ descriptor
080D89A8  mov  r3, sb                 @ parent
080D89AA  bl   0x08005B6C
```

At the scheduler call R4 holds `&position[0]` and R5 still holds `&y` (`sp + 0x26`, set at `0x080D8958`).

## The index

The index row `080D8924 080D89D0 172 86 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (86): the reachable CFG has 76 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080D8924.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080D8924, with every callee and data symbol bound to its ROM address (7 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 172-byte symbol equals the ROM span `[0x080D8924, 0x080D89D0)`: SHA-256 `3b92d5085d1b8c027f7dee874f84ec7a8fd99d91addf6a0e523644b117ae97c9` for both. `.text` is exactly 172 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed: every data symbol the source names is already in `config/data_symbols.json`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080D8924.c`: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, and 2 other selector values | `unsupported stack-alias use or escape; function-buffer proof: buffer callee 0x08005B6C: buffer callee 0x08005954: function-buffer evidence excludes runtime call thunks in inspected dependencies` |
| `conditional-scheduler-projected-outputs-v1` | `projected outputs require four ordered helpers and one scheduler` |
| `conditional-scheduler-descriptor-calls-v1`, `conditional-scheduler-descriptor-payload-calls-v1`, `conditional-scheduler-descriptor-payload8-calls-v1`, `conditional-scheduler-two-payload-calls-v1` (4) | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-branch-descriptor-calls-v1`, `conditional-scheduler-following-call-v1` | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-eight-target-branches-v1`, `conditional-scheduler-twenty-four-target-branches-v1`, `conditional-scheduler-three-per-path-calls-v1` (3) | `ordinary branch calls exclude every live local alias and pointer word` |
| `conditional-scheduler-live-local-alias-calls-v1`, `conditional-scheduler-live-local-alias-payload-calls-v1`, `conditional-scheduler-sequential-live-alias-counted-loops-v1`, `conditional-scheduler-three-per-path-live-alias-v1` (4) | `live-alias calls exclude pointer-bearing slots and word provenance` |
| `conditional-scheduler-twenty-four-target-following-calls-v1` | `following-call contract requires one scheduler site and a reached following ordinary call` |
| `conditional-scheduler-sequential-leaf-output-calls-v1` | `scheduler leaf output excludes preserved-register aliases` |
| `conditional-scheduler-sequential-killed-alias-calls-v1` | `alias kill excludes preserved-register aliases` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler requires exactly one backward edge` |
| `conditional-scheduler-guarded-descriptor-calls-v1` | `predicate helper contains an unsupported or memory-writing instruction` |
| `conditional-scheduler-halfword-output-payload-v1` | `halfword payload requires one exact output leaf and one scheduler site` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-scheduler-indirect-manager-v1` | `indirect manager contract requires one direct scheduler call` |
| `conditional-scheduler-manager-offset-v1` | `manager offset contract requires one direct scheduler call` |
| `conditional-scheduler-manager-paths-v1` | `manager paths contract requires one direct scheduler call` |
| `bounded-buffer-three-halfword-output-v1`, `bounded-buffer-named-three-halfword-output-v1`, `bounded-buffer-nested-halfword-output-v1`, `bounded-buffer-direct-halfword-output-v1` (4), and 12 other selector values | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |

The other 170 selector values give 58 other refusals, none of them a match; the most frequent are `addressed data requires a mapped object and signed32 addend` (26), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The function has no named data (the only literal is the callback `func_080D82E0`), so the default run tries the function-literal path and then the function-buffer fallback. The walk refuses the stored descriptor pointer (`unsupported stack-alias use or escape`) and the fallback stops in the scheduler, which reaches its callback through `_call_via_r3`. The 25 `conditional-scheduler-*` selectors refuse on the caller's shape: the live-alias and branch selectors on the local pointers held in R4 and R5 and on the pointer word in the descriptor, the sequential selectors on those aliases in preserved registers, and the single-call selectors on the four other calls. The three-halfword-output selectors, whose shape this is (three local halfwords filled by a leaf), walk into the scheduler with the descriptor and stop at the same thunk. In the prototype measured for the kit issue below, the descriptor contract applied as a per-site summary admits this function with no other change (not re-run here).

## Source notes

- `s16 position[3]` is declared in an inner block with `height`. Declared at function scope, the slots move and 5 halfwords differ (same size); the ROM's offsets (`sp + 0x24`/`0x26` for `x`/`y`, `sp + 0x28` for `position`) are what the block gives.
- `get_coordinates` is a `static inline` helper for the two `ldrsb`/`strh` pairs at `0x080D8962`-`0x080D896C`; the bytes are those of the two stores written in place.
- The descriptor type names only what the function writes: `position` at +4, `delay` at +0x14, `flags` at +0x16.

kit issue: shubshub/fftadecomp-kit#237
