# 080099A4 — first natural source, Parked only

## Outcome and ownership

The unchanged first source `080099A4.c` is **not a match**. Fixed agbcc
`-mthumb-interwork -O2` produces a complete 28-byte function, while the ROM
owns 32 bytes. The official matcher exits 1 with
`compiled symbol is shorter than the indexed span: 28 < 32`.
`first-official.log` preserves the first attempt; `official.log` is a fresh
reproduction. No source iteration, flag sweep, compiler-steering construct,
extent truncation or synthetic padding was attempted.

This isolated author directory contains no active production source or MATCH
report. The parent owns integration, metadata changes and lease release.
Both proposed patches are evidence only and have not been applied here.

Source SHA-256:
`02cdaf72ee3a22d8a96c7113c0342338ed771c0c3b8dc7145ba66173a6c53f34`.

## Complete body and exact discrepancy

| Property | ROM | Compiled first source |
|---|---|---|
| Full interval at the target entry | `[080099A4,080099C4)` | `[080099A4,080099C0)` |
| Complete symbol / text bytes | 32 | 28 / 28 |
| Reachable instructions / code bytes | 13 / 26 | 12 / 24 |
| Internal alignment | 2 zero bytes at 080099BE | none |
| Literal | 03000890 at 080099C0, offset 28 | 03000890 at 080099BC, offset 24 |
| Original and final ELF relocations | not applicable | none |

`CLASSIFIED.txt` records the complete independently decoded bodies. The local
CFG traversal establishes reachability and pool ownership; Binary Ninja's
Thumb decoder independently agrees on every instruction length. The ROM's
indexed end is correct. The current count 16 includes non-code words and
should be corrected to 13 in both indexes; `metadata-proposal.patch` changes
only these two counts.

The candidate folds the callback member's `+4` offset into `ldr r0,[r0,#4]`.
The ROM instead adds 4 to the table base in a separate instruction before
loading `[r0]`. Register allocation and the order of the table literal load
versus the handle shift also differ. One instruction and the subsequent
two-byte alignment disappear, moving the pool four bytes earlier. Relative
to the complete 32-byte ROM span, 25 positions differ or are absent in the
candidate; 7 positions are equal. This is a same-offset metric, not an aligned
diff percentage or partial-match acceptance.

ROM body SHA-256:
`33319daaae89f4756a3d93c753df636ae48c132cddf487efe59fdca3e317dc5b`.
Candidate body SHA-256:
`efc51c7174e3a746ff9f09debaca8848011d9fff39c93463cee0dc94d0c9dc60`.

The fresh original ELF has exactly one Thumb function symbol, value 1 and
size 28, a 28-byte `.text` with alignment 4, and no extra allocated payload.
A diagnostic fixed-address link has the same complete body, one function at
080099A5, no relocations, and no extra allocated payload. `build.json` pins
both ELF hashes and all target-relative differing positions. No linked bytes
were substituted for a shorter symbol or interpreted as a successful report.

## Recovered interface and known caller boundary

The source reads one callback word from a four-record table at 03000890,
using an 8-byte record with a full-word context at +0 and a callback at +4.
It returns 1 for a null callback and 0 otherwise; it neither invokes the
callback nor writes the table. The private `u16 (*)(u32)` callback view is
consistent with the frozen registration/dispatcher family proposal and the
baseline 098C4/098F4 declarations, whose paths and hashes are captured.
This query alone cannot establish a callback's nominal C type or validity.

`u32 handle` is a minimal full-word view justified by the target's direct
`lsls r0,r0,#3` of incoming r0, with no byte truncation or bounds guard.
It is not narrowed merely to preserve a historical caller declaration.
The exact original nominal parameter type is not uniquely recoverable from
this instruction sequence. The u8 result retains the known caller convention;
actual machine results are full-register 0 or 1, so this likewise does not
uniquely prove the original nominal return type.

The immutable baseline's `Parked/08008954/08008954.c:48` instead declares
`u8 func_080099A4(u8 handle)`. Its calls at source lines 85 and 92 pass an
object's u8 member at +0x20. The actual ROM call sites 080089D2 and 08008B1A
are preceded by `ldrb r0,[r0]` and followed by a left shift of returned r0 by
24 for a low-byte test. Both bounded raw windows are pinned in `build.json`.
They establish byte-valued inputs at these two sites, not a universal
parameter narrowing and not the required bound below 4.

`caller-declaration-proposal.patch` proposes only changing that declaration
to `u8 func_080099A4(u32 handle)`. A target-compiler combined-declaration
positive accepts the new signature; the old u8-parameter redeclaration
correctly fails with conflicting types. A separately assigned author owns
the caller repair and its complete-object comparison. This directory does
not modify the caller or claim current whole-program C compatibility.

## Bounded verification

- Eight target-compiler assertions establish scalar widths, record size,
  member offsets, callback-pointer width and record alignment.
- The bounded source plausibility checker returns no findings. The official
  invocation stops at the short-symbol guard before its own plausibility or
  MATCH verdict, so these are deliberately distinct claims.
- Twenty-four ROM/candidate pairs (48 executions) cover all four valid slots,
  null and two registered Thumb callback representations, ARM and Thumb return
  modes, varied register/RAM seeds, and both tested SP residues modulo 8.
- Each execution checks the exact ordered four-event memory trace: saved LR
  write, complete literal read, callback word read, saved LR read. The known
  different pool addresses are independently checked, not silently equated.
  All EWRAM/IWRAM bytes, the boolean result, r4-r12, LR, restored SP, return
  mode and the 4-byte maximum stack depth are checked. All 13 ROM and all 12
  candidate instructions are covered across the cases.
- Five machine-only negative controls are detected: wrong stride, wrong
  member offset, reversed null test, wrong true result, and byte instead of
  word load. These mutate test bytes only, never the recovered C.

There are no helper models or helper calls in this task, and no callback is
executed. Finite executions support only the tested contract, not universal
equivalence. Valid typed C requires live, suitably aligned table storage and
a handle in 0..3, valid null/function-pointer representations under the target
ABI, and a live nonoverlapping stack. Larger handles, full-word shift wrap,
arbitrary pointer representations, asynchronous table mutation, callback
lifetime and whole-game scheduler behavior are outside the claim. In
particular, machine wraparound does not make out-of-array C accesses valid.

## Inputs, reproduction and cleanup

The immutable game fixture is `game-next-84ef534` (505 active source files).
The requested published toolkit is the sibling `fftadecomp-kit`, parent
identified as commit c3baef2; `input-pins.json` binds its actual file contents,
the ROM, both indexes, data mappings, all `source_paths` headers, relevant
family sources/proposal, the parent dump and compiler/binutils inputs.
The checker copies only necessary fixture inputs, never the full game, and
rechecks every captured input after verification.

Run in an owned copy of this author directory to preserve a final freeze:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /path/to/owned-copy/check.py
```

The checker resolves the immutable game as a sibling of its work directory;
place the owned copy under `/home/user/.codex-work/ffta-ulw/`, or preserve that
same fixed input relationship. `check.py` runs the requested official command
against its private fixture. `freeze.py` validates retained results and pins
the final text artifacts. All generated objects, assembly, preprocessed files,
ELFs and fixture directories are removed. Only reproducible text evidence
remains. There is no MATCH report to replay; saved-report validation is not
applicable to this rejected first source.
