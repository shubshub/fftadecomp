# 0x080EF484 - scanline effect task: bytes identical, refused (the volatile semantic check's decision bound) (436 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. A task callback with a phase switch (0, 1 and
0x100-0x103). Phase 0 records the command's position, creates an effect, an animation and a controller, starts a
motion (`func_080E0608(&state->motion, y, y - 0x18, 0x3C)`) and sets `display |= func_080035A8(3)`
(0x080EF4EC-0x080EF4F0); phase 1 does nothing; phase 0x100 steps the motion and waits for it and the animation to
end; phase 0x101 counts 0x56 frames down, then creates a scanline task and fills its 160-entry buffer
(`func_080D996C`) with one value; phase 0x102 adds 2 to the first `state->counter` entries of the buffer each frame
until the counter passes 0x48, then clears `display` bit `func_080035A8(3)` (0x080EF600-0x080EF604); phase 0x103
waits for the scanline task and the effect to finish and sets phase 2. The index row `080EF484 080EF638 436 188 return` is right. No new
data symbol is needed.

## Byte identity

`080EF484.c` includes `control_flags.h` for `g_control_flags_03000940.display`, the header's non-volatile DISPCNT
copy; it accesses no volatile member. It was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`,
`agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080EF484, with every
callee and data symbol bound to its ROM address (18 `R_ARM_THM_CALL`, 5 `R_ARM_ABS32`). All 436 bytes of
`[0x080EF484, 0x080EF638)` equal the ROM: SHA-256
`9ad81dbb4a276bab49a7afab1e2ce3fcbdbce360b7e0f2b24791adb125515fdb` for both. `.text` is exactly 436 bytes.
`match.py` reaches its byte comparison and agrees:

```
bytes   identical
source  IMPLAUSIBLE (not on the allow list)
verdict HAND-ASM REQUIRED BUT NOT ALLOWED - byte identical, yet 0x080EF484 is not on the hand-asm allow list; park it, and only the maintainer may add it
plausibility findings:
  allowlisted volatile semantic check: real compile of func_080EF484: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)
188/188 instructions identical (436/436 bytes)
```

`plausible.py --strict` (the lexical check) exits 0; the finding above comes from the semantic check that
`match.py` runs for sources using the allowlisted declaration.

This replaces the earlier copy in this directory, a 444-byte candidate that was not byte-identical: its phase
switch had no `case 1`, and agbcc then roots the dispatch at 0x101 (from an extra literal word) instead of the ROM's
0x100, which shifts everything after it.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080EF484.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default | `HAND-ASM REQUIRED BUT NOT ALLOWED` (above): bytes identical, the semantic check fails |
| `named-data-buffer-v1`, `restoring-owner-acyclic-v1` and 187 other selector values (189) | `source IMPLAUSIBLE`, `verdict NOT VERIFIED - the selector was not run`, with `allowlisted volatile semantic check: real compile of func_080EF484: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)` |
| `bounded-buffer-bios-fill-source-v1`, `-local-source-semantics-v1`, `-overwritten-control-stores-v1` | `source IMPLAUSIBLE`, `NOT VERIFIED`, with `allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner` |

The other 21 selector values stop on their own shape requirements (switch data, thunks, runtimes, the inert-spin
and float profiles) before the semantic check.

## Cause

The semantic check executes the real, stripped and permuted compiles path by path and gives up after 32 unknown
branch conditions on one path. One loop causes it, in phase 0x102 (0x080EF5D4-0x080EF5E8):

```c
for (i = 0; i < state->counter; i++)
    buffer[i] += 2;
```

`buffer` is returned by `func_080D996C`. The bound `state->counter` is a `u16` field that the compiled loop reloads
after every store (`ldrh r0, [r5, #4]` at 0x080EF5E4), so each iteration adds one unknown branch condition. The
160-iteration fill in phase 0x101 (0x080EF5A0-0x080EF5AE) has a constant bound and does not count. With only the
phase 0x102 bound replaced by a constant (`i < 0x48`) in a scratch copy of the source, the check, run on its own,
passes: ``func_080EF484 agrees on 13 paths``. (That copy is not the ROM's size, so it was not run through
`match.py`.)

So this is the plain case of kit #137: an unknown loop bound, with no volatile access anywhere in the function.
Skipping the check for functions that touch no volatile member would not settle it on its own, because the loop
stores through a pointer returned by a call, which the check cannot rule out as an alias of the block.

## Source notes

- `case 1: break;` is an empty case. The ROM's dispatch is rooted at 0x100 (0x080EF490), the third of the six phase
  values; with only the five phases that have code, agbcc roots it at 0x101 (the earlier 444-byte copy). The
  matched `src/080E5310.c` of the same effect family also has a `case 1`.
- `func_080E0608(&state->motion, state->y, state->y - 0x18, 0x3C)` without the `(s16)` cast the earlier copy had;
  the callee's prototype narrows it.
- The phase-0 and phase-0x102 `display` updates are written as compound assignments on the allowlisted member.

## Ruled out

- No `case 1` (the earlier copy): 444 bytes, dispatch rooted at 0x101.

kit issue: shubshub/fftadecomp-kit#137
