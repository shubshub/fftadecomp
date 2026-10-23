# 0800A0B4: exact empty-function recovery rejected by the plausibility gate

The first natural source is an empty `void func_0800A0B4(void)` function. With
agbcc `-mthumb-interwork -O2`, its complete ELF function symbol is exactly the
two ROM bytes at [0x0800A0B4,0x0800A0B6), the Thumb instruction `bx lr`.
There were no source revisions after the first compile.

The official matcher exits 1 because `plausible.py` classifies every empty
function body as `ERROR: empty-body`. Its resulting verdict is
`HAND-ASM REQUIRED BUT NOT ALLOWED`, despite this source containing no assembly,
attributes, or other steering constructs. This source remains Parked and has
no matched-function credit under the current published toolkit. No exception,
allow-list entry, or alternate spelling was used.

## Entry and signature evidence

An actual Thumb BL at 0x0800A070 calls this entry. Its caller has a conventional
prologue at the indexed address 0x0800A06C and immediately overwrites r0 at
0x0800A074. This call supports a void result. The body reads no arguments, so a
no-argument prototype is compatible, but unused argument types and an ignored
return type cannot be recovered uniquely from these bytes.

A bounded Thumb BL-encoding scan over [0x08000000,0x08150000) finds that one
candidate site; an aligned 32-bit scan over the full ROM finds no literal equal
to the Thumb pointer 0x0800A0B5. These scans do not establish a complete call
graph or runtime reachability.

## Function extent and adjacent bytes

The generated STT_FUNC symbol has size 2, Thumb value 1, and offset 0 in a
four-byte-aligned .text section. There are no relocations or other allocated
payload sections. The full section is `7047c046`: its final `c046` is assembler
padding outside the function symbol. The ROM instead contains `0000` in the
unindexed interval [0x0800A0B6,0x0800A0B8), before the next indexed entry.

`bx lr` cannot fall through into that gap. The function's complete symbol is
byte-identical, but the full section is not. Preserve the original gap bytes;
do not expand the function endpoint or claim their original linker provenance.
No function-index or data-symbol changes are proposed.

## Verification

The local author evidence bundle records fresh official compilation, complete
ELF inspection, and 128 Unicorn executions covering all 16 NZCV patterns, four
register patterns, and both aligned Thumb and ARM return addresses. Every run
executes only `bx lr`, performs no memory access, preserves r0-r14, and returns
to the selected mode/address with NZCV unchanged. Unicorn's ARM926 model tests
the shared instruction semantics; it is not a cycle-accurate ARM7TDMI test.

Five mutated machine bodies fail the runtime contract. Eight ELF/CFG negative
controls reject wrong mode, alignment, section, type, size, or return structure.
Both the official rejected report and a forged MATCH verdict retaining its
IMPLAUSIBLE field fail report replay. The source's SHA-256 remains
`0d36b6d08750a31ab7af7cd296c2868eccee3839e5a3e703a1c06f470fdec4a5`.

Detailed artifacts are in the frozen local author bundle, not this publication
directory. Reproduction requires the approved ROM, the published c3baef2 toolkit,
and the bundle's private fixture. From a separate copy of that bundle, run
`python check.py` with the ARM toolchain on PATH and a disk-backed TMPDIR. An
official invocation is `python /path/to/toolkit/tools/match.py --root fixture
0800A0B4`; exit 1 with the empty-body finding is the expected result.

This is an exact semantic recovery with a current plausibility-policy rejection.
It does not show that the function requires hand-written assembly or that
decompilation is impossible.
