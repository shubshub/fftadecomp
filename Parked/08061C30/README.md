# 08061C30 — Parked, no match credit

Target: [0x08061C30, 0x08061C9C), 108 bytes and 45 reachable instructions.
Accepted claim: 6463132957, codex-sol61-v724-08061c30.

Recovered behavior: allocate a 100-byte sort workspace and a 16-entry pointer
table, populate pointers to the 28-byte records at data_02002948, sort using
the genuine func_08061C24 comparator through func_080028C8, assign ascending
nonzero ages at record offset 0x15, then free the table and workspace.

The frozen best candidate emits one complete 108-byte relocatable ELF
function with 45 assembly instructions under fixed -mthumb-interwork -O2.
Final native match attempt exits 1 with:
`compile failed: function-address caller differs from the ROM`.
This gate rejects the compiled caller while validating the callback binding,
before the ordinary byte-comparison/plausibility report is completed. No
plausibility, fresh-report, or exact-match success is claimed.

The concrete remaining difference is the initialization at 08061C46
through 08061C4E, spanning five instructions and ten instruction bytes. The
ROM computes the final record address first, using r1 for the 420-byte
record offset and adding it to the record base in r0. It then uses r1 for
the output cursor, initialized 60 bytes beyond the pointer-table base in r4.
The candidate initializes that output cursor in r1 first, then uses r2 for
the same 420-byte offset when computing the final record address in r0.
Both computations produce the same addresses; their order and temporary
register allocation differ.

The surrounding instruction sequence, descending initialization loop, sort
arguments, age-renumbering loop, cleanup and literal placement agree at the
assembly level. This comparison is diagnostic, not a successful linked-byte
verification or an assertion of a native N/N match count.

Natural forms tested included shared/separate signed counters, ascending
reverse indexing, descending for/do loops, typed pointer walking with the
observed signed address bound, explicit byte-offset walking, and typed/raw
record-base views. They produced 100-, 104-, 108-, 112- or 116-byte symbols or
the retained 108-byte initialization-order mismatch. Direct endpoint pointer
initialization folded the base and endpoint into one literal. Indexed loops
retained an extra counter or initialized the output cursor before the record
endpoint. The retained candidate is a complete tested attempt; no source,
compiler flags, ABI aliases, native gates, or metadata were changed to admit it.

Original unmodified compiler ELF and best assembly are retained outside the
matching root in the address artifact directory. Active unmatched source and
report are removed. Parent owns reservation disposition and integration.
