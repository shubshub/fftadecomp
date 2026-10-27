# 08142BE8 — Parked

Complete natural reconstruction of the GNU libgcc binary64 packer, adapted from the local `fp-bit-base.c` source. The incoming pointer addresses a class/sign/exponent/fraction record; the result is returned in R0:R1 as a double, with the original word-order swap. Variable unsigned 64-bit right shift naturally emits the canonical `__lshrdi3` relocation.

## Fresh native result

Fixed agbcc `-mthumb-interwork -O2`, approved AFXE ROM, ordinary native matcher with automatic canonical logical-right-shift proof; no optional software-double profile.

- Target: `[08142BE8,08142D34)`, 332 bytes / 139 reachable instructions.
- Candidate: complete 332-byte ELF symbol; diagnostic linked comparison matches 318/332 bytes and 129/139 same-address instruction encodings.
- Fresh native matcher exit: **1**. Exact refusal: `lshrdi3 caller requires exact complete mapped ROM bytes`.
- The exact-caller-byte gate refuses before plausibility. No plausibility success or match credit is claimed.
- Evidence is in sibling address scratch `08142BE8/final-native.log` and `candidate-difference.json`.

## Precise remaining difference

Fourteen differing bytes affect ten two-byte instructions, confined to `08142CF4..08142D08`. All earlier classification, rounding, underflow/overflow, canonical logical shift, literals, and the final word swap/return match. The candidate and target have the same overall extent, branch destinations, and instruction boundaries.

After the shared SP base is placed in R2, the target shifts exponent/sign into R1 and loads the old halfword/byte into R3, materializing each clearing mask before that load. The candidate shifts into R3 and loads the old halfword/byte into R1 before materializing the clearing mask. The corresponding AND/OR operand encodings differ. This is the unresolved register allocation/load scheduling difference in the final packed bitfield stores.

## Bounded natural forms ruled out

1. Direct assignments to the original packed union's fraction/exponent/sign fields emitted 336 bytes. Separate SP-base materializations for exponent/sign caused a four-byte complete-extent refusal.
2. A named packed field structure and pointer view for all three assignments emitted 332 bytes, but moved base construction ahead of the fraction store and differed in 34 bytes.
3. Direct fraction assignment followed by a shared pointer view for exponent/sign emitted 332 bytes and reduced the residual to 14 bytes. This is the preserved candidate.
4. A pointer to the complete union instead of its field structure produced the same 14-byte residual.
5. Natural unsigned-short exponent / unsigned-char sign bitfield types also produced the same 14-byte residual.

No inline assembly, pragmas, artificial volatile, forced inline, runtime aliases, padding, compiler flag changes, or verifier changes were used. Shared files and other addresses were not modified. The failed active source/report are removed; this pair is the frozen bounded outcome.
