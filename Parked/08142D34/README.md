# 08142D34 — parked binary64 unpacking attempt

Target and best compiled ELF symbol both cover the complete Thumb extent
`[0x08142D34, 0x08142E10)`: 220 bytes and 97 reachable instructions, including
literal pools. A direct raw comparison of the best assembled symbol against
the complete indexed ROM span finds 216/220 bytes equal at identical offsets.
This is a raw same-offset byte count, not an accepted native match or aligned
native diff score.

The native matcher exits 1 with:
`compile failed: inconsistent stack aliases at control-flow join`.
It therefore does not generate a current matching report or plausibility verdict.
The owned unmatched src and stale initial native report were removed.

## Recovered behavior and types

The function unpacks binary64 into number class, sign, exponent and fraction.
It swaps the two incoming words, extracts a packed 52-bit fraction, 11-bit
exponent and one-bit sign, normalizes subnormal fractions, distinguishes NaNs
from infinities, and inserts the implicit significand bit for normal numbers.
The local toolchain source `/home/user/agbcc/gcc_arm/config/fp-bit.c` supplies
this same unpacking implementation and its packed bitfield, enumeration,
fraction union and unsigned DI-mode integer types. The preserved candidate
uses those types; no compiler flags, assembly, volatile, pragmas, shared files
or toolkit files were modified. No data binding is required.

## Exact remaining differences

| Address | Compiled | Target |
| --- | --- | --- |
| 0x08142D4C | `ldrh r0, [r2, #6]` | `ldrh r3, [r2, #6]` |
| 0x08142D4E | `lsls r0, r0, #17` | `lsls r0, r3, #17` |
| 0x08142D52 | `ldrb r0, [r2, #7]` | `ldrb r2, [r2, #7]` |
| 0x08142D54 | `lsrs r0, r0, #7` | `lsrs r0, r2, #7` |

All other bytes, including branch destinations, fraction shifts, output writes,
and literal pools, match at the same offsets. The candidate retains r2 as an
SP alias beyond sign extraction; the target clobbers it with the sign byte.
The native verifier consequently encounters inconsistent alias states at a
control-flow join. This is distinct from the unused-load-before-store family.

## Bounded attempts

Four fixed native invocations used agbcc `-mthumb-interwork -O2`:

1. A split 32-bit fraction model compiled to 248 bytes and failed comparison.
2. The actual packed 52-bit union and swapped-source pointer compiled to 220
   bytes but failed the native stack-alias join check.
3. The original signed sign local retained the same native rejection.
4. The original DI-mode fraction, class enum, fraction union and local ordering
   retained the same 220-byte symbol and native rejection; this is the preserved
   candidate.

Root owns reservation release and integration. No native success is claimed.
