# 08009030 — Parked v2: grounded u16 helper return, unchanged bytes

The only C change from the preserved original is the return declaration of
`func_08015110`, from `void` to `u16`. Its actual returning epilogue subtracts
r10 from r5 and explicitly zero-extends the low halfword. The revised caller
continues to discard this result; no statement or compiler flag changed.
`source-change.patch` records the exact delta. This grounded type correction
is not a source-form search.

The fixed agbcc `-mthumb-interwork -O2` build produces the **identical complete
272-byte candidate** as before. The ROM is also272B, but **201 byte positions
differ**. The source remains Parked and is not a match.

## Complete extent and metadata proposal

The full owned range is `[0x08009030,0x08009140)`, containing244 code bytes /
116 reachable instructions and seven reached literal words. There is no
alignment padding. The internal word at0905C is skipped by both paths; trailing
words are at09128,0912C,09130,09134,09138,0913C. The latter four are omitted by
the old endpoint09130. The next indexed function starts at09140 and is excluded.
Raw Thumb branch/literal decoding, Capstone CFG traversal and Binary Ninja
instruction lengths agree. The separate proposal is end09130→09140,
bytes256→272, count128→116; no other function metadata is changed.

The original and linked candidate ELF symbols are each272B. Six Thumb-call
relocations bind five addressed helpers and the compiler's genuine
`_call_via_r2` thunk to typed odd Thumb symbols. No final relocation, additional
allocated payload, external padding or hidden pool remains. The callback is
loaded through actual ROM word0836D4B8; no addressed compiler-runtime alias is
introduced by the C source.

The first mismatch is at offset+0x0A: ROM `83 b0` reserves12 local/outgoing
bytes; candidate `82 b0` reserves8. The ROM spills the destination parameter
at SP+4, whereas the candidate retains it in `r9`. Register allocation,
table-address construction and reloads differ throughout. The candidate has
an extra literal for0836D4D8 (the first row's text-ID subarray) and reuses the
global-slot address instead of the ROM's duplicate global literal. Both complete
bodies still contain seven literal words and116 instructions; equal length
does not make them byte-identical.

- ROM body SHA256: `52fe5e61ac7bd2bf41a11a1e5fcf6e0e8fba01084cfd622fdd45ae4c71f16899`
- Candidate body SHA256: `e457039927e4b31d71e4793ee1a5dedfcac54c7234d01b2515206091ac985ed4`
- Source SHA256: `5cbde1a16a0d6a14bf5b1dd8cd14e9c9bf1a4a064f0c842a38fd453f065703a4`

## Official result and source diagnostics

The unchanged approved `kit-software-double-candidate-v3` accepts the supported
ordinary direct-call/thunk CFG far enough to compare the complete linked body,
then reports `NOT MATCHING - bytes differ`, exit1. Its generated nonmatch report
is retained only as `official-nonmatch.md` in the author evidence directory;
strict successful-report replay rejects it. No software-double profile is used.

The source checker also marks lines29/30 `SUSPECT: rom-address`, producing the
report's `IMPLAUSIBLE` status. These are the typed readonly initializers for
the actual row table0836D4D4 and text-pointer table085567F0. Their values and
uses are grounded by reached ROM literals, a20B row stride, halfword text-ID
loads and word pointer loads. Neither declaration writes ROM. This explains
the lexical suspects but does not waive the gate: the findings remain recorded,
and no suppression comment, allow-list or verifier edit was added. Byte mismatch
is independently sufficient to keep this source Parked.

## Behavior and arithmetic domain

The low byte of `index` selects a4B state record at active+0x338. A disabled
record returns0 without accessing tables or helpers. Otherwise selection picks
an ID from a20B ROM row and then a text pointer. If flag0x207 is clear and the
ID is3, row entry7 and cursor selection7 replace it. The caller clears an
active+0x6C8 buffer, optionally initializes/moves the cursor for index8, renders,
then copies from the freshly reloaded active buffer to destination plus the
freshly reloaded record-row byte times64, returning1.

`length = (22 - row) * 64` uses defined signed multiplication, not a left shift
of a potentially negative number. The promoted product lies in[-14912,1408]
and is converted to u16 modulo65536. For row23, length is65472, not a negative
or clamped size; the final halfword-copy count is length/2. This requires large
enough, live, suitably aligned, nonoverlapping storage. Nothing establishes
that every engine state meets those requirements. Enabled-case tests use only
the first nine actual ROM rows and selections0..7; no total table extent,
text-string validity or arbitrary index/selection safety is claimed.

The original record pointer and clear destination remain cached across calls,
but active-state pointers and the record's row byte are reloaded where the ROM
does so. The bounded checks deliberately mutate those values in larger-helper
models. Caller frame layouts differ (44B versus40B total), while both restore
r4-r11/SP and return correctly to ARM or Thumb.

## Bounded execution evidence

32 ROM/candidate executions cover eight cases, both return modes, EWRAM/IWRAM
states, disabled early return, flag false/true, ID3 fallback, index8 cursor path,
active-state replacement, row-byte reload, zero length and wrapped65472B length.
All116 caller instructions in each body execute across those cases. Checks
validate arguments including the outgoing fifth word, defined RAM reads, exact
nonstack writes, bounded stack writes, untouched remaining memory, result and
saved-register/SP ABI. Ten runtime negative controls and13 compiler layout/
arithmetic assertions pass. A compatible u16 redeclaration compiles without
diagnostics; the old void redeclaration is rejected as conflicting. Modeled
15110 returns0,1,32768 and65535 are ignored without affecting the checked
outcomes. The freshly source-bound negative report is rejected by strict replay.

Actual instructions execute for:

- The complete predicate080C9540..080C9572, including both outcomes.
- The real0814224C `bx r2` thunk and the50B clear body at03005E78.
- The four-byte0814186C `SVC0B; BX LR` wrapper.

The clear bytes are installed in the fixture from ROM
`[08A38A2C,08A38A5E)`, SHA256
`0dbe8fb48536010f6573169bf01637e474a3dff7d66bc1174ed0ba8bb0540a64`.
The actual pointer word is03005E79. **Installation and unchanged RAM identity
at invocation are explicit premises**; the startup installer is not executed
here. The separate installer audit is in `task-02768-installer-review/REVIEW.md`.
All tested nonzero clear lengths are multiples of64 with aligned buffers; the
clear leaf's unrelated unaligned/remainder paths are not exhaustively covered.

`08013528`, `08013728` and `08015110` are whole-call ABI/effect models. They
preserve callee-saved registers, clobber caller-saved registers/flags and perform
explicit synthetic writes/rebindings; their real bodies are not executed.
The 15110 model now supplies a canonical u16 return in r0 after volatile-register
clobbering; the caller does not consume it. This is an explicit return model,
not execution of 15110. The independently recorded epilogue
`[08015384,0801539C)`, SHA256
`c4b49c191f51d52443bf24b170e2d3f257ed6d0251ff5706d5f1ecb26cc1ecc7`, grounds
the declaration, not every path's feasibility, helper termination, historical
nominal C type or whole-helper semantics.
The actual SVC instruction is intercepted by an explicit halfword-copy CpuSet
model, restricted to aligned, nonoverlapping buffers and the observed low21-bit
count domain. **BIOS code is not executed.** Neither model results nor the
ordinary call-summary verifier prove the complete helper/engine semantics.

## Reproduce

`/home/user/.codex-work/ffta-ulw/08009030-author-v2/probe.py` creates a private
fixture from immutable `game-next-73c22d0`, copies all nine headers, applies only
the caller metadata proposal, runs the official normal match command and
records full ELF/difference evidence. `check.py` recompiles the revised source
and runs the bounded execution/model checks. `probe.json` pins all inputs and
helper/data contexts. Every generated fixture and binary is removed.

The original author source, report, runtime scripts and manifest remain frozen;
`original-preservation.log` checks their SHA256SUMS. This repair does not resolve
other translation-unit interfaces, including the separately identified 08F94
second-argument declaration of09030. All changed files are isolated under
`08009030-author-v2`; production and original evidence are untouched.
