# func_080922CC: the first heading of a camera pan ignores the target's quadrant

**Status: latent. No caller in the ROM can trigger it.** Every caller passes
`turn_percent` 100. With that value, the motion stepper replaces the bad
heading before the heading moves anything, so the shipped game behaves
exactly as the corrected code would. `repro.py` shows this step for step, and
shows the divergence with a `turn_percent` that no caller uses.

## The bug

`func_080922CC` sets up the camera pan that `func_08092390` steps. It computes
the target and the camera position in 8.8 fixed point:

* It stores `dx` and `dy`, made absolute, for the pan's span (`max(|dx|,
  |dy|)`). The absolute values are taken at 0x08092352-0x08092362, and the
  span is stored at 0x08092368 / 0x0809236C.
* It then derives the initial heading from the same absolute values:

```
0809236E  lsls r0, r2, #8 ; asrs r0, r0, #16    ; (s16)(|dx| >> 8)
08092372  lsls r1, r1, #8 ; asrs r1, r1, #16    ; (s16)(|dy| >> 8)
08092376  bl   func_08141860                    ; BIOS ArcTan2 (svc 0x0A)
0809237A  lsls #16 ; lsrs #24 ; str [r7, #0x10]  ; angle = ArcTan2 >> 8
```

ArcTan2 of two non-negative values lies in [0, 0x4000], so the stored heading
is always between 0 and 64 (0 = +x, 64 = +y, on a 256-step circle). A target
to the left of the camera or above it gets a heading mirrored into the first
quadrant.

## Trigger and reachability

The bad heading matters only if something uses it before it is corrected.

* **The only reader is the stepper.** The state is always `data_0200F4C0`.
  The ROM loads that address only to pass it to this function or to
  `func_08092390`: loads at 0x08093590, 0x080952B6, 0x0809690C and 0x08096938
  in `func_08092784`, plus `src/08096F3C.c` and `src/08096F7C.c`. Nothing
  refers to 0x0200F4D0, the heading's own address. `func_08092390` reads
  speed, positions, span and divisor, then calls `func_08007AD0` (bl at
  0x08092422). That stepper reads the heading.
* **The stepper corrects it before moving.** `func_08007AD0` computes the
  true heading from the *signed* differences. It wraps `true - angle` into
  [-128, 128], adds `difference * turn_percent / 100` to the heading and
  normalises it, and only then moves the camera along the new heading. With
  `turn_percent` 100 the heading becomes the true heading exactly (mod 256)
  on the first step, before any movement.
* **Every caller passes 100.** All four calls are BLs; there are no
  function-pointer references to 0x080922CC. Each passes the same four stack
  arguments, `(-120, -86, 4, 100)`:

  | call | stack-argument stores |
  |---|---|
  | `func_08092784`, bl at 0x080935A8 | 0x08093594-0x080935A4 |
  | `func_08092784`, bl at 0x080952D2 | 0x080952BE-0x080952CE |
  | `func_08092784`, bl at 0x0809692C | 0x0809691A-0x0809692A |
  | `func_08096F3C` (`src/08096F3C.c`), bl at 0x08096F6A | — |

To trigger the bug, a caller would have to pass a `turn_percent` below 100 for
a target left of or above the camera. No caller does.

## Behaviour against correct behaviour

Set-up headings on the 256-step circle:

| target from the camera | ROM | correct |
|---|---|---|
| right (+40, 0) | 0 | 0 |
| down (0, +40) | 64 | 64 |
| left (-40, 0) | 0 | 128 |
| up (0, -40) | 64 | 192 |
| (-40, +40) | 32 | 96 |
| (-40, -40) | 32 | 160 |

With `turn_percent` 100 (the game's value), `repro.py` sets up pans in twelve
directions and steps each one to completion with the ROM's `func_08092390`.
The state after every step and every camera position written are identical
between the ROM and the fixed build. They match even in the eight directions
where the two set-up headings differ.

With `turn_percent` 50 (hypothetical) and a target 40 px to the left, the
first step turns only halfway, from 0 towards 128:

* ROM: the heading becomes 64 and the camera moves *down*, from (100, 80) to
  (100, 82).
* Fixed: the camera moves left to (98, 80).
* The ROM's pan curves away from the straight line (4 px at most under the
  repro's ArcTan2 model) and takes 18 steps instead of 16.

## Impact

None in the shipped game. The wrong heading is overwritten inside the first
`func_08007AD0` call, before that call moves the camera, and no other code
reads it.

If a caller ever passed `turn_percent < 100`, pans towards the left or upward
would set off in the mirrored direction and curve back.

## Developer intent

The intent was that the initial heading points at the target.

The most likely mistake is variable reuse. The code takes `|dx|` and `|dy|`
in place for the span (`dx = -dx` when negative), then passes the same
variables to ArcTan2, which needs the signs to find the quadrant. The mistake
never showed up because the heading is re-aimed fully on the first step at
`turn_percent` 100, and that is the only value the game uses.

Evidence:

* `func_08007AD0`, the stepper this set-up feeds, passes the *signed*
  differences to ArcTan2 (`src/08007AD0.c`).
* Another motion set-up does the same job correctly. `func_0809CAF4` takes
  `|dx|` and `|dy|` for its distance test (0x0809CB54-0x0809CB68) but gives
  ArcTan2 the signed differences, `asrs #24` of the raw `dx << 16` and
  `dy << 16` at 0x0809CBB0-0x0809CBB4 (bl at 0x0809CBB6). The convention was
  signed input, kept separate from the absolute distances.
* `src/081287C4.c` repeats this function's set-up line for line, also passing
  the absolute values to ArcTan2. There `turn_percent` is the constant 100,
  so it is latent in the same way. It is a copy of the same template, not an
  independent design choice.

## The fix

```c
#ifdef BUGFIX
    state->angle = func_08141860((s16)((state->target_x - state->current_x) >> 8),
                                 (s16)((state->target_y - state->current_y) >> 8)) >> 8;
#else
    state->angle = func_08141860((s16)(dx >> 8), (s16)(dy >> 8)) >> 8;
#endif
```

This gives ArcTan2 the signed differences, exactly as `func_08007AD0` computes
them. The set-up heading then equals the heading the first step would choose.
That is why the fixed and the ROM builds agree whenever `turn_percent` is 100.
The default build is unchanged: it MATCHes 194/194, and `plausible.py
--strict` exits 0.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x080922CC and requires it to equal your ROM's
   194 bytes.
2. Runs the ROM bytes and the `-DBUGFIX` build from the same state.
3. Steps every pan with the ROM's own `func_08092390` / `func_08007AD0`.

Stubs:

* the projection `func_0801C918`;
* BIOS ArcTan2, modelled as `round(atan2(y, x) * 0x8000 / pi)`, which is exact
  on the axes where the heading assertions sit;
* the camera setter `func_0801E5E0`.

`func_0801E6F0`, the sine and cosine readers and the divide all run from the
ROM. Requires unicorn and the repository toolchain (see the docstring).

```
$ python3 docs/bugs/080922CC/repro.py baserom.bin
source src/080922CC.c: default build == ROM bytes [080922CC, 0809238E)

1. Set-up heading (0..255, 64 = +y), target 40 px from the camera:
  [ok] right ROM / BUGFIX: (0, 0)
  [ok] down  ROM / BUGFIX: (64, 64)
  [ok] left  ROM / BUGFIX: (0, 128)
  [ok] up    ROM / BUGFIX: (64, 192)

2. The game: every caller passes turn_percent 100.  The first step
   replaces the heading before it moves the camera, so the ROM and the
   BUGFIX pans are identical step for step, in every direction:
  [ok] (  40,   0) set-up heading   0 vs   0;  17 steps, camera paths equal: True
  [ok] (  40,  40) set-up heading  32 vs  32;  24 steps, camera paths equal: True
  [ok] (   0,  40) set-up heading  64 vs  64;  17 steps, camera paths equal: True
  [ok] ( -40,  40) set-up heading  32 vs  96;  25 steps, camera paths equal: True
  [ok] ( -40,   0) set-up heading   0 vs 128;  16 steps, camera paths equal: True
  [ok] ( -40, -40) set-up heading  32 vs 160;  23 steps, camera paths equal: True
  [ok] (   0, -40) set-up heading  64 vs 192;  16 steps, camera paths equal: True
  [ok] (  40, -40) set-up heading  32 vs 224;  25 steps, camera paths equal: True
  [ok] ( -37,  23) set-up heading  22 vs 105;  20 steps, camera paths equal: True
  [ok] (  51,  -9) set-up heading   7 vs 248;  20 steps, camera paths equal: True
  [ok] (  -5, -60) set-up heading  60 vs 188;  20 steps, camera paths equal: True
  [ok] (  90, -70) set-up heading  26 vs 229;  30 steps, camera paths equal: True

3. Trigger (no caller does this): turn_percent 50, target 40 px left.
  [ok] first step heading ROM / BUGFIX: (64, 128)
  [ok] first step position ROM (moves down, not left): (100, 82)
  [ok] first step position BUGFIX (moves left): (98, 80)
  [ok] ROM path leaves the straight line (> 1 px): True
  [ok] BUGFIX path stays on it, px: 0.0
  [ok] ROM pan takes more steps: True
  ROM: 18 steps, up to 4 px off the line; BUGFIX: 16 steps, on the line

4. Non-trigger at turn_percent 50: target down and right (+30, +20).
  [ok] set-up heading equal: True
  [ok] camera paths equal: True

all assertions hold
```
