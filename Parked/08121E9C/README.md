# 08121E9C

Unmatched after three bounded plausible source candidates with agbcc
`-mthumb-interwork -O2`. Every native execution exited 1 and marked the source
plausible. The complete target is 84 bytes and 28 instructions; each candidate
compiled to the same 88-byte body with 29 instructions.

The recovered behavior allocates 0x958 bytes from the owner at data_020159C4,
initializes it through g_callbacks_0836D4B8[0], then allocates 0x1000 bytes,
constructs its manager, and saves the global mode. The existing teardown
08121EF0 establishes fields at offsets 0, 4, and 0x10. The allocation and
manager signatures come from their existing matched implementations.

The remaining difference is register allocation and constant reuse. The
compiler saves each repeated size in r4 across calls, puts the global addresses
in r5/r6, adds argument copies, and saves/restores r6. The target holds the
globals in r4/r5, separately loads 0x958 into r1 at both uses, and recomputes
0x1000 in r1 at both uses. Literal positions, call displacements, and the
complete extent therefore differ.

The attempted forms were an existing explicit callback-thunk declaration,
the callback table invocation itself, and the table invocation with explicit
ROM-observed allocation size and only the known object prefix. All produced
identical native bytes. No assembly, volatile, pragmas, dead code, artificial
register pressure, helper body, or toolkit changes were used.

`match.md` is the exact final native failure report. It compares 88 bytes
because it follows the compiled extent, including four bytes beyond the
84-byte target. Its side-by-side disassembler also misdecodes some target
Thumb BL pairs. The authoritative 84-byte target and bounded decode are saved
in `state/matching-08121E9C-author/target.json` in the handover root; that
packet also retains all three execution logs, earlier candidates and reports,
and the source-bound current-machine receipt. Ordinary helper calls retain
the native ARM ABI boundary; no independent callee contract is claimed.
