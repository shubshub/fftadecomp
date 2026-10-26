# 080DCBBC

Complete recovered natural C; not a byte match. Target extent is
0x080DCBBC..0x080DCD06: 330 bytes and 151 reachable instructions.

The function allocates 0xC0 bytes for a candidate list and an exclusion list
at offset 0x60. Three 0x60-byte temporary allocations receive lists from
08099CDC, 08099D08 and 08099D34 using the current context from 08096D7C.
The first list becomes the candidates; the other two are concatenated as
exclusions. Candidate words absent from the exclusions are written to the
supplied destination. All temporary storage is freed, and the byte-sized
number written is returned.

The preserved candidate was tested with the default native matcher and fixed
agbcc -mthumb-interwork -O2. Native exit 1: compiled symbol 328 bytes is shorter
than the indexed 330-byte span. The extent rejection precedes byte comparison
and a plausibility verdict. No aligned score or same-offset byte-equality
count is claimed for this candidate.

The same fixed compiler's ELF symbol is 328 bytes / 150 reachable instructions.
The copy_and_free helper is fully inlined; func_080DCBBC is the only defined
function. The candidate uses the same 8-byte local frame, the same fourteen
external call sites and the recovered loop structure.

Precise remaining differences visible in the emitted assembly:

- The exclusion append pointer uses `add r6, r4, r0`; the target at 080DCC50
  uses the equivalent commutative operand order `adds r6, r0, r4`.
- After the third temporary free, the target at 080DCC88 copies the current
  count from r4 to r0. The compiler omits that move and keeps the value in r4.
- Consequently the candidate loads the saved candidate count into r0 rather
  than r1 for the first filter bound, then sums the two exclusion counts using
  r1/r4 instead of the target's r3/r0. The missing move accounts for the
  two-byte extent gap and changes subsequent relative branch displacements.

Bounded natural forms tried:

- Separate counts and direct copy loops: complete 330-byte symbol, but
  extensive count, pointer and index register differences.
- A reused current count saved after each copy/free phase: 328 bytes.
- Separate copy and filter indices: 328 bytes.
- Ordinary inline copy helper with filtering counters scoped to the final
  phase: 328 bytes, with the target's copy-loop register assignments.
- A separately promoted third count: 328 bytes, no retained count move.
- Ordinary inline copy-and-free helper returning the copied count: 328 bytes.
- Signed word-sized saved exclusion count, preserved here: unchanged 328-byte
  layout and remaining count-handoff difference.

No assembly, volatile storage, forced inlining, compiler flag changes, inert
operations or gate changes were introduced. This records a bounded source
mismatch, not a permanent impossibility claim. The final native output and
compiler assembly are retained in address-private scratch. Unmatched active
source/report removed.
