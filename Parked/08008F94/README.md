# 08008F94 — Parked menu-row recovery

## Disposition

**Parked only.** The natural recovery compiles without diagnostics at fixed
`agbcc -mthumb-interwork -O2`, but its complete body is160B/66I rather than
the ROM's156B/67I. The unmodified approved matcher exits1 with:

    recursive or intra-function calls are unsupported

This rejection is consequential to the real size difference: the candidate
extends through09034, so its extra literal at09030 overlaps the genuine
callee entry08009030. The ROM body ends immediately before that entry. No
extent truncation, alternate address, alias or verifier bypass is used for
official credit. There is no official MATCH report or active-source claim.
The separate full typed diagnostic link and bounded tests are not official
acceptance and do not make the candidate placeable at its ROM address.

One natural form was written. Two grounded corrections precede this freeze:
agbcc rejects a C99 flexible-array member, so the unknown-length record tail
uses its GNU zero-length-array spelling; the target compiler rounds the
30-byte control view to32 bytes (`STRUCTURE_SIZE_BOUNDARY=32` in thumb.h),
so the following unknown region starts at310 rather than30E. The final
record tail is at338 as required by the ROM. Initial syntax and layout forms
and their diagnostics are retained separately. Neither correction searches
register allocation or instruction ordering. No subsequent byte-driven
iteration, flags, assembly, volatile or artificial storage was attempted.

This v2 makes one further declaration-only compatibility repair:
`func_08009030`'s second parameter is `u8 *destination`, matching the frozen
natural 09030 definition. The local destination already has type `u8 *`.
No expression, statement, call order, cast, storage, compiler flag, or other
declaration changes. In particular, the existing `u16 func_08015110(...)`
return type remains unchanged. The original source and full evidence remain
frozen in sibling `08008F94-author`; selected original artifacts are retained
here as `previous-v1-*`. Fresh fixed-option compilation proves complete
160-byte candidate identity, emits no diagnostics, and retains the same
official rejection. The complete bounded runtime suite is rerun and produces
byte-identical result evidence; this is not merely a transferred test claim.

## Complete ownership and proposals

The complete half-open body is `[08008F94,08009030)`:

| Ownership | Count |
| --- | ---: |
| Reachable Thumb code, including five BL instructions | 144B /67I |
| Trailing literals at09024,09028,0902C | 12B |
| Internal or external alignment within the owned span | 0B |
| Total | 156B |

The literals are02009188,085567F0 and000002E9. A PC-relative read at08FDE
requires the final word0902C..09030, omitted by the existing index. Fresh
Capstone CFG traversal follows both sides of the single conditional and
classifies every byte; Binary Ninja independently confirms each instruction
length. No table or interior entry occurs in the target body. The next
indexed function starts at09030 and no indexed body overlaps the correction.

`metadata-proposal.diff` changes only target end0902C→09030, size152→156,
count76→67, preserving start/mode/kind. It also proposes the grounded data
binding `g_table_085567F0` at085567F0. The source declares an unsized array
of constant pointers to constant bytes; the ROM explicitly loads a word
from `base + 4*(entry+745)` and passes it as the renderer's text argument.
This is data, not an addressed function/runtime alias. The bounded tests
observe twelve pointer words at08557394..085573C4 (indices745..756), all
pointing inside this ROM. Neither that accessed window nor the unsized
declaration claims the table's nominal allocation or general index validity.
No production mappings are edited.

## Natural contract and target layout

The global slot02009188 supplies a live state pointer. The local partial view
has display pointer+18, renderer region+24, control+2F0 and four-byte records
starting+338, with the enabled byte at record+3. The display's buffer pointer
is at+10. Control fields used by this caller and its actual clamp helpers are
byte width+15, byte divisor+17 and halfwords count+18, scroll+1A, base+1C.
Seventeen target-compiler assertions check scalar widths, these offsets,
record stride and the control's actual32-byte compiled size. The view does
not assert the nominal allocation size or the unknown renderer's layout.
The zero-length record tail is an agbcc GNU extension, not portable ISO C.

The caller interprets the low byte of the input as signed, captures the
control address, obtains a u16 position from08017B9C, reloads the global
display pointer and computes `buffer + position*32`. It clears through
08013A88 with count `width*2`, obtains a u16 record index from08017B68,
loads text pointer `table[index+745]`, and reloads the global state for its
enabled byte and renderer address. It passes flag1 exactly when enabled is
zero, passes fifth argument1, then calls08009030 with the low-byte index and
the same captured destination. Return values of the last two calls are
ignored; this recovery returns void.

For the bounded actual-helper domain, count is1..12 and divisor1..255.
Both clamp helpers form a signed16 narrowing of `signed8(input)+scroll`,
then clamp negative results to0 and positive excess to count-1. 08017B9C
executes actual08142950 signed-remainder code, then returns
`u16((index % divisor)*width*2 + base)`. This is remainder, not quotient.
Widths0..255 and u16 base/narrowing are exercised, including a wrapped
final position. Arithmetic remains within promoted32-bit ranges in these
cases. Signed8/16 conversions use the target compiler's two's-complement
behavior; they are not portable, implementation-independent conversions.

The complete execution contract requires live, aligned and sufficiently
backed state/display/control/record objects, a valid table element, and a
destination array containing the entire required range. Captured pointers
must remain alive across calls; actual rendering/overlay capacity, aliasing,
termination, retention and initialization contracts remain unresolved.
The local declarations of the two already recovered clamp functions match
their existing parameter/member types. Their different partial struct views
are target-layout evidence, not a whole-program strict-aliasing/effective-
type proof. Unsafe aliasing with globals, control or stack is excluded.

## Complete compiler evidence and exact mismatch

The original ELF contains one function and160B `.text`, alignment4, with
no external padding or extra allocated helper/data bodies. Its six original
relocations are five `R_ARM_THM_CALL` records and one `R_ARM_ABS32` table
literal. The diagnostic linker independently checks the existing unique
Thumb target entries, emits typed Thumb function definitions and a typed
object definition, rejects stubs/orphans, leaves no relocations, preserves
every non-relocated byte, and checks exact target symbol values/types.
The linked function size, `.text` size and objcopy output all agree.

| Item | ROM | Candidate |
| --- | ---: | ---: |
| Full owned bytes | 156 | 160 |
| Code bytes / instructions | 144 /67 | 142 /66 |
| Literal bytes | 12 | 16 |
| Internal alignment | 0 | 2 at09022 |
| Caller frame | 28B | 28B |

The candidate has93 equal and63 unequal positional bytes in the156-byte
common prefix, plus four extra bytes. It schedules the u16-result shift
before the display loads instead of between them. For the record flag it
combines the field offset into an extra0000033B literal instead of the
ROM's `0xCE*4` base and `ldrb +3`, shortening code by one instruction while
adding a literal and alignment. This changes subsequent instruction offsets
and BL encodings. `build.json` records every mismatching offset;
`compiled.txt` retains both complete spans and decoded candidate code.

Full target-body SHA256:
`df5378ff4e62c240b08261ad55bc34b6edecddf4340ca6e531e7a5d5175ec0dc`.
Full diagnostic candidate SHA256:
`a8146ad4192a5dd3afe7bfcd8e2f85b0f5f001d7f8e9c03941a8ae9858eed735`.
Plausibility has no findings. Both the honest rejection text and that text
prefixed by a bare forged MATCH claim fail strict report replay. These are
two no-credit controls, not a claim of comprehensive forged-report testing.

## Bounded execution evidence and limits

The24 pairs/48 Unicorn executions compare an independent scalar/call oracle
with both the actual caller ROM and full diagnostic candidate. Coverage is
67/67 ROM and66/66 candidate caller instructions, not every path or input.
The actual ROM bodies08017B68,08017B9C,08142950 and08013A88 execute, with
26,37,92 and16 visited instructions respectively. The remainder zero-divisor
path is excluded by a checked domain guard; no overflow/trap behavior is
claimed. Dependency spans/hashes and the twelve-word table window are in
`runtime-results.json`.

Three explicit models are used:

- 08141868, the BIOS veneer called by actual08013A88, is replaced entirely.
  Its arguments and initialized stack zero-word are checked, then the model
  writes `width*64` zero bytes. No SVC or actual BIOS instruction executes;
  zero count is a model-defined empty fill, not proved BIOS behavior.
- Entire08015110 rendering is replaced by checked arguments, a two-byte
  marker write and caller-saved register/flag clobbers. Its actual text
  parsing, buffer consumption and retention behavior are not exercised.
- Entire08009030 overlay is replaced by checked arguments, a second marker
  write and ABI clobbers. It verifies render-before-overlay order. Actual
  overlay code cannot execute in place in this candidate because the extra
  candidate literal overwrites its entry; this is a deliberate model limit,
  not a fix for the extent collision.

Cases include signed-byte boundaries and upper-bit contamination, all twelve
record indices, clamp-low/in-range/high branches, signed16 sum wrapping,
nonzero divisor extremes, widths0/255, u16 position wrapping and enabled
values0/1/128/255. Full EWRAM/IWRAM effects, ordered call arguments including
the fifth stack word, ordered model writes, paired actual stack writes,
initialized consumed RAM reads, current-frame stack reads/writes, r4-r11,
balanced SP and Thumb/ARM return mode are checked. Both word-aligned SP
residues are covered. Nested actual frames stay within44 bytes; caller frame
is28. Unspecified void-return r0 is not compared as a return value.

Nine executed negative controls catch unsigned selector, destination stride,
clear-count factor, enabled predicate, fifth argument, table-index bias,
an actual second-clamp field mutation and insufficient logical destination
capacity in both ROM/candidate runs. Three separate oracle guards reject
zero divisor, nonpositive count and insufficient buffer extent. These guards
are test preconditions, not claims that ROM rejects those inputs. No
universal BIOS, whole-game, future callback, helper retention, arbitrary
pointer replacement or all-input C equivalence is claimed.

## Reproduction

    env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
      PATH=/home/user/armtc/root/usr/bin:$PATH \
      python3 /home/user/.codex-work/ffta-ulw/08008F94-author-v2/check.py

The checker uses immutable game-next-73c22d0 and approved
kit-software-double-candidate-v3, copies all nine headers into an owned
disk-backed fixture, applies proposals only there and sets TMPDIR there.
It removes generated compiler fixtures on exit and verifies input pins.
For independent review, copy the scripts/source to an owned sibling scratch
directory before running, rather than mutating this frozen evidence.
Only text artifacts remain. Parent owns integration and lease release.
