# 08008E94 — Parked v2: compatible signed-byte helper declaration

The only C change from the preserved first attempt is the declaration of
`func_08008F94`: its parameter is now `s8`, not `s16`. This agrees with the
separately recovered definition and the actual callee's low-byte sign extension.
`source-change.patch` records the exact one-line delta. No statements, types of
other helpers, flags, expression ordering or storage arrangements were changed.

The fixed agbcc `-mthumb-interwork -O2` build remains **NONMATCH**: its complete
function symbol is **236 bytes**, versus the **256-byte** ROM span
`[0x08008E94,0x08008F94)`. This is not a verifier-only failure or a match.

## Complete body and official result

The ROM contains 109 reachable instructions/238 code bytes, two internal zero
alignment bytes at `0x08008F02`, and four reached literal words at `0x08008F04`,
`0x08008F88`, `0x08008F8C` and `0x08008F90`. Raw Thumb branch/literal decoding,
Capstone CFG traversal and Binary Ninja instruction lengths agree. The proposed
metadata change remains instruction count **128 to 109**, with no endpoint
change. `metadata.patch` is only a proposal in this isolated author directory.

The candidate has 101 instructions/222 code bytes, two alignment bytes and
three literal words. Original and linked ELF symbols are both 236 bytes; no
pool or external padding is omitted. All ten `R_ARM_THM_CALL` and two
`R_ARM_ABS32` function bindings resolve to typed odd Thumb symbols. There are
no remaining relocations, unresolved symbols or other allocated payload.

Relative to the old candidate, only bytes at offsets `+0x69` and `+0x6B`
change: the caller's signed argument narrowing now shifts by 24 rather than
16 bits. This observation is a result of the grounded type repair, not a source
search. Relative to ROM there are still 243 unequal byte positions, including
20 absent bytes. The first difference is `+0x02`: ROM `57`, candidate `47`.
The ROM saves r8-r10 and has a 48-byte caller frame; the candidate saves r8
and has a 40-byte frame. Pointer allocation, epilogues and pool reuse differ.

- Source SHA256: `f8b624950d5a13eb956dd1ff8c110a6f341220435b7f48095173668eb93f83a9`
- ROM body SHA256: `82f7bc8e7e8c65153fbad75d3edd37f7273837b9867f1bc3cffe930149be5f28`
- Revised candidate SHA256: `5b3cc45218a8d287c14a8d8673e456b6e8af3f73651054edb0f1cf828f232412`

The unchanged approved `kit-software-double-candidate-v3` exits 1:

```text
function-address caller requires an exact mapped Thumb span;
function-buffer proof: function-address caller requires an exact mapped Thumb span
```

Separate submission of the actual complete ROM body and its exact binding
manifest still rejects with `function-address evidence supports only frameless
callers` and `function-buffer evidence requires an inspected buffer call`.
Scalar outgoing words are not a borrowed local buffer. No verifier or mapping
was altered to bypass this. No successful report exists; successful-report
strict replay is inapplicable. `official.log` is failure evidence, not a report.

## Signed-byte boundary and actual execution

The loop index is bounded by a freshly reloaded byte count, but may reach 254.
The new target-compiler call narrows this index to signed byte before entering
08F94. The ROM caller supplies the original nonnegative index. The test keeps
these raw registers distinct and executes the actual 36-byte/17-instruction
08F94 prefix, including the BL at `0x08008FB4`, stopping at the first helper
entry `0x08017B9C` before that helper executes.

| Loop index | ROM raw r0 | Revised raw r0 | Actual prefix signed value |
|---:|---:|---:|---:|
| 127 | `0000007F` | `0000007F` | 127 |
| 128 | `00000080` | `FFFFFF80` | -128 |
| 129 | `00000081` | `FFFFFF81` | -127 |
| 254 | `000000FE` | `FFFFFFFE` | -2 |

At that cutpoint both callers produce identical r1 bits. The actual prefix
reloads `0x02009188` and supplies current-state +0x2F0 in r0. Its 28-byte open
frame, saved r4-r8/LR words, initialized r8, retained r9-r11 and BL return
address are checked before the model resumes the caller. The model explicitly
restores that activation's saved state; the actual remainder/epilogue is not
executed. It writes a synthetic signed-normalized result marker and may change
the global count/pointer. Those writes test caller reloads, not actual 08F94
effects. No downstream bounds, valid negative index use, or full helper closure
is proved by this prefix test.

Two complete leaves execute unchanged actual code: 17B50 returns the u16
conversion of `min(u8 field_16, s16 field_18)`; 17FB0 stores its low-byte
argument at +0x11 and its shifted value at +0x0E. A negative limit can yield
255 when the caller stores the low byte. Seven other direct helpers are whole
ABI/effect models: 15C90, 17AD8, 17AF4, 15D58, 09414, 157A8 and 16234.
Callback bodies 17E80/17F04 are not executed. Their bindings do not establish
callback lifetime or universally compatible callback invocations.

## Bounded validation and limits

32 ROM/revised-candidate executions cover eight cases, ARM/Thumb returns,
EWRAM/IWRAM state placement, 0/1/2/4/129/255 iterations, count growth/shrinkage,
active-pointer replacement, dimension/halfword wrapping and all caller, leaf
and prefix instructions. Checks include initialized RAM reads, all outgoing
words, exact non-stack writes, bounded frame writes, unchanged remaining RAM,
SP and saved-register ABI. Eleven runtime negative controls are detected,
including wrong callee sign extension, narrowing width and global pointer.
28 target layout/arithmetic assertions pass. A compatible s8 redeclaration
compiles; adding the old incompatible s16 declaration fails compilation.

The source requires aligned, live initialized state/resource storage and the
stated helper contracts. Unsigned byte/halfword conversions are modulo width;
promoted sums are at most 131070 and the loop counter cannot overflow int.
Conversion of 128..254 to s8 is **implementation-defined**, not portable ISO C
representability. Its signed-low-byte behavior is checked on the fixed target
compiler. Emulator runs do not establish abstract C object lifetime/aliasing,
asynchronous behavior, frame separation for arbitrary allocations, actual
modeled helper semantics or universal equivalence. Other cross-TU interface
questions are outside this one-declaration repair.

## Reproduction and preservation

Evidence resides in `/home/user/.codex-work/ffta-ulw/08008E94-author-v2/`.
`probe.py` builds a private fixture from immutable `game-next-73c22d0`, copying
all nine headers and applying only the count proposal. `check.py` recompiles
and runs the bounded execution and type checks. Run each with `FFTA_ROM`
unset, `PYTHONDONTWRITEBYTECODE=1`, `TMPDIR=/home/user/tmp`, and the ARM
toolchain on PATH. Both scripts capture/recheck inputs and remove their own
generated fixtures/binaries. The original `08008E94-author` and its independent
review remain unchanged, with their historical source/manifest pinned.
