# 080088D8 — Parked natural recovery

**Not matching; no matched-function credit.** The approved ordinary typed-data
and direct-call verifier accepts this candidate's structure and source
plausibility, but the complete function still differs in 11 byte positions.
This is a byte mismatch, not a verifier-blocked recovery.

## Forms and complete ELF evidence

The first natural form used the literal ROM table address. It is preserved,
with its original compiler/checker/log evidence, in `raw-cast-form/`. Its
source SHA-256 is
`8a58994ea6c1cd4eaf88d7d1f06de7118d4253edc4b740674b9c53302f25be2b`.
The source checker flagged that actual ROM-address cast as suspect.

One parent-authorized semantic data-model correction replaces the cast with
`extern const OptionDefinition g_table_0836D4D4[]` and a private, evidence-backed
data-symbol mapping. The declaration is unsized, following existing project
table conventions. No statements, loop increments, flags, or storage were
reordered to influence code generation. The corrected form emits exactly the
same linked bytes as the first form and passes source plausibility. It is the
retained source, SHA-256
`da7ca067bf45e5f9ea7a4035ae042bc9e0f342f3a904add3d7c091a169fcdc71`.

The full ROM span `[080088D8,08008938)` is 96 bytes: 41 instructions / 86 code
bytes, the zero alignment halfword at 0800890E, and two internal literal words
at 08008910 and 08008914. Those literals are 02009188 and 0836D4D4. There is no
external gap before indexed entry 08008938. Capstone CFG traversal and Binary
Ninja instruction lengths agree, and code/pool/alignment ownership is disjoint
and complete. `metadata-proposal.diff` changes only the count from 48 to 41 in
both immutable input maps; endpoints and their existing kind fields remain.

The original ELF owns one 96-byte Thumb function and a four-byte-aligned
96-byte `.text`, with no external assembler padding. Its original relocations
are THM_CALL at offsets 36 and 70 to `func_080094BC`, and ABS32 at offset 60 to
the table object. The approved typed link binds the actual internal literal
and both calls, leaves all nonrelocated bytes unchanged, and produces no
unresolved relocations, veneers, extra functions, or allocated data sections.
Both ROM and candidate save 20 stack bytes and allocate no local frame.

| Complete body | SHA-256 |
| --- | --- |
| ROM | `76b972312e971596c8477862ba6e87ea5e32462767af6f6c3224f126a03463fb` |
| Candidate, both forms | `eda50979e828fa05521ef768bf18c04db982677f03c0a05630d00d9b7e278e41` |

Exactly 85 of 96 equal-position bytes agree. All 11 differing bytes are listed
in `results.json`: initialization scheduling at 080088E4/E5/E7/E8/E9, and the
six bytes at 08008928..0800892D representing three reordered increments. The
ROM loads the table after initializing the loop index/zero register and
increments table, index, entry; the candidate loads earlier and increments
index, entry, table. No byte-steering iteration was attempted. The official
report's 92/96 figure is its sequence-aligned comparison, not equal-position
equality; neither figure is a MATCH.

`official.log` is the requested fresh `--mode thumb --no-write` run, exit 1.
`not-match-report.md` is a separately generated honest private report using
`elf-symbol-thumb-data-v1`. Strict report validation rejects both that report
and a forged MATCH verdict. No successful MATCH report or active source is
being supplied.

## Recovered contract and observed table

This no-argument function reads the pointer at 02009188 once and fills ten
four-byte entries at pointed-state offset 0x338. Each entry has bytes at offsets
0=value, 1=count, 2=width, 3=enabled. These names are descriptive recovery names,
not independently established gameplay terminology. The partial state view
ends at 0x360; that is not the full allocation size of the actual state object.

The definition pointer advances by 20 bytes for each of the ten iterations.
Only its halfwords at offsets 0 and 2 are read, each narrowed to a byte in the
output. Their actual pairs are `(3,16), (2,16), (3,16), (2,16), (2,16), (2,16),
(2,16), (2,16), (6,13), (0,0)`. The observed ten-stride ROM window is
`[0836D4D4,0836D59C)`. Actual reads occupy 40 bytes in twenty separate halfword
accesses, the last ending at 0836D58C. Neither the unsized declaration nor the
200-byte inspected window asserts a nominal table allocation length. The
unknown sixteen bytes per stride remain uninterpreted by this caller.

For entries 0..8, the function calls `func_080094BC((u8)index,1)`, stores its
low return byte as value, and writes enabled=1. Entry 9 instead stores value=0
and sets enabled when the helper's low return byte is zero. The final loop
increment forms the one-past entry/definition pointers without dereferencing
them. The caller makes exactly ten calls in order, not just two dynamic calls
because it has two static BL sites.

The typed contract requires an initialized valid pointer slot; a live writable
state object covering its ten-entry output; a live definition table covering
the ten accessed records; and a valid nonaliasing stack. Actual helper behavior
additionally requires initialized readable state bytes at offset 0x1BCC..0x1BCF,
beyond the caller's partial struct view. These settings, outputs, pointer slot,
ROM table, and active stack do not overlap in the tests or claimed domain.
No aliasing, concurrent mutation, MMIO, null-pointer, or undersized-object
behavior is claimed. The helper's declared byte return is supported here by
the actual read-mode return range, not by treating arbitrary machine words as
proof of a C prototype.

## Actual helper evidence and separate models

With second argument 1 and indices 0..9, the real helper dispatches through
the ten-entry ROM jump table at 080094F0. It reads the same global state pointer
and the four settings bytes at +0x1BCC. Indices 0..8 select bits or bitfields
from its first three bytes; index 9 calls actual ROM comparator 080096B0 on
all four bytes and the four-byte ROM window at 0851BA4E (`02000000`). The
comparator returns zero for equality, and the helper converts equality to 1.
Consequently the caller's last enabled byte is 0 for equal settings and 1 for
different settings. No helper writes state in this exercised read mode.

`dependencies.txt` records the bounded read-mode instruction ranges, dispatch
targets, literals, comparator, and data windows; `results.json` pins them.
This is not classification or proof of the helper's separate mode-zero mutation
path, arbitrary indices, or its other callees.

Twelve ROM/candidate pairs (24 executions) execute the actual helpers, with no
return substitutions. Settings cases cover equality, first/second/third/fourth
comparison-byte differences, zero and set bitfields. Every caller instruction
is exercised, 41/41 for each body; the bounded allowed helper subset covers
89/93 instructions, not the whole helper or every path. Maximum observed stack
depth is 44 bytes: caller 20, read helper 16, comparator 8.

Two additional pairs (four executions) are explicitly synthetic caller tests:
the entire helper call is replaced with a return-word model that clobbers
caller-saved registers and flags, and the table halfwords receive high-byte
patterns. They check low-byte copying and zero predicates, including return
words 0x12340000 and 0xFEDCBA80. Those model returns are not actual helper
behavior and do not expand the typed helper contract. The synthetic table is
not represented as the actual ROM table. Original ROM and source remain intact.

Checks compare all forty ordered byte writes, all ten argument/return records,
the twenty exact table-read addresses/widths, the entire 64 KiB mapped EWRAM
arena, r4-r11 and SP preservation, Thumb/ARM returns, two word-aligned SP
positions, and unchanged IWRAM outside the 44-byte stack envelope. Read hooks
reject unapproved state/global/table accesses. Seven controls detect caller
predicate/stride/loop-bound mutations, actual helper/comparator mutations, and
one-byte-short output capacity for both bodies. Sixteen fresh agbcc assertions
validate the scalar sizes, partial layouts, stride and byte conversion.
These finite emulator checks are not universal helper, C-language, timing,
hardware, memory-safety or termination proofs.

## Reproduction and handoff

`check.py` uses immutable game-next-370e2e6 and approved
kit-inert-spin-candidate-v2, copying all nine headers into an owned fixture.
Only that fixture receives the count correction and one table mapping.
The input maps, source and toolkit are pinned; `results.json` records all
source/header/compiler/data/ROM digests and proposed mapping digests.
The ROM SHA-1 is `4ac05441f4de70a4ec3dd932116346c61b8783d9`.

Run copies of the final source and checker from an owned sibling review
directory, not inside this frozen author directory:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=<owned-disk-directory> \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

The checker runs the requested official command with `--root <fixture>
--mode thumb --no-write 0x080088D8`, then creates the private nonmatch report.
All generated compiler and fixture directories are self-cleaned. The
raw-cast-form directory is intentional text-only provenance, not a runnable
standalone fixture. No production, Git, reservation or shared inputs changed.
Root owns independent review, any Parked/data/map integration, and release.
