# 080DFF04: conditional task creation and completion polling

**NONMATCH. Parked preservation only; zero compiled-match credit.** One natural
candidate was frozen and compiled once with the canonical default agbcc and
`-mthumb-interwork -O2`. The complete ELF function is140 bytes/67 instructions;
the independently qualified target is136 bytes/65 instructions. Both are
frameless and contain no literal pool or alignment bytes. No source, type,
register, ordering or compiler-flag retry and no native campaign followed.

## Recovered behavior and limits

The compatible three-pointer callback-shaped interface returns a full zero
word. Phase0 copies unsigned count/data/delay parameters without initializing
the existing task or advancing phase. Phase1 and unrecognized phases are idle.
Phase100 waits on the byte status from D8B4C, conditionally creates via D7A70
when data/count are nonzero, then reloads/increments the unsigned16 phase.
Skipped creation retains the old task. Phase101 decrements a nonzero delay,
polls/releases through D7ABC even for null, stores the result, and completes at
phase2 only when both the task and reloaded delay are zero.

Local fields and three external declarations are grounded in the sealed ROM
inventory and independent callee review. Original nominal types, registration,
global caller reachability, task initialization and scheduler correctness are
not established. Manager validity, descriptor consumption/nonretention,
allocation failure and task lifetime remain external obligations. Structural
ABI verification is not recursive callee or runtime semantic proof.

## Exact remaining differences

- Compiled entry saves r4-r7/LR rather than r4-r6/LR, retains parent in r7,
  and copies the state pointer from r5 into r6 at DFF0C. The ROM retains parent
  in r6 and uses r5 for the state throughout.
- Compiled phase increment loads/stores through r6 at DFF60/DFF64 and branches
  to its epilogue. The ROM loads through r5 at DFF5E and branches to a shared
  phase store at DFF82, also used by the phase2 transition. This adds one store
  in the compiled layout in addition to the extra entry pointer-copy instruction.
- The extra two instructions shift branches and BL encodings. The three linked
  targets remain D8B4C, D7A70 and D7ABC. Complete compiled ownership ends DFF90,
  four bytes beyond the real DFF8C boundary; that excess is not padding credit.
- At identical byte positions within the true136-byte target,10 bytes and2
  complete instructions agree. These positional counts describe shifted layout,
  not percentage semantic equivalence. Full target/compiled bytes, each differing
  offset and independently decoded CFG instruction lists are retained.

The canonical report honestly says `NOT MATCHING - bytes differ`, with main and
process exit1. Its `121/140 bytes` is an LCS-aligned diagnostic, not positional
equality. Its ROM display extends four bytes into the following function, and
decodes ROM using compiled instruction boundaries; consequently its `40/64`
instruction display and spurious coprocessor mnemonics are not an inventory of
the target. The authoritative separately decoded counts are65 target and67
compiled. The original report is preserved unmodified, not proposed for src.

The approved ROM, full-symbol ownership, nine unchanged headers, target-only
mapping correction, three typed relocations, linked CFG, absence of residual
relocations and source plausibility all check. Wrong ROM, missing pools,
external text alignment and unresolved relocation artifacts do not explain the
nonmatch. The source remains the first candidate; no assertion that another
natural reconstruction cannot match is made.

## Retained evidence and integration boundary

Only this C file and README form the proposed Parked payload. Evidence remains
under `/home/user/.codex-work/ffta-ulw/080DFF04-author-next/`:

- `ABI.md`, `freeze.json`, `compile-start.json`: precompile rationale, source and
  nine-header/map/tool fingerprints, serialized freeze and explicit start time.
- `elf-capture.json`: complete original912-byte and linked4540-byte ELF encoded
  as hex, all sections/symbols/relocations, function bytes and process status.
- `canonical.log`, `isolatedroot/docs/match/080DFF04.md`: sole canonical run.
- `verification.json`, `DISASSEMBLY.md`: complete ownership and exact comparison.
- `HANDOFF.md`, `SHA256SUMS`: provenance and sealed artifact manifest.

Source SHA-256:
`b24c612e2cadf68a8a68f9ecf878e1eb319736f0967990966845fd71eea7c5d5`.
The separate unapplied `metadata.patch` corrects only DFF04 instruction counts
68->65 and legacy symbol size14->136. It does not change endpoints, E0824,
BDB0, data mappings or any shared file. Metadata accuracy earns no C-match
credit. Root owns independent review, integration and reservation release.
