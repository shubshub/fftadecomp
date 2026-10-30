# 080C9208 bounded matching attempt

Accepted native lease: claim 6531773049, lane sol-9208.
Target: complete Thumb [0x080C9208, 0x080C92F0), 232 bytes, 93 reached instructions.

The routine selects up to three indices with a nine-case switch, inspects member0
of the actual packed16-byte data_02002E78 records, and conditionally replaces an
index with the defining u8 func_080CCAD8(u8) result. The candidate preserves the
observed three-byte output and low16-bit selector boundary. No shared mapping,
header, helper signature, compiler flag or native profile was changed.

Three distinct natural forms were tried with the normal default native matcher:

1. A cached byte index and ternary assignment. Native stopped at
   `switch caller requires an exact mapped Thumb span`.
   The single parent-authorized unchanged-source compiler-only diagnostic measured
   an ELF function symbol of230 bytes. Its complete .text section was232 bytes,
   including alignment outside that symbol. The emitted loop eliminated the
   counter and used a separate ternary-zero path, differing from the target.
2. Direct output-index accesses with the packed u32 member value conditionally
   replaced by the helper result. Native stopped at the same mapped-span guard.
   This form's emitted extent was not separately measured.
3. Direct output-index accesses with an explicit packed-member guard and if/else
   output assignment. Native passed the exact mapped-span guard and stopped at
   `switch caller differs from the ROM`, the direct full-body byte comparison.
   This final source is retained here. No separate diagnostic was authorized or
   run for this form, so the exact emitted-byte differences are not available.

All three native attempts exited1. No MATCH or unsupported-model claim is made.
The three-form bound is exhausted. No successful proof was replayed.

Exact prior sources, source/header/map/runtime/binary pins before each attempt,
full native stdout/stderr, and the one complete diagnostic pipeline with ELF,
assembly, emitted and target bytes remain immutable under:
`state/matching-080C9208-author/` at the handover root.
The final frozen receipt there binds this Parked source and every attempt.
Native stopped before producing docs/match/080C9208.md; no report was fabricated.
The parent owns lease release and any later integration decision.
