# 0x08104AEC - party effect callback with ten small scan loops: bytes identical, refused (a dead stack alias that sends the proof into func_0801CC7C, which returns its own frame address in R2; and the scheduler loop bounds) (1366 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`u32 func_08104AEC(void *task, Command08104AEC *command, State08104AEC *state)` is a scene callback in the family of
`081168B4`. Phase 0 reads the leader's facing and position, scans the 16x16 map column or row from the leader for
the first and last walkable cells (`func_0801CC7C`, `func_0801CD08`, `func_0801CC18`), converts the cell to world
coordinates (`func_0801CA78`, `func_0801C918`), starts a setup task and calls `func_080DE268` on every party member.
Phase 0x101 repeats the scan backwards from the far edge, moves the camera (`func_0801BB0C`) and spawns five child
tasks through the scheduler `func_08005B6C` with a stack descriptor; the later phases wait for the tasks and spawn the
closing events.

## The index

The index row `08104AEC 08105042 1366 629 return` is right: the literal words are inside the function (the last at
0x08105008), and the span ends with `bx r1` at 0x08105040; 0x08105042-0x08105043 is zero padding before
`func_08105044`. No index change is needed.

## Byte identity

`08104AEC.c` (SHA-256 `43632d91d2c5129186fdcf0528f21a88ab27039c411f95eed015d316981242ad`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x08104AEC with every callee and data
symbol bound to its ROM address (43 relocations resolved). The 1366 linked bytes equal the ROM span
`[0x08104AEC, 0x08105042)`, SHA-256 `26e3b8c555dc9f5f7367f3884fc670b2f5322854a8bad626bf6cafbb98792fde`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Four symbols are needed; none is in `config/data_symbols.json`. Each address is exactly one aligned literal word in the whole ROM, inside this
function. The extents are the distance to the next object and are not otherwise proven.

| Symbol | Literal word | Use | Bytes |
|---|---|---|---|
| `data_0839F720` | 0x08104D28 | second argument of `func_080E03F8` (the setup task) | 0x18 |
| `data_0839F738` | 0x08105008 | second argument of `func_080DCFE4` | 0x14 |
| `data_0839F74C` | 0x08104D84 | event script for `func_080DFD8C` | 8 |
| `data_0839F754` | 0x08104F40 | event script for `func_080DFD8C` (the existing `data_0839F75C` follows) | 8 |

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x08104AEC` with this source copied to `src/08104AEC.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `unsupported stack-alias use or escape; function-data-buffer proof: buffer callee 0x0801CC7C: local stack pointer escapes through a return register` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v2` | `buffer callee 0x0801CC7C: local stack pointer escapes through a return register` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v1` | the same |
| `--owner-runtime-profile conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `--owner-runtime-profile conditional-scheduler-three-per-path-live-alias-v1` | the same |
| `--owner-runtime-profile conditional-scheduler-live-local-alias-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |
| `--owner-runtime-profile bounded-buffer-root-return-scratch-v1` | `buffer callee 0x0801CC7C: local stack pointer escapes through a return register` |
| `--owner-runtime-profile named-data-buffer-dead-argument-aliases-v1` | the same |

## Cause

1. **A dead stack alias in R2 sends the proof into `func_0801CC7C`, which returns its own frame address in R2.** In
   phase 0x101's first scan loop the compiler hoists the
   descriptor's address: `subs r2, #0x22; str r2, [sp, #0x50]` at 0x08104DC6 spills it and leaves the copy in R2.
   The loop then calls `func_0801CC7C(column, row)` at 0x08104DE4 (`ldrb r0, [r5]; ldrb r1, [r6]; bl`). A stack
   alias in a caller-clobbered register at a call makes the buffer proof walk the callee. `func_0801CC7C` writes R2 on
   every path (`adds r2, r4, #0` at 0x0801CCA6), but when `bge` at 0x0801CCD0 is taken it returns at 0x0801CD04 with
   R2 holding the address of its own local at sp+1 (`mov r2, r8` at 0x0801CCC8; r8 = sp+1 from
   0x0801CC94-0x0801CC98), and the walk refuses that at `match.py:5065`. The second scan loop has the same shape at 0x08104E62 (R2 = sp+0x18 from `mov r2, sp; adds r2, #0x18`
   at 0x08104E40). R2 is dead at both calls: nothing reads it before it is rewritten. kit#199 is the same refusal for a
   root that returns an expired frame address in R1; `bounded-buffer-root-return-scratch-v1` and
   `named-data-buffer-dead-argument-aliases-v1` refuse this function with the call-site summaries' line.
2. **The scheduler loop selectors' bounds.** `scheduler_loop_composition_profile.phases` requires the whole owner to
   fit its instruction bound (256, or 512 for the wide limits; `scheduler_loop_composition_profile.py:81` and `:91`);
   this function has 629 instructions. It also admits only loops that count in a register; eight of the ten loops
   here (the source's eight `s16` scan counters) count in stack slots (`ldrsh` of the slot, `cmp`, branch, call, back edge), so they fall outside the
   counted-loop rule whatever the bound. The live-local-alias selector refuses on its call-site and target bounds
   (`scheduler_branch_profile.py:59`).

## Source notes

1. **`unit = func_080DD4B4(state->value, i); func_080DE268(unit);`** in phase 0 (the ROM keeps the result in r6,
   `adds r6, r0, #0` at 0x08104D0C). The nested form `func_080DE268(func_080DD4B4(state->value, i));` differs
   (38 differing lines). The sibling `081168B4` uses the nested form.
2. **The descriptor is declared in the phase 0x101 block**, so its 28 bytes sit at sp+0x18, between phase 0's
   halfwords and this block's. Declared at function scope (as `081168B4` does) the function is 1346 bytes.
3. **`u8 mode` in phase 0**: `u32 mode` gives 1394 bytes. `081168B4` also uses `u8` there.
4. No volatile, no control flags, no helper or macro.

No original bug is reproduced.

kit issues: none for either refusal yet. Related: shubshub/fftadecomp-kit#199 (the same refusal for a root that
returns an expired frame address in R1).
