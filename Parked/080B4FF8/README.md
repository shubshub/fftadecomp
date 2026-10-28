# 080B4FF8 — Parked

The complete target spans 080B4FF8..080B50EE: 246 bytes and 121 reachable instructions. The recovered function animates fourteen 15-bit RGB palette entries, using each entry's direction bits to move the three channels between 15 and 31. It uses the genuine named RAM symbol data_03003A64.

The final default native matcher exited 1 with plausible source and a complete 248-byte ELF symbol. The comparison reports 111/122 compiled instructions identical and 229/248 bytes identical. These counts cover the compiled span, which extends two bytes past the indexed target. This is not an exact match.

The RGB extraction, channel updates, direction-bit changes, recombination, palette store, and return instructions match. The remaining difference is the loop and its setup: the compiler replaces the ascending index 2..15 with a counter initialized to 13 and decremented through zero. The target increments its counter from 2 and compares against 15. The resulting initialization, pointer scheduling, counter update and comparison differ; the compiler needs an additional negation instruction and produces two extra bytes.

Tried natural explicit pointer iteration and array indexing, direct channel loads versus a cached color, an integer versus signed-short index, and ordinary for, do-while and explicit-break loop forms. Direct channel loads recover the target register assignment; the signed-short index introduces extra narrowing and address work. The ordinary integer for loop is retained. No compiler flags or shared metadata were changed, and no steering constructs were used.

The differing native report is retained privately outside the matching root at ../080B4FF8/native-not-matching.md. Unmatched active source and report were removed.
