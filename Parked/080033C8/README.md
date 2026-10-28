# 080033C8 — bounded nonmatch

Complete ROM owner: `080033C8..08003410`, 72 bytes / 34 reachable instructions.
Recovered behavior: for a `u16` count, wait for DISPSTAT (`04000004`) bit 0
to clear, then wait for it to set, once per iteration. The target reloads the
halfword on both polling backedges.

The preserved complete candidate uses the installed real data binding
`extern u16 data_04000004`, a `u16` counter, and the two direct polling loops.
With fixed `agbcc -mthumb-interwork -O2`, it compiles to 68 bytes / 32
instructions, four bytes shorter than the complete target. Native match exits
1 at the complete-symbol extent guard (`68 < 72`), before byte comparison,
plausibility evaluation, or source/report replay. There is no match credit.

The generated code hoists the loads from both polling backedges into their
preheaders; each backedge becomes a comparison-only self-loop. It also caches
the initial status bit across outer iterations and saves r6 in addition to
r4/r5. Thus the gap includes register allocation and repeated MMIO access,
not just a trailing literal. A direct typed-link diagnostic succeeds; only
12 bytes are equal at the same offsets, which is not an aligned diff score.

A volatile-qualified MMIO access ordinarily expresses these externally
changing reads, but this assignment and the native plausibility contract
forbid volatile. No volatile, artificial side effect, runtime alias, assembly,
compiler flag change, or compiler-steering expression was introduced. No
matching natural nonvolatile form was recovered in this bounded attempt;
this is not a permanent impossibility claim.

Native log and the last compiled assembly/object/linked bytes remain in the
private sibling `080033C8` scratch directory. Unmatched active C/report were
removed. Metadata and toolkit files were not changed.
