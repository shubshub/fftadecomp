# 080D2380 bounded matching attempt

Accepted claim6524624654, lane sol-2380. The best retained ordinary C
produces a152-byte complete symbol against the154-byte indexed function.
Native exit1 is a size refusal before full linking/comparison. No native
report or source-plausibility verdict was generated.

Three natural forms were tried: direct returns with word-valued locals
and a masked RNG bit; byte table values with a shared selection result
and narrowed RNG modulo2; and byte return with direct conditional returns.
Their native symbol sizes were152,152 and148 bytes. Form2 is retained.
Diagnostic assembly preserves the defining u32 RNG declaration and target
u16 result narrowing. The remaining differences include initialization
and narrowing scheduling, lookup-head registers, and special-case branch
and table-pool placement. The retained body has140 instruction bytes and
12 literal bytes with no alignment gap; target additionally has the observed
two-byte internal alignment gap. This does not remove the code-generation
differences. No filler or positional byte-equality score is proposed.

The record ID is the packed ten-bit field established by matched080D2D54.
The list lookup follows the preceding080D2300 source analogue. The retained
u32 input is narrowed at the u16 lookup boundary, matching observed low16
input behavior without claiming a unique historical nominal interface.
No residual-register parameters, padding, assembly, pragmas, volatile,
dead operations or verifier changes were added.

All exact candidates, native failures, diagnostic assemblies, complete
target evidence and runtime/source/mapping-bound receipts are retained in
state/matching-080D2380-author/result.json. No active source/report remains.
