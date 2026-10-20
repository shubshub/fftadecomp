# Parked: func_08123860

Status: plausible recovery, not byte-identical. The natural source names the
script-state and unit-array objects separately. Their enclosing source-level
relationship has not been established.

## Recovery and target

The target covers `0x08123860..0x08123898`: 19 Thumb instructions occupying
46 bytes, two alignment bytes, and two literal words. It clears the byte at
`0x02002184`, calls `0x0802D934`, `0x0802D824`, and `0x080D2F2C`, then calls
`0x0809A950` with unit base `0x02000080` and count 24 before returning `0x110`.

Bounded Binary Ninja and Capstone inspection confirm the control flow and
addresses. The fourth callee processes records at stride `0x108`; the first
helper independently accesses 24 records at the same unit-array base and
stride. The script-state base `0x020020D0` is also used by nearby handlers.
This establishes two real objects, but does not establish a containing type
that explains deriving one object's address from the other.

## Why the earlier byte-identical candidate was rejected

The ROM retains `0x020020D0` in `r4` across the first three calls, then adds
the literal `0xFFFFDFB0` to obtain `0x02000080`.
An earlier candidate reproduced all 56 bytes by expressing this as
`(void *)((u32)state - 0x2050)`.

Independent source review rejected that representation: the declared
`ScriptBattleState` had no enclosing relationship to the unit array, so the
negative offset was supported only by the observed register calculation.
Exact bytes and the automated plausibility check did not establish an
adequate source abstraction. That candidate and its match report were
removed; it must not be counted as a verified match.

## Natural recovery and remaining difference

The parked source uses the existing independently mapped objects
`g_state_020020D0` and `g_state_02000080`. With
`agbcc -mthumb-interwork -O2`, it produces a 48-byte ELF symbol:
15 instructions occupying 38 bytes, two alignment bytes, and two literal
words containing the object addresses.

With the candidate temporarily installed as `src/08123860.c`, the official
command failed with:

```text
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
  python3 ../fftadecomp-kit/tools/match.py --root . 0x08123860

compiled symbol is shorter than the indexed span: 48 < 56
```

The compiler no longer needs to preserve `r4`. It addresses the active flag
through the script-state symbol, then loads the unit-array symbol directly
for the last call. The retained base, address subtraction, register copy,
and saved-register epilogue in the ROM are absent.

No speculative enclosing layout was added to recover those instructions.
The function remains available for a later match once an independently
justified source representation is found; it is not declared inherently
unmatchable.
