# 080C4A40 bounded matching attempt

Accepted claim 6524303195, lane sol-4A40. The retained ordinary two-loop
implementation is plausible and has the full 224-byte symbol. Native exit 1:
220/224 bytes and 106/110 instructions are identical.

Only four instructions differ. At 080C4AA0 and 080C4AFC, the compiler leaves
the cost difference in r2 while ROM writes r1. At 080C4AA6 and 080C4B02, the
score add/subtract therefore uses r2 rather than r1.
All branches, loads, helper calls, frame operations and s16 narrowing match.

Three natural forms were tried: one combined constant-first expression,
a constant-last expression, and a named cost temporary evaluated before
updating score. The third form is retained. No assembly, pragmas, volatile,
artificial storage, dead operations or compiler steering were introduced.

The helper uses the defining u8 func_080C8280(const void *) declaration.
Context and unit field views follow existing 080C4964/080C4B20 sources.
No native gate or shared input was changed. The report records NOT MATCHING;
there is no MATCH claim. Full machine/source/mapping-bound receipts and
earlier attempts are in state/matching-080C4A40-author/result.json.
