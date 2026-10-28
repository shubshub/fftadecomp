# 080C486C: complete natural C, byte mismatch

The ROM owner is [0x080C486C, 0x080C48A4), 56 bytes and 26 reachable
instructions, including the shared 0x2964 literal. Claim 6483162011 was
accepted. The final fixed agbcc -mthumb-interwork -O2 run returned 1:
NOT MATCHING, source plausible. The preserved candidate also has a complete
56-byte ELF function and 26 instructions, with no relocations.

Recovered behavior: read the unsigned halfword count at state +0x2964. For
that many records, copy the word at state +0x5C plus successive 0x328-byte
strides into the consecutive output words. Reload the count and return its
signed-16-bit interpretation. The output may alias state, so the final reload
is retained.

The remaining difference is allocation and scheduling. The ROM moves the
output to r5 before moving state to r1, then uses r2 for the record cursor,
r3 for the remaining count and r4 for the stride. The candidate saves state
in r4 and output in r5, then uses r3 for the cursor, r2 for the count and r1
for the stride. Its count copy precedes the stride construction, unlike the
ROM. The loop stores, branch destinations, return loads and literal have the
same recovered purpose, but the complete byte sequences differ. The native
alignment comparison reports 11/26 identical instructions (38/56 bytes).

Bounded natural forms tried: loading the count once followed by while,
explicit nonzero guard plus do/while, guarded for with a separately initialized
counter, typed 0x328-byte record structures, a byte cursor with word reads,
and a signed-16 return declaration versus an explicit signed-16 cast. The
single-count forms compile to 52 bytes; the guarded for adds a second guard
and compiles to 60 bytes; the final byte-cursor form and typed do/while form
compile to the same complete 56-byte candidate. No flags, assembly, volatile,
register bindings, artificial padding or dead code were used.

The original unmodified compiler ET_REL and assembly are retained outside the
disposable matching-root in the sibling 080C486C delivery directory, along
with the final native refusal log, failed report and result.json. The active
source and report were removed. This attempt has zero C matching credit.
