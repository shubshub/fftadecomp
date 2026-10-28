# 08092784 — Parked complete reconstruction

Accepted claim: 6480813757 (codex-sol61-v826-08092784).
Target: [0x08092784, 0x08096B2C), 17,320 bytes and 7,226 reachable instructions.
Profile: restoring-owner-runtime-v1, immutable kit 4ae54d90aac99574a41a395fee7fc1da0c0a477c.
Compiler: unchanged agbcc -mthumb-interwork -O2.

The complete natural C reconstruction contains the 127-state dispatcher, its
three nested switches, tracking and movement state, state-stack operations,
typed callback calls, and genuine unsigned division expressions. The final
candidate compiles and retains the original, unmodified compiler relocatable
ELF in the sibling 08092784 artifact directory.

## Exact remaining gate

The final native match command exited 1 at validate_span with:
`inert spins require an exact unique nonoverlapping Thumb span`.
The sole emitted STT_FUNC is 17,740 bytes, 420 bytes larger than the required
17,320-byte owner. No compiled bytes were accepted as a match. The native
owner CFG/ABI/byte-equality/source-plausibility/replay sequence therefore did
not complete, and no match report exists. No match or instruction credit is
claimed; fresh report_matches is unavailable without a successful report.

The first byte difference is offset 0x0A: the generated stack reservation is
0x98 bytes versus the ROM's 0x90. Register allocation also differs (generated
object pointer r7 versus ROM r8). The linked candidate has 540 external static
call sites versus 543 in ROM. A diagnostic walk of every state finds the same
callee sets; state 105 folds two func_08025448 sites into one. These diagnostics
do not establish semantic equivalence or replace native verification.

The independent native source plausibility command exits 0 with no findings.
That result does not satisfy the earlier failed exact-span gate. Concrete
semantic refinements before freezing included the chain-index branch, two
state-stack transitions, low-byte result tests, the 0x15/0x16 record selectors,
and the first unsigned-division dividend's byte conversion. Further changes
would require more evidence about original layouts, scoped temporaries and
control flow; no artificial padding or register steering was used.

## Preserved evidence

The sibling address directory contains result.json, compile-result.json,
native-match.log, plausibility.json, original.o, original-symbols.txt,
compiled.s, compiled.bin, linked.elf, the complete target dump and the state
call diagnostic. All are outside disposable matching-root except this Parked
source/README pair. Active unmatched source and report were removed.
