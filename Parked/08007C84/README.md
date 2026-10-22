# 08007C84 — Parked

One natural double-arithmetic reconstruction was compiled with agbcc
`-mthumb-interwork -O2`. No source spelling/flag search or addressed runtime
alias substitution was used.

- Target: complete `[08007C84,08007F9A)`, 790 bytes, 339 reachable instructions,
  40 bytes of required internal double constants and 2 bytes of internal
  alignment. The following 2 bytes before 08007F9C are external alignment.
- Candidate: complete 766-byte ELF symbol, 327 instructions; `.text` is 768
  bytes including 2 external alignment bytes. First difference at offset 0xC:
  ROM moves r0 to r10, candidate copies it to r7. 709 overlapping bytes differ;
  target has another 24 bytes. Both use 88 local bytes plus 32 saved bytes.
- Official pinned verifier: exit 1, `call target must be an undefined addressed
  function`, on the compiler's canonical floating helper relocations. No
  official accepted report/positive strict replay is claimed.
- A separate diagnostic typed link binds the compiler's six canonical
  soft-double names to the observed ROM entries solely for execution tests.
  All 35 BL relocations are resolved; this does not bypass the official gate.
- 56 bounded caller executions and 32 actual-helper microcases pass, with
  complete caller instruction coverage, full EWRAM checks, bounded writes,
  saved-register/SP/ARM–Thumb returns, and five detected negative controls.
  All floating helpers execute from the actual ROM; no helper models are used.

The recovered state contains two input-double-array pointers, a count, a phase
byte, current/start/end indices and four eight-double coefficient arrays.
Initialization constructs cubic interpolation weights. Processing emits eight
samples for each axis, copies an endpoint, and advances the index. Other phases
return 1 unchanged, as in the ROM.

This is bounded finite-domain evidence, not a general floating-point or alias
proof. Phase 1 requires initialized coefficients and valid disjoint objects;
integer/pointer calculations must be defined. Actual transitive packing code
reads some previously unwritten stack bytes; tested stack fills agree, but
arbitrary-initial-memory independence is unproved. NaNs, subnormals, overflow,
exception handling and general rounding-mode behavior remain outside the claim.

Author scratch `08007C84-author/CONTRACT.md`, `probe.py`, `check.py`, logs, ELF
metadata and input manifest contain the reproducible details. Only the index
instruction count needs correction, 395 to 339; endpoint unchanged. Source
remains Parked because both byte equality and official profile acceptance fail.
