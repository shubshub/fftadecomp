# 0x080D4DA0 - byte-identical; refused by the volatile semantic check (repeated stores to one member)

Retry of Parked/080D4DA0 on 2026-11-16, kit fcdf2d45. Bytes identical 76/76 (36/36 instructions); match.py refuses. Recorded as unmatchable: the
evidence requires maintainer review.

The source here uses include/control_flags.h: offset 0x46 of the block at 0x03000940 is `mosaic_lo`, a volatile u8 bit-field member, and the
function updates each nibble with two read-modify-writes (`mosaic_lo &= 0xF0; mosaic_lo |= low;` and the same for the high nibble). The volatile
member gives the ROM's dead ldrb before each store and keeps the two stores per nibble separate; the older parked source declared its own
non-volatile struct, whose two stores merged (60 bytes). RMW style as src/0813FAA0.c (winin_lo |= 4) and src/08126430.c (bldcnt_lo |= ...).
The volatile is the allow-listed declaration in include/, so the rule is met; the refusal is a verifier gap.

Refusals:
- default: bytes identical / source IMPLAUSIBLE (not on the allow list) / HAND-ASM REQUIRED BUT NOT ALLOWED; finding: allowlisted volatile semantic
  check: func_080D4DA0: the real and stripped compiles differ in observable behaviour (path 2, event 1: real store8 (g_control_flags_03000940 +
  0x46) <- trunc(0x8, and(load(...), 0xf)), stripped store8 (...) <- trunc(0x8, orr(and(load(...), 0xf), (lsr((arg(0x1)*0x1000000), 0x18)*0x10))))
- --owner-runtime-profile bounded-buffer-bios-fill-overwritten-control-stores-v1: source IMPLAUSIBLE / NOT VERIFIED - the selector was not run;
  allowlisted volatile semantic check: BIOS fill requires an actual direct call in its closed owner (the only selector that plausibly fits; it
  needs a CpuSet call).
plausible.py alone exits 0; the refusal comes only from the semantic check.

Why the C cannot change it: the check recompiles with volatile stripped and requires the same stores; without volatile agbcc folds the two writes
to one member into one store, in any spelling. The kit README (fcdf2d45, residual risk of the semantic check) already names this function as a
known false refusal: "It refuses legitimate volatile semantics ... repeated stores (x &= 0xF0; x |= v;, 080D4DA0). Such functions cannot use the
allowlist." A kit change admitting repeated stores to one allow-listed member would settle it.

Kit issue: (to be filed) - the semantic check compares against a volatile-stripped compile, which merges repeated stores to one allow-listed
member, so such functions are always refused (documented in the kit README, not tracked by an issue; #137 and #165 cover other bounds/windows).
