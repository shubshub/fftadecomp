# 08016D64 — Parked

The complete indexed target is `0x08016D64..0x08016E1A`: 182 bytes and 89 reachable instructions. The tested natural C clears the byte flags, initializes the coordinate bounds, derives the transition steps with unsigned division, rounds the horizontal step to even for the relevant mode, and handles zero quotients.

The final native invocation used the approved ROM, fixed `agbcc -mthumb-interwork -O2`, and the default function-address profile. It returned exit 1 before runtime proof, byte comparison, or plausibility:

```text
compile failed:
division caller requires an exact nonoverlapping mapped Thumb span
```

A direct compile with the same flags emitted only the target FUNC, with complete ELF symbol size 180 bytes and 88 instructions. It contains two compiler-generated `__udivsi3` calls from genuine unsigned C division; no runtime-address aliases or addressed helper calls are used. The target is two bytes and one instruction longer.

The remaining difference is local allocation around the first layout flag test: the ROM loads layout into R1, computes the mask in R0, loads width into R2 and height into R7, then copies the retained layout to R5. The candidate loads retained layout directly into R5 and width into R1, avoiding the ROM's preservation copy. The later masked-layout AND also uses R5 as its destination instead of R0. Store order and the two unsigned division operations were recovered, but natural local flag forms did not reproduce the remaining allocation. A semantic inline sizing helper was also tested; constant propagation reduced its emitted body to 146 bytes, so that form was discarded.

This directory preserves the final tested 180-byte candidate. No native byte-match score, runtime-proof success, or plausibility acceptance is claimed. Active unmatched source/report files and obsolete manual compile intermediates were removed.
