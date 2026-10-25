# 080DFF8C: staged two-channel curve sampling

**NONMATCH. Preserve this unchanged first candidate in Parked only.** One
precompile-frozen natural source was compiled once with default
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. No source/type/order/register/flag
retry or native campaign followed. This receives zero compiled-match credit.

## Actual canonical result and ownership

The canonical tool exited 1 with the exact diagnostic:

```text
compiled symbol is shorter than the indexed span: 654 < 690
```

The passive observer recorded one compile return and one linked-function return.
Canonical main did not return an integer: it exited via the diagnostic string;
the observer printed that string and propagated process status 1. The tool
stopped before its comparison/report-writing stage. **No canonical match report
was produced**, and this README is not a replacement verification report.

| Body | Complete span | Reached instructions | Owned bytes |
| --- | --- | ---: | --- |
| ROM target | [080DFF8C,080E023E), 690 bytes | 337 | 684 code + 4 literal + 2 alignment |
| Compiled symbol | [080DFF8C,080E021A), 654 bytes | 319 | 648 code + 4 literal + 2 alignment |

Both original and linked .text sections are 656 bytes: the two-byte `c046`
assembler filler after the 654-byte symbol is excluded. It cannot supply the
missing 36 target bytes. The ROM's external interval E023E..E0240 is excluded
as well. The actual full 690-byte target remains authoritative; the candidate's
654-byte length does not define a smaller valid ROM function.

## Exact remaining differences

- The compiler allocates a 40-byte local frame instead of the ROM's 28 bytes;
  both save 32 register bytes. It keeps state/payload initially in r5/r4 and
  spills both, rather than the ROM's payload in r7 and state at frame+4.
- Direction branches merge their component selection and narrowing paths
  differently. The opaque call moves from E00E6 to E00B0 (54 bytes earlier).
  This is visible control-flow/register allocation, not missing direction cases.
- Different midpoint/fixed-point register allocation and extra stack reloads
  partly offset that shortening. Table calls move from E011E/E0146 to E00EC/E0116;
  the two sampler calls move from E0204/E0222 to E01E6/E0200.
- The compiled phase-0x101 increment and phase-0x102 completion share a store;
  the ROM instead shares the phase-0x100 increment and phase-0x102 completion
  store. Branch/return positions therefore differ throughout.
- Both bodies own the same constant 0x101, but the compiled literal/alignment
  are at DFFC8/DFFC6 instead of DFFC4/DFFC2. The complete result is 18 fewer
  instructions and 36 fewer symbol bytes, not a removable pool/alignment artifact.

Only 46 equal byte positions occur in the 654-byte overlap, and seven complete
instructions agree at their absolute positions. These are positional layout
counts, not semantic-equivalence percentages. Every differing byte and both
independently decoded complete CFGs are retained in the author bundle.

Complete raw original (1512-byte) and linked (5256-byte) ELF reparses confirm a
single owned function, five typed R_ARM_THM_CALL relocations to 141860, 07A60,
07A4C and twice E06A4, no unresolved linked symbols, no residual relocations,
no extra allocated sections, helpers or veneers. Static ordinary-call CFG
validation covers each complete body; targeted source plausibility has no
findings. Approved ROM identity, full ownership and frozen source/header/map/tool
identity rule out wrong-input, missing-pool and unresolved-relocation explanations.
No claim that all natural reconstructions must fail is made.

## Recovered semantics and limits

Constructor E0730's callback literal and 0x60 payload size support a compatible
three-pointer callback returning zero. Phase zero copies four signed-coordinate
halfwords, unsigned magnitude/count, direction byte and two output pointers.
It neither advances phase nor initializes arrays or padding. Phase 0x100 retains
the direction/equal-coordinate cases, signed16 component narrowing, opaque
result high-byte selection, arithmetic half-difference midpoints and signed
table-result scaling. Signed64 multiplication by 65536 expresses fixed-point
values without negative signed left-shift dependence. Count zero still gives
-65536 for the final coordinate. Phase reloads and all observed stores remain.
Phases 0x101/0x102 call the sampler with five arguments for the two outputs;
there is no output-null guard. Other phases are idle.

The `u16 func_08141860(s16,s16)` declaration is qualified by current matched
08007AD0 and the four-byte SVC wrapper, not by an invented BIOS arithmetic
meaning. Original nominal types, hidden interrupt inputs, SVC return/preservation
and memory effects are not uniquely proved. The ordinary direct-call profile
assumes ABI-conforming returning callees. E06A4 remains **Parked, not matched**.
Valid objects, scheduler/descriptor lifetime, output capacity, successful sampler
allocation and safe/nondegenerate sampler inputs remain external obligations.
Counts 0/1/2 do not yield three increasing coordinates; no guards or repairs are
invented, and no all-input runtime-equivalence or transitive constructor proof
is claimed. No native campaign was run after the NONMATCH.

## Retained evidence and integration scope

Only this C file and README form the proposed Parked payload. Full evidence stays
at `/home/user/.codex-work/ffta-ulw/080DFF8C-author-next/`:

- `ABI.md`, `freeze.json`, `compile-start.json`: rationale, explicit chronology,
  first source plus all nine headers, private maps and toolchain bindings.
- `elf-capture.json`: raw complete ELF hex, all section/symbol/relocation data,
  linked function bytes and actual diagnostic/process status.
- `canonical.log`, `process-exit.txt`: the sole canonical invocation's result.
- `verification.json`, `DISASSEMBLY.md`: static full-body/ELF inspection and diffs.
- `HANDOFF.md`, `SHA256SUMS`: exact pins and final provenance.

Frozen/ready source SHA-256:
`e7c5b266d5aab695523ba012df3c0ad8d43de75c19743450c33af518cf6ce6b3`.
The separate `metadata.patch` corrects only DFF8C instruction count 345->337 and
legacy symbol size 26->690, with unchanged endpoints and no E0240 edits. Root
subsequently integrated its independently approved two-target metadata proposal;
the sole compile remains bound to the earlier isolated DFF8C-only mapping.
Metadata correction is not source-match credit. Root owns independent review,
integration and reservation release.
