080C1920 bounded predicate matching attempt

Accepted claim 6525547585, lane sol-1920.
Complete target [0x080C1920,0x080C1980): 96 bytes, 41 reached instructions,
92 code bytes and one four-byte named flag literal.

The source uses the defining C95A8 u8(u16) and AA10 s32(SearchContext*)
contracts, with explicit observed low-u8 casts of AA10. The actual defining
133BC4 helper returns u8 and calls the matched 131BB8 leaf. The pointer lookup
970E8 has complete bounded two-pointer input/pointer result ABI and matched
caller evidence. The SearchContext offsets 0 and 0x80 come from defining AA10.
The only global is the existing mapped byte data_030028A0.

Three natural forms were checked with the ordinary native command:
1. Sequential early returns: plausible 96-byte complete symbol, NOT MATCHING.
2. Nested positive predicates: plausible 96-byte complete symbol, NOT MATCHING.
3. Explicit per-path s32 result: plausible 104-byte symbol, NOT MATCHING.

The retained 080C1920.c/native-report.md pair is exactly attempt 2. It has the
best positional comparison among the two complete 96-byte forms: 43/96 bytes
match at identical offsets. The native alignment score of 80/96 is not an
exact positional-byte score. All complete logs and other attempts are retained
under state/matching-080C1920-author/.

Precise remaining difference: target places its shared true-return block at
0x080C1948 and branches back to it, with a false block at 0x080C1974 and the
flag literal at 0x080C197C. Attempt 2 branches on true to 0x080C1962 and uses a
false block at 0x080C1972. Its code is 90 bytes/40 instructions plus two alignment
bytes and the four-byte literal. Target code is 92 bytes/41 instructions with
no alignment. Branch offsets and subsequent BL displacement bytes consequently
differ. Attempt 1 puts its literal in the middle. Attempt 3 has the desired
first conditional direction but adds result-register moves and byte
normalization, producing eight excess bytes.

This is a branch/layout mismatch; the native verification profile accepts the
actual operations and all three sources are plausible. No unsupported gate,
MATCH credit, artificial operations, fake prototypes, inline assembly,
pragmas, volatile, shared-input edit or successful native replay is involved.
The native third comparison prints 104 target bytes into the following
function; the retained exact boundary and positional comparisons remain 96
bytes, and no credit is claimed for those eight out-of-span bytes.

Parent owns release and integration. Active source/report were moved out after
the bounded failure. Runtime, all nine headers, three map hashes, full target,
full native outputs and per-attempt exact comparisons are in result.json.
