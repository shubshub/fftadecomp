# 08008954 — Parked natural state-dispatch recovery

## Disposition

Not a match, not active-source credit. One natural switch-based form was
written at fixed `agbcc -mthumb-interwork -O2`. Its complete diagnostic-linked
body is 940 bytes / 390 instructions, versus the ROM's 1018 bytes / 414
instructions. No extent was shortened to claim equality. No statement order,
flags, register allocation, artificial storage, inline assembly, volatile,
or addressed-runtime alias was used to close this gap.

`first-form.c.txt` preserves the original form. The first later correction
changes `func_08013404`'s declaration to the existing matched implementation's
`u32, u32` parameters and explicitly converts the two callback addresses to
those target-sized words. It fixes a cross-translation-unit scalar/function-
pointer parameter mismatch; it does not erase the function relocations.
The complete candidate bytes are identical before and after that correction.
Revision v2 additionally corrected only `memcpy`'s length parameter from
`unsigned int` to `unsigned long`, the compiler's canonical size type.
The independent v1 review found the built-in-prototype warning; v1 remains
unchanged in the sibling `08008954-author` directory. Local gcc/c-decl.c
defaults SIZE_TYPE to `long unsigned int` and uses that type to build the
`memcpy` prototype; libc/include/string.h declares the size_t parameter.
The corrected whole-source compile emits no warnings or other diagnostics.
The complete candidate bytes remain identical to v1.

Revision v3 changed only the two declarations relevant to callback registration:
`func_08008E78` now has its independently recovered `u8(void)` type, and
`func_080098F4` accepts `u8 (*)(void)`, consistent with the approved Parked
08008D50 declaration. No callback cast, statement, or emitted instruction
changes. The frozen v1 and v2 directories remain untouched.

This v4 changes exactly the 09140 declaration to `u8 func_08009140(void)`
and its state4 invocation to `selection = func_08009140();`. The independently
recovered 09140 definition takes no arguments. Its actual ROM overwrites
incoming r0 at 0800914A before reading it; state is loaded from 02009188.
No ignored parameter or cast is manufactured. No other source statement,
type, ordering, or compiler option changes. The frozen v3 directory and
manifest remain unchanged; its source, full compile listing/build, and
runtime results are also retained here with `previous-v3-` names.

Fresh compilation of v3 under the same immutable game500/toolkit-v3 inputs
reproduces its complete original 940B/391I candidate hash. The v4 source
legitimately removes the `ldr r0, [r6]` at old candidate 08008A00 immediately
before the 09140 call. The call and subsequent block addresses move; branch,
call, table, and literal encodings are recalculated. Extra internal alignment
keeps the full body at 940 bytes, now 390 instructions. Against v3, 672 bytes
at the same offsets remain equal and 268 differ. This is a semantic ABI repair,
not a successful match or a byte-identical declaration-only change.

## Complete raw-ROM ownership

The owned half-open span is `[0x08008954,0x08008D4E)`. Fresh Capstone CFG
traversal follows both conditional successors and the actual eleven local
dispatch words. Binary Ninja independently checks every reached instruction's
length. `CLASSIFIED.txt` records the complete result:

| Category | Bytes |
| --- | ---: |
| 414 reachable Thumb instructions, including 30 BL instructions | 888 |
| 19 PC-relative literal words | 76 |
| Eleven local switch destinations at 08008978..080089A4 | 44 |
| Five internal two-byte zero alignment gaps | 10 |
| Total owned body | 1018 |

Internal alignment starts at 08008AAA, 08008AEE, 08008B9A, 08008BEE and
08008CAA. The zero halfword 08008D4E..08008D50 is external and excluded;
08008D50 is the next indexed prologue. No indexed entry overlaps this body.
The index's 509 count counted words as instructions; the count-only proposal
is 509 to 414, with both endpoints, mode and kind unchanged.

The dispatch guard accepts state values 0..10; larger unsigned halfwords
return zero. All table entries are even addresses of reached blocks within
this function, not separate entry claims.

## Natural semantic contract

The pointer slot at 02009188 supplies a live state object. The partial view
through offset 1BCF is a minimum storage requirement for the recovered
accesses, not a claim about the nominal game allocation. Its grounded fields
are state/depth at +4/+6, eight halfword continuation slots in +8..+17,
two argument words at +18/+1C, byte handle/command at +20/+22, byte control
value at +2BC, opaque control at +2C4, panels at +310/+324, opaque dialog
at +11C8, and four settings bytes at +1BCC. Panel halfwords at +A/+E and
the flag byte at +10 are read directly. Eighteen target-compiler assertions
check these offsets and view sizes.

The eight history slots are the bounded view ending before the separately
observed argument at +18; their existence is not a proof that all game
states obey its capacity. A push requires depth < 8, a single pop requires
1..8, and the zero-result branch in state8 requires at least two entries.
Multiple pushes require enough remaining capacity. Machine wraparound and
out-of-object history accesses are outside the C contract, not repaired.

| State | Caller behavior |
| --- | --- |
| 0 | Initialize through 08008D50; push4, select2 |
| 1 | Return1, without helper calls |
| 2 | Poll the byte handle; if complete, invoke 08008E94 and pop |
| 3 | Poll the handle; if complete, clear depth and select1 |
| 4 | Query a low-byte selection, update control, then choose a continuation |
| 5 | Update the menu and control, then pop |
| 6 | Apply persistent two-bit mode; update control; register callback; select3 |
| 7 | Create dialog with ten arguments, store callbacks, set panel/menu flags, update control, pop |
| 8 | Poll a low-halfword result; interpret subsequent low byte as signed; reset/pop twice/pop-and-clear as appropriate; update control |
| 9 | Copy four ROM default bytes into state then persistent settings; apply mode; update panel/control; clear depth and select6 |
| 10 | Copy four state settings into persistent storage; apply mode; update control; clear depth and select6 |

In state4, selection0 leaves the continuation alone; 2 selects6; 3 sets
command1D and pushes9,4,8 before selecting7; 4 sets command1E and pushes10,6,8
before selecting7; other byte values push4 and select5. State8 negative
results clear depth/select4; positive results pop then clear depth; zero
results pop twice. The panel comparison is the full promoted sum of two
unsigned halfwords, not a wrapped 16-bit sum.

The selection call has no C arguments. Its bounded whole-call model consumes
none and does not require an ignored state pointer in r0. Recorded actual
caller-ROM entries carry 02010000, while the repaired candidate carries
08008A00; these are observations, not argument requirements. Removing the
obsolete argument also removes its otherwise unused pointer-slot reload.
The contract excludes volatile/asynchronously changing pointer-slot accesses;
the actual 09140 prefix reloads the slot itself. This resolves this one direct
call's declaration consistency, not all remaining cross-translation-unit or
callback dispatcher typing questions.

Calls may change the global state pointer. The recovery reloads it where
required while retaining the explicitly captured panel/menu objects in
state7 and the control-value address in state6. Such retained objects must
remain alive. The concrete tests cover selected model-driven replacements,
not arbitrary frees, reentrant changes, asynchronous mutation or aliasing.

## Typed bindings and boundary proposals

`g_state_02000000` and `g_state_020020D0` already have mapped bindings.
The only new data proposal is unsized `const u8 g_table_0851BA4E[]` at
0851BA4E. Exactly four bytes, `02 00 00 00`, are observed by this caller;
neither the declaration nor this evidence asserts a nominal allocation size.

The function-address literals 080096E1 and 08009729 independently identify
previously unindexed Thumb leaf entries. Bounded CFGs establish complete
non-overlapping bodies 080096E0..08009728 (72B,34I,one trailing literal)
and 08009728..0800975C (52B,21I,two trailing literals and two internal
alignment bytes). Their pointer uses, code, pools and next boundary are
recorded in `dependency-classified.txt`; the two-map insertion proposal is
separate from the target count correction. No C is authored for these leaves.
08008E78 is already indexed. Merely storing these function addresses does
not establish their future invocation/lifetime contracts.

`func_080098F4`'s actual ROM implementation stores a callback word and context
in the first free one of four records; the bounded dispatcher at 080098C4
passes that context in r0 and tests the low16 return through a real call
thunk. That machine-level observation does not require a C callback type
`u16 (*)(u32)`. The current declaration is `u8 (*)(void)`, consistent with
the independently recovered `u8 func_08008E78(void)` definition and the
approved Parked 08008D50 registration declaration. 08008E78 ignores incoming
r0 and explicitly zero-extends its own helper's byte return. Future recovery
of the dispatcher and registration bodies must resolve context/return typing;
whole-program C compatibility is not established by these bounded ABI facts.
The registered callback is not executed by these tests. The other two
callback addresses pass as words to the existing `func_08013404(u32,u32)`
API. The explicit pointer-to-word conversion is target-defined: agbcc emits
the original function-address ABS32 relocations, and the diagnostic link
verifies their odd Thumb values. This is not a portable ISO C claim.

## Official verifier versus diagnostic build

The unmodified approved toolkit rejects the source with exit1:

    call target must be an undefined addressed function

The cause is the three original `R_ARM_THM_CALL memcpy` relocations.
Natural C retains the canonical `memcpy` spelling. No addressed alias is
substituted to pass the ordinary addressed-function binder. Independently,
the same toolkit's switch-binding branch rejects nonempty function-address
bindings, so this local-switch / callback-literal composition also lacks
an approved profile. These are verifier limitations, not explanations that
erase the genuine compiler mismatch. Plausibility is checked separately and
has no findings; the official command stops before producing a report.

For diagnostics only, a separate typed linker binds `memcpy` to 081443FC.
Its complete 98-byte ROM body has the standard forward-copy structure,
including the byte path exercised by all three four-byte calls; the local
agbcc libc/string/memcpy.c supports that identification. This is not an
official runtime-identity proof. All other external bindings are indexed or
independently proposed function entries or mapped objects. Local section
relocations resolve solely to the emitted switch table/blocks.

Original and linked ELF checks establish one function, no extra allocated
data or helper bodies, 49 relocations (29 THM_CALL and20 ABS32), no remaining
linked relocations, no unexpected stubs, no change outside original
relocation words, and exact typed target/addend resolution. Complete .text
and function size are both940, alignment4, no external candidate padding.
The candidate owns838 code bytes,52 literal bytes,44 table bytes and6
internal alignment bytes. The original frame is40 bytes (16 saved+24
outgoing); the candidate frame is44 (20 saved+24 outgoing).

The 940-byte common prefix contains92 equal positional bytes and848
different bytes, with78 additional target bytes absent. `build.json` lists
all differing common-prefix offsets; `compiled.txt` retains both complete
hex spans and the candidate code classification. The first byte already
differs: ROM pushes r4-r6/lr; compiled code pushes r4-r7/lr. No official
MATCH report exists, and a bare forged MATCH claim fails strict replay.

## Bounded execution evidence

`runtime.py` compares49 independently parameterized oracle cases against
both actual caller ROM and the complete diagnostic-linked candidate:
98 executions. All414 ROM and390 candidate caller instructions are visited.
This is instruction coverage, not exhaustive path/input coverage.

Eight helpers execute their actual ROM instructions: 080098F4, 08009920,
080099A4, 0801339C, 08013404, 08013428, 08017D18 and081443FC. The17D18
cases deliberately use a null owner and never enter its nested-helper
branch; memcpy executes the actual four-byte byte-copy path, not a model.
Helper spans and hashes are in `runtime-results.json`.

Nine other helpers are explicit ABI models: 08008D50,08008E94,08009140,
0801174C,08011860,08013380,08016234,08017508 and08017E28. Their deterministic
test writes, return values and optional state-pointer replacements are
fixture behavior, not claims about the actual game implementations. They
clobber r1-r3/r12 and arithmetic flags, preserve callee-saved registers/SP,
and do not retain stack arguments. The ten outgoing arguments are captured
before the dialog model returns. No BIOS, callbacks, hardware or unmodeled
helper closure is silently executed.

`prefix.py` separately executes the actual 09140 ROM entry up to, but not
including, its first BL at 08009178. The explicit domain is a valid initialized
02009188 pointer slot and input halfwords at 03000002/03000004, with pressed
mask 0x0002 set. Twenty executions use the actual r0 values observed in the ten
state4 cases for both caller bodies. Six additional executions use zero,
FFFFFFFF, DEADBEEF, STATE, OTHER, and the pointer-slot address, while the slot
points to the other live state and pressed also contains high bits. All 26
execute the same 28 prefix instructions and reach comparison arguments
`(current + 0x1bcc, 0x02002fc0, 4)`, independent of incoming r0. Both
word-aligned SP residues, the exact 32-byte register-save image, initialized
consumed reads, unchanged non-stack memory, and the stop boundary are checked.
These prefix executions do not run the comparison, the rest of 09140, its
return, BIOS, or any downstream helper. They do not replace the nine explicit
whole-call models in the 98 full caller executions. Two prefix mutants
(removing the incoming-r0 overwrite and changing the comparison byte count)
are caught; a separate guard rejects a missing cancel bit. That guard limits
the fixture domain and does not assert the real function rejects other input.

Cases include every state and out-of-range defaults; every nested selector
arm; byte/halfword narrowing with upper-bit contamination; signed-byte
boundaries; panel sums63,64 and131070; all four persistent modes; four-slot
callback registration including full capacity; and five global-pointer
replacement scenarios with both objects alive. Memory is initialized in
explicit allowed RAM regions. Every consumed non-ROM read must have an
initialized byte; stack reads must additionally be within the current
frame and previously written. Actual push stores are accounted as the
instruction extends its frame. The entire EWRAM, non-frame IWRAM, ordered
non-stack writes, helper arguments/order, r4-r11, SP, return value and
Thumb/ARM interworking return are checked. Both word-aligned SP residues
are exercised. Different dead frame contents are not claimed equal.

Eight executed semantic mutants are caught: continuation, command,
outgoing width, panel threshold, signed result, copy size, completion return,
and an actual memcpy destination-stride fault. Two additional oracle-domain
guards reject insufficient push capacity and two-pop underflow; they are
precondition tests, not claims that the ROM rejects invalid histories.

The contract excludes null/invalid state objects, bad history capacities,
handle indices outside the four records for actual polling, overlapping
memcpy ranges, owner-nonnull17D18 behavior, unsafe aliasing with globals or
stack, insufficient object storage, uninitialized consumed fields and
nonreturning/misbehaving models. No all-input, whole-game, eventual callback
or helper-retention equivalence is claimed.

## Reproduction and retained artifacts

    env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
      PATH=/home/user/armtc/root/usr/bin:$PATH \
      python3 /home/user/.codex-work/ffta-ulw/08008954-author-v4/check.py

The checker uses immutable game-next-73c22d0 (game500) and approved
kit-software-double-candidate-v3, copies all nine shared/private headers into an
owned disk-backed fixture, sets TMPDIR there for the official command, and
removes that entire generated fixture on exit. Input hashes are verified
unchanged. `input-pins.json`, `check.log`, `official.log`, `original-object.txt`,
`build.json`, `runtime-results.json` and `SHA256SUMS` preserve the evidence.
Only text artifacts remain. No production source/report, maps, headers,
toolkit files, status, Git or reservations were modified by this lane.
