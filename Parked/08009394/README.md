# 08009394 — Parked panel/control update recovery

## Disposition

**Parked only.** One natural source form was compiled with fixed
`agbcc -mthumb-interwork -O2`; it remains unchanged. No statement reordering,
type/flag/register search, invented extra argument, inline assembly,
volatile, artificial storage, or shortened target extent is used.

The complete ROM body is126B/53I. The complete candidate is118B/50I, with
32 equal and86 different positional bytes in the common prefix and eight
target bytes absent. The candidate .text is120 bytes, including external
`c046` alignment after the118-byte function symbol. Neither those alignment
bytes nor a truncated ROM slice are counted as function equality.

The approved official no-write command exits1 before report generation:

    compiled symbol is shorter than the indexed span: 118 < 126

This is a genuine extent mismatch, not an unsupported instruction/profile
claim. Separate typed linking and the ordinary direct-call CFG/ABI verifier
pass for the complete candidate. They do not override the official extent
failure, establish a match, or produce a creditable report. Plausibility has
no findings and the compiler emits no diagnostics.

## Complete ownership

The half-open target span is `[08009394,08009412)`:

| Kind | Bytes |
| --- | ---: |
| 53 reachable Thumb instructions, including seven BLs | 120 |
| Internal literal 02009188 at093D4..093D8 | 4 |
| Internal zero alignment at093D2..093D4 | 2 |
| Total | 126 |

The zero halfword09412..09414 is external alignment and excluded;09414
is the next indexed prologue. Fresh Capstone CFG traversal follows both
branches, excludes data from code, and owns every byte exactly once.
Binary Ninja independently checks all reached instruction lengths. There
is no jump table, interior entry evidence, or overlap with another indexed
body. `CLASSIFIED.txt` records the classification. The separate two-map
proposal changes only the target instruction count63→53; start, end,
byte size, mode and kind stay unchanged. No production map is edited.

## Natural contract and typing

The three input parameters are bytes: step, selection, and redraw. The
function loads the global pointer at02009188 once and captures panel+310,
menu+324, and control+2F0 within that state. These captures remain in use
even if a called helper replaces the global pointer. Objects must stay
alive and valid across those calls.

The first call to08017FBC receives menu and step; its actual ROM body is
just `bx lr`. This caller supplies the proposed parameter roles, but the
empty machine body alone cannot uniquely establish a C signature. With
redraw zero, actual08017FB0 stores selection at panel+11 and selection<<4
at panel+E. With redraw nonzero, the caller forwards the signed low byte
of selection to08008F94, then passes the captured control and step to
08017884. It next invokes08017AF4 with the current panel byte and mode11,
reloads panel+11 as signed for08017B68, narrows that helper's u16 result
to a byte, and calls08009414. The caller's own return type is void.

Declarations for08017FB0,08017884,08017AF4 and08017B68 are grounded in
the immutable matched definitions; their source hashes are pinned.
Their local record views reproduce the defining field names/types and
offsets. Twelve target-compiler assertions check view sizes, control/panel/
menu offsets, selection and extent fields, and clamp fields. The outer
state/control views describe the observed accesses, not a nominal game
allocation or a portable whole-program effective-type/aliasing proof.

Two legitimate compatibility details remain visible in the mismatch:

- The existing08017884 definition is `void(void *,u32)`. The ROM caller
  sets r2=1 immediately before it, but the helper does not consume that
  incoming value. No third C parameter is manufactured. Actual wrapper
  execution covers both branches, with its nested calls explicitly modeled.
  Recorded r2 is1 for the ROM caller and the prior model's caller-saved
  clobber value for the candidate; neither is a declared argument.
- The existing08017AF4 second parameter is u8. The natural call therefore
  emits an unsigned byte load, whereas the target caller sign-extends the
  same stored byte before the real callee narrows it back to u8. Typed
  call comparisons normalize that byte and retain the differing raw
  register values separately. They do not falsely claim whole-register
  argument equality. The subsequent08017B68 u32 argument is explicitly
  converted from signed8 and is checked as that full forwarded value.

The other differences include address-arithmetic register choices, one
fewer address-setup instruction, call/branch displacements and literal
placement. The retained first natural source is not altered to restore
the unused r2 store, redundant signed load, or target instruction count.

## Complete ELF and provenance

The original object has one function and seven undefined addressed
`R_ARM_THM_CALL` relocations. Typed linking binds only unique indexed Thumb
entries, checks their odd symbol values, and leaves no unresolved
relocations, extra allocated code/data, or veneers. Non-relocated bytes
remain unchanged. The original/linked complete function size is118 bytes;
alignment is4 and complete .text is120 bytes. Candidate ownership is114
code bytes and four literal bytes, without internal alignment.

`build.json` records every common-prefix differing byte and all original
relocations. `compiled.txt` retains both full hex bodies and reachable
candidate disassembly. The complete target SHA256 is
`dd05564191773d4c70294fe1beb7d2676a068c8673e1b49188c055418ab82b7c`;
the full candidate SHA256 is
`ed678e8fe4f74828ef50639c713de815b2b19fe58860eadcfa3385afd084ac64`.
There is no official MATCH report. Strict replay rejects both the actual
failure log and a bare forged MATCH prefix; this is a bounded no-credit
control, not a general report-forgery completeness claim.

## Bounded runtime evidence

Sixteen paired cases execute the actual caller ROM and full candidate:
32 positive executions. They cover all53 target and50 candidate caller
instructions. The following actual ROM helpers also reach every instruction
in their bounded bodies:08017FBC (1),08017FB0 (6),08017884 (14),08017AF4
(19), and08017B68 (26). `dependency-classified.txt` and runtime-results pin
the raw helper spans and hashes. These are instruction-coverage results,
not exhaustive path/input proofs.

Five deeper functions are explicit whole-call models:08008F94 redraw,
08009414 final update,0801784C step result,08017734 successful step apply,
and0801799C flag-controlled update. Model return values, marker writes,
selection/scroll changes and global-pointer replacements are fixture behavior,
not recovered helper semantics. In particular, no Parked08008F94 compiled
body, actual09414 body, renderer, BIOS or hardware implementation executes.
Models clobber r1-r3/r12/NZCV, preserve callee-saved registers/SP, terminate,
and retain no pointers. Wrapper17884's low16 signed result handling is real;
both nested-call branches execute. Wrapper17AF4's flags guard and byte/sign
conversions are real; its nested update is modeled.

Cases exercise both redraw branches; all input byte conversions with upper
register bits present; selection0,1,127,128,255; positive/negative/wrapping
signed16 clamp inputs; low-byte final results above127; count1 and larger
positive counts; negative/zero/positive step results with contaminated upper
halves; both flags branches; and model-driven selection/scroll changes
between the caller's two reads. Two live state objects exercise global
pointer replacements while the caller retains its original captures.

The oracle checks complete EWRAM, IWRAM outside current/dead stack space,
ordered non-stack writes, typed call sequence/arguments, initialized consumed
reads, current stack allocation, exact caller save image, r4-r11, SP, and
Thumb/ARM interworking return. Both word-aligned SP residues are used.
The caller frame is24 bytes, with actual wrapper nesting accounted separately.
Return-register contents are not compared as a C value because this caller
returns void. Raw argument registers and stack traces remain in the evidence.

Nine executed controls catch an altered branch, setter argument, redraw
signed conversion, mode argument, forwarded clamp u32 conversion, final
narrowing shift, actual setter shift, and uninitialized panel selection in
both caller bodies. The forwarded-u32 control detects an argument-contract
difference even though the current clamp subsequently uses only its low byte;
it is not falsely presented as a changed clamp result. A separate count-domain
guard rejects zero before execution. An initial attempted negative changed
only sign extension before a u8 consumer and was correctly not detected as a
behavior difference; the retained test changes the actual shift amount instead.

The bounded domain requires a positive signed16 count (1..32767), valid
aligned initialized state/global storage, sufficient backing for every
accessed view, and live non-overlapping objects not aliasing the stack.
Signed-byte and signed-halfword narrowing use the target compiler's
two's-complement behavior, not portable ISO C guarantees. Arbitrary helper
retention, aliasing, freeing, asynchronous changes, nontermination and full
game behavior remain unproved. Invalid count cases are excluded, not claimed
to be rejected by the ROM. No all-input equivalence is claimed.

## Reproduction

    env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
      PATH=/home/user/armtc/root/usr/bin:$PATH \
      python3 /home/user/.codex-work/ffta-ulw/08009394-author/check.py

The checker uses immutable game-next-e299a92 (game502), approved
kit-software-double-candidate-v3, all nine shared/private headers, and the
pinned Downloads ROM. It creates only a disk-backed owned fixture, sets
TMPDIR there, runs the official command with `--mode thumb --no-write`,
and cleans generated binaries on exit. Input pins are rechecked. The initial
check log is retained: that harness initially expected a report even after
the honest short-extent rejection. The checker expectation was corrected;
the source never changed. Only text evidence remains. Parent owns independent
review, metadata integration, publication and lease release.
