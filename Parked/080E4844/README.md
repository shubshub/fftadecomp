# 080E4844 — sole natural candidate, NONMATCH

This unchanged candidate was frozen and compiled exactly once with canonical
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2`. Actual main return, SystemExit
code and process exit were all **1**. The report says **NOT MATCHING - bytes
differ**, and source plausibility is **IMPLAUSIBLE** due to four SUSPECT
numeric ROM pointer initializers. There is no waiver, source revision, second
compile, native campaign or match credit. This pair belongs in Parked only.

## Complete ownership and exact difference

| Body | Bytes | Reached instructions | Code / literal / alignment bytes |
| --- | ---: | ---: | --- |
| ROM [080E4844,080E4A14) | 464 | 192 | 416 / 40 / 8 |
| Complete compiled symbol | 480 | 203 | 438 / 36 / 6 |

The compiler's section and function symbol are both 480 bytes, with no
outside-symbol filler. Exactly **18/464 target-owned positions agree**;
446 present positions differ, none are absent, and 16 additional compiler
bytes lie beyond the target envelope. First difference is offset 2, E4846:
ROM `84b0` (sub sp,#16) versus compiled `4746` (mov r7,r8).

The canonical diagnostic compares a 480-byte ROM window. Its final 16 ROM
bytes, `f0b5474680b489b080460e1c151c3388`, belong to the next indexed entry
E4A14 and receive no ownership credit here. Its alignment-based 386/480 byte
and 118/189 displayed-instruction figures are neither positional identity nor
the complete reached-CFG counts above. The raw owned-range comparison is
retained separately in verification.json.

Observed differences include a saved r8 (24 saved bytes versus ROM's 20),
early consolidation of the 03000940 pointer into r8, explicit low16 mask-result
extensions, different old-child Boolean normalization, register assignments
and literal placement. Both retain 16 local outgoing bytes and the 16 direct
calls to 14 unique indexed targets. These describe the sole output, not an
impossibility claim or authorization to alter types/order/spelling for a retry.

## Recovered behavior and limits

The compatible callback is u32(void *,void *,void *), registered at E4AF4
with payload size 0x2C. Phase zero narrows selector/flags and obtains signed
coordinate outputs. Phase 0x100 creates three children, initializes countdown
12 and reloads/increments phase. Phase 0x101 decrements an unsigned halfword
without a zero guard: initial zero wraps to FFFF. Only newly zero starts the
next ordered effects, updates the halfword RAM shadow, creates the sound child
and advances phase. Phase 0x102 polls/stores children in short-circuit order;
shadow clearing requires a previously nonnull mask child becoming null.
Sound child+28 is not polled. No omitted initialization or new guard is added.

Numeric pointer tables at 08396CDC,08396CEC,08396CE4,08396D04 and fixed record
arguments are independently witnessed; no named-data mapping or table extent
is invented. The four table initializers remain canonical SUSPECT rom-address
findings. Prior ABI/data evidence is not an automatic plausibility pass, and
no post-output justification comments or other source changes were added.
The shadow uses the observed u16 accesses, not bitfields or volatile loads.

Nominal scalar types are compatible choices, not unique original typedefs.
Selector range, valid initialized state, object/storage lifetime, allocation,
scheduler descriptor copying and callee return/preservation remain assumptions.
D6134 is not granted invented null safety. Passing ordinary framed/typed-call
checks is not recursive scheduler proof or runtime-equivalence evidence.

## Retained evidence

Full immutable bundle:
`/home/user/.codex-work/ffta-ulw/080E4844-author-next/`.
It retains precompile ABI.md, preparation/initial snapshots, freeze.json,
compile-start.json, canonical.log, process-exit.txt, complete original/linked
ELF hex and section/symbol/relocation capture, comparative DISASSEMBLY.md,
verification.json and the canonical nonmatch report. Source SHA256 including
the precompile target comment:
`47ff1c2f035c3493e4b7cd96eadd39573818ca2c6c0a2e7e2024095a98ae96cb`.
Source plus nine headers fingerprint:
`2b2f80de4467af5668155fe2fcaa8c2a4302dcb449dfbd946ab016723d013022`.

The separately approved three-entry metadata-current.patch is retained for
provenance only; it changes instruction counts and legacy symbol sizes, not
this endpoint or data mappings. Root owns its shared integration. Only this
C and README are proposed Parked payload; no match report goes into shared
compiled-match inventory. All generated binaries were cleaned by the canonical
workspace; full ELF evidence is text, and no ROM copy or cache remains.
