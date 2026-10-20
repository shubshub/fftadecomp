# 0x08123E00

Status: natural control-flow recovery, not byte-identical or verifier-admitted.
The source remains a matching task; no match report is claimed.

## Complete boundary

Independent bounded Binary Ninja analysis finds 28 basic blocks and 325
reachable Thumb instructions, with all seven switch destinations resolved.
The complete function occupies `[0x08123E00, 0x08124238)`, or 1080 bytes:

- 756 instruction bytes, with the common return ending at `0x08124216`.
- 71 distinct PC-relative literal words, totaling 284 bytes.
- A seven-word switch table at `[0x08123E98, 0x08123EB4)`.
- Six two-byte zero alignment gaps before literal pools, totaling 12 bytes.

The last literal word is at `0x08124234`. The code at `0x08124238` is a
separate, previously unindexed function, not another pool or case. Its bounded
CFG has 12 blocks and 46 instructions, ending at `0x0812429E`; two external
alignment bytes precede the indexed function at `0x081242A0`.

## Recovered behavior

The input is narrowed to an unsigned byte. Mode 7 calls `0x08123D50` and
returns immediately. Other modes run common initialization, reset a range of
flags, and clear three bytes and a halfword in script state. Modes 0 through 6
then select seven case bodies; larger values return after initialization.

The cases set scene state and register callbacks in the table at
`0x03002710`. Mode 1 additionally clears counters and selected state flags,
processes 24 records at `0x02000080` with stride `0x108`, and resets another
flag range. Mode 2 selects two callbacks using flag `0x40`.

All recovered field offsets and record strides come from actual loads,
stores, and pointer increments. Callback symbols are stored as addresses,
not invoked here; their declarations deliberately leave argument lists
unspecified and do not establish their eventual invocation contracts.
The indirect region operation receives the observed destination and size;
its implementation or effect is not identified.

## Verification boundaries

The ROM only saves `r4`, `r5`, `r6`, and the return address. It has no local
stack allocation, stack-pointer arguments, or outgoing pointer slots, so the
bounded stack-buffer profiles do not address its blockers.

At `0x08123E74`, the ROM dispatches through the checked seven-entry jump table
using `mov pc, r0`. Supplying the actual ROM BL site/target pairs to the
existing CFG verifier solely to isolate caller control flow produces
`unresolved program-counter write`. This diagnostic is not a verified-call
claim or an accepted evidence profile.

The natural C switch also emits eight local `.text` `R_ARM_ABS32`
relocations: the table address and its seven destinations. Current linking
only accepts mapped external objects for absolute data relocations.
Callback-function address relocations are independently outside that data
contract. Neither issue is repaired by adding missing direct-call mappings.

The call at `0x08123E22` uses the real `_call_via_r2` thunk at `0x0814224C`
(`bx r2` followed by its alignment instruction). The pointer loaded from
`0x0836D4B8` is `0x03005E79`. The current tool recognizes that thunk shape;
this is not proof of the RAM routine's behavior.

## Candidate checks and outstanding work

The retained source compiles and assembles with the normal
`agbcc -mthumb-interwork -O2` flags to a complete 1056-byte function symbol,
24 bytes shorter than the recovered ROM extent. Its register allocation,
loop representation, and pool layout still need matching work. No linked
byte-equality score is asserted.

The scoped plausibility check reports zero findings. The normal command,
while this candidate occupied `src/08123E00.c`, stops with:

```text
compile failed:
call target is unknown, ambiguous, misaligned, or not Thumb ROM code
```

At that check, `0x08096BA0` and `0x0802DBA0` were absent from the function
mapping. Other directly called functions are indexed, although several
provisional extents have not been audited by this recovery. The caller's
full 1080-byte mapping and the separate `0x08124238` boundary were reported
to the coordinating session.

Only one natural implementation was compiled, apart from renaming a local
type that conflicted with the shared header. No switch-to-if rewrite,
artificial callback constants, compiler-flag sweep, assembly, volatile
access, pragmas, or verifier bypass was used. Matching requires supported
local switch relocations and control-flow proof, supported typed callback
address relocations, dependency mapping, and ordinary source-level matching.
