# 0806D590 — unmatched

Target: complete `[0x0806D590, 0x0806D5F4)`, 100 bytes and 37 reachable instructions.
Compiler: fixed agbcc `-mthumb-interwork -O2`; ordinary native selector.

The complete natural reconstruction tests the context byte at offset `0x1A88`.
State 4 plays sound `0x64`, writes command `0x3C`, and saves event `0x17`
at context offset `0x446C`. Otherwise it tests state again; state 1 plays
sound `0x68`, writes command `0x3E`, and saves the same event.
All context loads and calls retain the target's order.

The best direct if/else reconstruction compiles to a 96-byte single ELF
function with 35 instructions. Native match exits 1 at the complete-extent
gate: `compiled symbol is shorter than the indexed span: 96 < 100`.
The byte-comparison, native plausibility and saved-report replay gates are
therefore not reached. A separate source-only plausible.py check exits 0.
No matched report is claimed.

Exact remaining layout difference: the target saves r4/r5/r6, copies the
input to r4 and r6, and retains separate byte stores through r4/r6 in its
two branches. The compiler saves r4/r5, retains one input pointer in r5,
and merges both command stores into one shared `strb r0, [r5]`. This
removes one pointer copy and one command-store instruction (4 bytes).
The shared event store and the two 0x1A88 literal words remain present.
The original unmodified relocatable object and generated assembly are
preserved in the sibling 0806D590 artifact directory.

Bounded natural attempts: direct if/else; an early-return first branch;
a guard-style second branch followed by the common event store; and a
semantic sound/command/event helper. Direct control-flow forms stay at
96 bytes. A plain static helper emits extra function text and is refused;
ordinary static inline compiles to 92 bytes. None reproduces the target.
The final parked candidate is the complete direct if/else reconstruction.
No flags, ABI evidence, mappings, assembly or volatile accesses were changed.

Zero match credit. Active unmatched source/report removed.
