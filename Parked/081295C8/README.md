# 0x081295C8 - phased tilemap transfer task: bytes identical, refused (a spawned task, four compiler `_call_via` callback calls and a function literal) (1992 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`u32 func_081295C8(void *task, TaskRequest *request, PanelState *state)` is a phased task of the 0x0812 module. Phase 0
sets the blend and display bits in `g_control_flags_03000940`, sets up two background layers, allocates and clears two
0x260-byte tilemaps and copies two palette rows. Phase 0x100 spawns the portrait task `func_08129D90` through
`func_08121B8C` with a stack request. The later phases page through a list: each entry is revealed and hidden by a
row ramp (`func_08007620`, `func_080076F4`, `func_08007894`) that queues tilemap transfers (`func_08000B68`,
`func_08000BAC`), its name is drawn into a text line, the portrait's pose is set and a sound is played, and button A
advances. Phase 0x102 restores the layers, frees the tilemaps and marks the caller's context complete.

## The index

The index row `081295C8 08129D90 1992 823 return` is right: the span holds 823 instructions with its literal pools,
and the next function, `func_08129D90`, starts at the indexed end. No index change is needed.

## Byte identity

`081295C8.c` (SHA-256 `849098e735947b530b3484bacd747d54508446aeef7032fb6268156f80e01727`) was compiled as `match.py`
compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x081295C8 with every callee and data symbol bound to
its ROM address (78 relocations resolved). The 1992 linked bytes equal the ROM span `[0x081295C8, 0x08129D90)`,
SHA-256 `ca9089a48e1d22f0fe93f40565dc43128c60fa5b1a4e61eda1ba43ef7e4eec8b`. `match.py` refuses before its own byte
comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Three symbols are needed; none is in `config/data_symbols.json`. Each address was found as an aligned literal word by
scanning the whole ROM, and every such word is inside this function. The extents are the distance to the next object.

| Symbol | Literal words | Object |
|---|---|---|
| `data_083C4510` | 0x08129988, 0x08129B10 | 0x260 bytes: the tilemap rows transferred to the second layer while the ramp runs |
| `data_083C4770` | 0x08129C74 | 0x8C bytes: the 10x7 tile block for a key whose `alternate` bit is set |
| `data_083C47FC` | 0x08129C70 | 0x8C bytes: the 10x7 tile block otherwise; the existing `data_083C4888` follows |

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x081295C8` with this source copied to `src/081295C8.c` and
the symbols above added. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `function-address evidence does not support runtime call thunks` | `tools/match.py:682` / `:1138` |
| `--owner-runtime-profile conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` | `tools/scheduler_entry_profile.py:66` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v1` | `call-site summaries exclude root calls through runtime thunks` | `tools/scheduler_call_site_profile.py:272` |
| `--function-address-profile canonical-thunks-v1` | `stack aliases cannot cross calls in caller-clobbered registers` | |

## Cause

The function combines three things that no single selector admits together (51 calls in all):

1. **A function literal**: `func_08129D90` (literal word 0x08129838), the spawned task's callback.
2. **A spawn with a stack request**: `bl func_08121B8C` at 0x0812981C (`src/08121B8C.c`), with `&child` on the stack.
3. **Four compiler-emitted callback calls** through the canonical thunks: `bl 0x0814224C` (`bx r2`) at 0x081297AE and
   0x08129888, and `bl 0x08142250` (`bx r3`) at 0x081297C4 and 0x081297DA. They are the calls through
   `g_callbacks_0836D4B8[0]` (clear) and `data_0836D4BC[0]` (copy) in phases 0 and 0x101.

Each selector stops at a different part of this composition: the default path at the thunk calls, the
canonical-thunks selector at a stack alias crossing a call, and the two scheduler selectors at their entry and
root-call contracts (refusal texts above).

## Source notes

1. **`static inline set_pose(state, pose)`.** The ROM has this block twice, at 0x08129C28 (pose 8) and 0x08129C96
   (pose 12), each opening with `ldr r0, [r7, #4]; bl func_08005BFC`. At the second site the pose constant is loaded
   at 0x08129C94 (`movs r4, #0xc`), ahead of the `state->task` load and the call: the argument is evaluated before
   the body starts. The two sites written out as plain statements differ (seven differing lines), as do three
   statement-macro forms (six, six and thirteen differing lines). A `u32 pose` parameter is also byte-identical.
   A reviewer should judge the helper under the inline-helper policy: two ROM copies, no out-of-line copy.
2. **`static inline next_transfer(state)`** is the text of the helper in the merged `src/081288C8.c`. The ROM repeats
   its load, stride, mask and store group eleven times (`movs rN, #0xb1` eleven times, first at 0x08129858); the
   address of the `next_transfer` byte at +0x3A4 (`movs r0, #0xe9; lsls r0, r0, #2`) is formed six times in the
   function and reused within a phase.
3. **A `source` local in phase 0x10A** for the two tile blocks. Passing the conditional expression straight to
   `func_08000BAC` differs (33 differing lines).
4. **`u8` return types for `func_08128B4C`, `func_0812949C` and `func_08021C5C`.** The ROM narrows each result
   (`lsls r0, r0, #0x18; cmp r0, #0` after the calls at 0x08129B8A, 0x08129BAA and 0x08129C8A), although their merged
   definitions (`src/08128B4C.c`, `src/0812949C.c`, `src/08021C5C.c`) return `u32`.

No original bug is reproduced.

kit issues: no issue yet for this composition. Related: shubshub/fftadecomp-kit#134 (compiler `_call_via` callbacks
through `g_callbacks_0836D4B8` / `data_0836D4BC` beside arithmetic runtimes) and #226 (a stack event descriptor whose
task callback runs through `_call_via_r3`; the same scheduler-entry refusal).
