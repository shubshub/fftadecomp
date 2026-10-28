# 0809D464 — unmatched

Target: complete `[0x0809D464, 0x0809D58A)`, 294 bytes / 141 reachable instructions.

The complete retained natural C candidate initializes movement state and object flags, invokes the observed update calls, checks the movement type/mode and route adjustment result, then adjusts interior route-point heights and sets the completion flag.

Final native matcher result: exit 1 before comparison, `compiled symbol is shorter than the indexed span: 284 < 294`. The direct compiler assembly listing contains 136 instructions. No native byte-match count or plausibility verdict was produced, and this is not a match.

Remaining differences observed in the compiler listing:

- Target keeps the movement-state base in sl/r10 and saves/restores three high registers. Candidate retains the base in r4 until its last field store and saves/restores only r8/r9.
- Initial halfword constants use different temporary registers and load/store scheduling.
- Target forms the signed destination-byte addresses at 0xFE and 0xFF independently before loading. Candidate reuses the 0xFE address and adds one.
- The retained explicit point-pointer loop has the target's decrement-before-pointer-update and zero-count termination. Its point initialization precedes the count-minus-one calculation, whereas the target orders those two setup operations oppositely.

Bounded tested loop forms:

- Forward index with indexed route accesses: 284 bytes; pointer update preceded decrement.
- A point pointer initialized at function entry and an explicit count-minus-one countdown: 288 bytes; additional saved-register allocation and signed loop termination differed.
- Forward index plus explicit point pointer initialized in the for header: 284 bytes, retained for the closer loop update/termination sequence.

All compiler flags remained fixed at agbcc `-mthumb-interwork -O2`. No assembly, padding, volatile access, register variables, or dead code were used. The unmatched active source and any address report were removed.
