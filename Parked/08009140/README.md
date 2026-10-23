# 08009140 — Parked input/selection handler

## Disposition

**Parked only.** The first natural C form is preserved separately. The final
source changes only08009030's destination parameter declaration from void*
to u8*, agreeing with its independently frozen definition; the local
destination was already u8*. No statement or expression changes. The full
compiled bytes and runtime results are identical before and after this
cross-translation-unit type correction. Compilation is warning-free and
plausible at fixed `agbcc -mthumb-interwork -O2`. Official verification
supports its ordinary direct-call profile and complete316-byte extent, but
returns exit1, `NOT MATCHING - bytes differ`. This is a genuine compiler-byte
mismatch, not a missing verifier capability. No source-order, register,
flag, alias, volatile, assembly or artificial-storage search was performed.

The actual316-byte body contains138 instructions; the candidate contains140.
There are251 equal positional bytes and65 different bytes, no missing or
extra bytes. The tool's separately aligned instruction-diff score is
125/138 instructions and294/316 bytes; that score is not raw positional byte
equality. `build.json` lists all65 differing offsets. No MATCH credit is
claimed and the official nonmatching report is retained honestly.

## Complete ROM ownership

The full half-open span `[08009140,0800927C)` contains300 code bytes/138
instructions, including twelve BLs, and four internal literal words at
0918C..0919C. Those words are02009188,03000000,00001BCC and02002FC0.
The literals are skipped by branches; they are not code or independent
entries. There is no internal/external alignment, local switch table or
unowned byte. 0800927C begins the next indexed function.

Fresh Capstone CFG traversal follows both conditional successors, records
the twelve calls and four PC-relative words, and accounts for every byte.
Binary Ninja independently agrees with every reached instruction length.
No indexed body overlaps this one. `metadata-proposal.diff` changes only
the two maps' instruction count158→138; start/end/size/mode/kind remain
unchanged. No new data or function binding is needed and no production map
is changed.

## Natural contract

The global slot02009188 supplies a live state. The input record at03000000
has halfword pressed bits+2 and repeated input+4. The handler captures the
panel at state+310 and control at+2F0 before branching. Its partial state
view also names display pointer+18, four-byte entries at+338, and the four
settings bytes at+1BCC. Display buffer pointer is+10. Panel selection is
signed byte+11. Entry bytes are current+0, count+1, unknown+2, enabled+3.
The ten-entry view is the minimum covering the explicit access to entry9,
not a proof of nominal game allocation or validity of larger indices.

Fifteen target-compiler assertions check these offsets and relevant sizes,
including32-byte control and20-byte panel rounding. Control field views and
the two clamp function parameter declarations agree with their existing
recovered definitions. Binary layout agreement between partial struct views
does not by itself prove whole-program effective-type/strict-aliasing safety.

| Input condition | Behavior |
| --- | --- |
| Pressed bit1 (`2`) | Compare four state settings bytes against02002FC0. Equal: audio call(1,69), return2. Different: return4. This branch takes priority when both bits are set. |
| Neither bit1 nor bit0 | Pass the repeated halfword to0800927C and return its low byte. |
| Pressed bit0 (`1`) | Compute selected index and destination through the two clamp helpers. Disabled entry: audio call(1,6B), return0. Zero count: return3. |
| Enabled entry with nonzero count | Query setting9, increment current modulo256 and reset to0 if the narrowed current reaches/exceeds count. Invoke08009030 with low-byte index and captured destination. |
| Overlay returns nonzero low byte | Capture current global entry9, apply setting(selected,0), query setting9 again. If its low byte changed, write the previous byte to the captured entry9 enabled field and redraw with argument6 if the captured control's signed scroll exceeds2. Finally call audio(64), return0. |
| Overlay returns zero low byte | Keep the earlier increment/reset and return0 without setting/audio follow-up. |

The actual clamp helpers form a signed16 narrowing of
`signed8(selection)+scroll`, clamp it to0..count-1, and returnu16. The second
executes actual08142950 remainder instructions and computes
`u16((selected % divisor)*width*2 + base)`. Destination is buffer+position*32.
The caller indexes records with signed16 selected but passes unsigned low
byte selected to later helpers. The runtime domain restricts count to1..10,
divisor to1..255 and all backing storage to valid initialized objects.
Zero divisor and invalid/negative record indices are outside that domain.
Signed narrowing is target-defined two's-complement behavior; tested
arithmetic does not overflow promoted signed32 values. The unsigned-byte
increment intentionally wraps before comparison. No extra signed-overflow
or trap behavior is assumed.

Calls may change the global pointer. The source reloads it where required,
but retains previously captured control/entry/destination pointers. Those
objects must remain alive and nonconflicting. The tests include global
replacement after the overlay and again during setting application, and
changes to the old captured control's scroll. They do not prove arbitrary
reentrancy, frees, asynchronous input updates, helper retention, rendering
capacity or aliases with globals/stack. The partial state view's minimum
storage is not a nominal allocation claim.

## Function-type integration issue

The natural definition is `u8 func_08009140(void)`. Incomingr0 is overwritten
at0914A before use, and no incoming register/stack argument is consumed.
The state comes from02009188. The freeze intentionally does not manufacture
an unused parameter to match an older provisional caller declaration.

Frozen08954v3 currently declares
`u8 func_08009140(State08008954 *state)` and invokes
`selection = func_08009140(*current)`. Its return type agrees, but the
argument lists are incompatible C function types across translation units.
`typing-evidence.json` pins that exact caller/source and the machine evidence.
The parent must assess both its declaration and call expression together
before any future integration; neither frozen source is silently changed
here. Merely observing that the extra r0 word is ignored does not establish
whole-program C compatibility. This issue is separate from the byte mismatch.

## Compiler and verifier evidence

Original ELF checks establish exactly one316-byte function and316-byte
`.text`, alignment4, no extra allocated helper/data bodies and no external
padding. All twelve original relocations are addressed `R_ARM_THM_CALL`s.
The official typed linker resolves them to unique indexed Thumb entries,
without veneers or unresolved relocations; exact symbol types/odd addresses,
non-relocation byte preservation and full objcopy/ELF equality are checked.
The ordinary ABI-summary CFG verifier accepts every caller path. It does
not prove the actual callees' semantics or termination.

The candidate owns304 code bytes/140 instructions and12 internal literal
bytes, with no padding. It materializes03000000 using two instructions
instead of the ROM literal, moves the repeated-input value through another
register, and schedules the u16-result shift earlier around display loads.
Later selected/reset values use r4/r5 differently. Those choices alter
initial offsets/literal placement and register encodings; no source rewrite
is used to force the ROM's choices.

- Full target-body SHA256:
  `c8495ae33bc775df99e279ee380bae35561276a81a416c4fa729825c691e86e4`.
- Full candidate SHA256:
  `69cc6c7636f7ecc844a56f966ffe12fb1cf294b7bd95251a24a2966a246d4b38`.
- `official-report.md` remains NOT MATCHING. Strict replay rejects it and a
  copy changing only its verdict to MATCH. These two no-credit checks are
  not a claim of exhaustive adversarial report coverage.

## Bounded execution evidence

`runtime.py` independently computes expected scalar results, ordered call
arguments and ordered writes for30 cases, then runs both caller ROM and the
complete linked candidate:60 executions. All138 ROM and140 candidate caller
instructions are visited. This is instruction coverage, not exhaustive paths.

Actual ROM helpers execute:080096B0 comparison,08017B68 clamp,08017B9C
position, and08142950 remainder. Visited instruction counts are20,26,37 and84
respectively; full windows/hashes are retained. Comparison always receives
length4; its nonpositive-length path is not covered. Remainder's zero-divisor
path is explicitly excluded. No BIOS or hardware implementation executes.

Six entire helper boundaries are models:080094BC,08009030,08008F94,
08141540,08141570 and0800927C. Setting queries supply explicit arbitrary
return words; setting application writes a test marker and may replace the
global pointer or captured control field. Overlay writes a one-byte marker,
supplies an arbitrary return word and may replace the global pointer. Audio
and redraw models are argument-observing no-ops. Navigation supplies the
specified return word. Every model clobbers r1-r3/r12 and arithmetic flags,
preserves callee-saved registers/SP, and does not retain pointers. These
effects are fixture behavior, not inferred actual helper contracts. In
particular the prior Parked08F94 recovery is not substituted or executed.

Cases cover cancel priority, equality and each mismatch position, navigation
low-byte return contamination, disabled/zero-count entries, current values
at/above the cycle bound and255 wrap, overlay low-byte success/failure,
equal/different low-byte setting queries, scroll thresholds2/3 and negative
signed values, signed8/16 clamp boundaries, final position wrapping, and
the pointer-replacement scenarios described above.

Checks compare full EWRAM, whole IWRAM after explicitly accounted stack
writes, exact ordered non-stack writes, helper argument/order, initialized
consumed RAM reads, current-frame stack accesses, caller saved-register image,
r4-r11, balancedSP, returnbyte and Thumb/ARM return mode. Both word-alignedSP
residues are covered. Caller frame is32 bytes; actual nested frames are
bounded by48 bytes. Different dead helper-frame return-address contents
between the two code layouts are not required to be identical.

Ten executed controls catch cancel-mask/return changes, destination stride,
enabled predicate, increment, cycle bound, redraw threshold, actual comparator
equality mutation and uninitialized current-record reads in both bodies.
No universal helper, input-domain, whole-game or whole-program C proof is
claimed.

## Reproduction and cleanup

    env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
      PATH=/home/user/armtc/root/usr/bin:$PATH \
      python3 /home/user/.codex-work/ffta-ulw/08009140-author/check.py

The checker uses immutable game-next-73c22d0 and approved
kit-software-double-candidate-v3. All nine headers and corrected metadata are
copied only into an owned disk fixture; TMPDIR points there. Fixtures clean
on exit and all original input pins remain unchanged. Independent review
should run copies in its own sibling directory to preserve this freeze.
No production, shared headers/maps/tools, Git, status or lease operations
occurred. Parent owns integration/release. Only text evidence remains.
