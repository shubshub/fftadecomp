# 080C8570: redirected record-field lookup

## Status and complete target

This is an honest source recovery, not a byte match. The retained source
compiles to one 1,194-byte Thumb function with 497 instructions; the complete
target is `[080C8570,080C8A24)`, 1,204 bytes and 501 reachable instructions.
No prefix match or target-span extension is claimed.

The target contains 1,002 instruction bytes, two internal zero bytes at
`080C8596`, two literal words at `080C8598` and `080C859C`, and a 48-word
table at `[080C85A0,080C8660)`. The first literal binds the named object
`g_table_08521A14`; the second points to the local switch table. All 48
destinations are even, distinct instruction entries. `080C8A24` begins a
separate function and is excluded.

The entry saves `r4`, `r5`, `r6`, and LR. There is no fixed frame, incoming
stack argument, nested call, or non-stack write. The selector comparison is
at `080C858A`, its backward unsigned-default branch at `080C858C`, and the
four dispatch instructions at `080C858E..080C8594`. The table base is loaded
once into `r6` at `080C8588`. The two redirect backedges return to the
comparison. The published `98fb667` preloaded-switch CFG validator accepts
all 501 actual-ROM instructions; its support is not a global blocker.

## Interface, fields, and control flow

The compatible calling interface is `u32(u8 first, u8 second, u8 selector)`.
All three incoming values are narrowed to their low eight bits. Incoming
`r3` and stack arguments are not consumed. Existing matched callers use
this interface; the actual BL at `080C930C` in `080C92F0` corroborates the
entry. Terminating results fit in 16 bits, but this does not uniquely prove
an original narrow return declaration: the routine forwards a full word.

Each record has observed stride `0x34`. The initial record is selected by
`first`. Selector 2 returns its raw byte at `+5`. Every other supported
selector first checks that redirect byte: `0xFF` selects `second`, another
nonzero value selects that record index, and zero permits the field read.
The nonzero/non-`0xFF` path reads the redirect byte a second time. The source
preserves these per-case checks and read order rather than hoisting them
outside the switch.

Selectors above 47 intentionally loop at the guard without reading record
data. Redirect chains can cycle, including a fallback record redirecting
to itself. No termination guarantee, extra guard, or default return is
introduced. The selected record bytes must be readable; no table allocation
length or index-validity bound is inferred from the eight-bit parameters.

The source models observed byte fields and byte-local bitfields without
packing attributes. Cross-byte values remain explicit combinations. This
table uses decimal selectors and hexadecimal byte offsets; `byte` denotes
an unsigned byte, and all shifts are logical.

| Selector | Returned field when no redirect is followed |
| --- | --- |
| 0 | `byte00 | byte01 << 8` |
| 1 | category byte `04` |
| 2 | raw redirect byte `05` |
| 3 | byte `06` |
| 4 | `byte07 | byte08 << 8` |
| 5 | `byte09 | byte0A << 8` |
| 6, 7 | low and high nibbles of byte `0B` |
| 8..13 | bytes `0C..11` |
| 14 | `(byte12 >> 3) & 7` |
| 15 | `(byte12 >> 6) | (byte13 & 1) << 2` |
| 16 | `(byte13 >> 1) & 7` |
| 17 | `(byte13 >> 4) & 7` |
| 18 | `(byte13 >> 7) | (byte14 & 3) << 1` |
| 19 | `(byte14 >> 2) & 7` |
| 20 | `byte14 >> 5` |
| 21 | `byte15 & 7` |
| 22..25 | bytes `16..19` |
| 26 | `byte1A | (byte1B & 15) << 8` |
| 27 | `(byte1B >> 4) | byte1C << 4` |
| 28 | `byte1D | (byte1E & 15) << 8` |
| 29 | `(byte1E >> 4) | byte1F << 4` |
| 30..32 | bytes `28..2A` |
| 33 | byte `2C` |
| 34, 35 | low and high nibbles of byte `2B` |
| 36..40 | bytes `2D..31` |
| 41..47 | bytes `20..26` |

The compiler's observed record size is 52 bytes. Paired execution exercises
every selected field and bit partition against the actual byte-based ROM
behavior, including high-bit and combined-field values. This is a recovered
layout, not a claim that the original source used these names or types.

## Remaining code-generation differences

The retained function saves `r4`, `r5`, and LR, not the target's additional
`r6`. Its initial pointer calculation lacks the target's separate base-copy
instruction. The record, table base, and selector therefore use different
registers throughout. Its guard is at `080C8588`, rather than `080C858A`.

The candidate has no internal alignment halfword before its object word.
Its object word, table pointer, and first case are at offsets `0x24`, `0x28`,
and `0xEC`; the target uses `0x28`, `0x2C`, and `0xF0`. Its 48 table words
and every changed case displacement are included in the full comparison.

The candidate's selector-18, selector-26, and selector-28 combined fields
use two shifts where the target uses a mask materialization, AND, and shift.
Each removes one instruction. Together with the missing initial base copy,
this accounts for four fewer instructions. Removing the target's two-byte
internal alignment accounts for the remaining size difference. Other
operand allocations and the selector-15 extraction sequence also differ.

The candidate symbol ends at `080C8A1A`; its `.text` section is 1,196 bytes
because the assembler adds an external halfword after the 1,194-byte symbol.
That external halfword is not included in the candidate comparison. The
object has exactly one emitted function and 50 ABS32 relocations: one named
object binding, one local table pointer, and 48 local case words.

The official fresh `98fb667` matcher exits 1 with
`switch requires one exact adjacent unsigned guard and five-op dispatch`.
The candidate does not have the supported preloaded layout, so it cannot
produce a successful report or replay. This candidate-local profile
rejection does not explain away the independent full-symbol mismatch.
No report, active source, or private header remains under `src/` for this
address.

## Natural alternatives checked

- An ordinary byte-view switch with explicit masks and little-endian
  combinations compiles to 1,208 bytes and 504 instructions. It also has
  different register allocation and the unsupported dispatch layout.
- Computing a byte offset before adding the named table base changes the
  initial multiply/load scheduling but leaves that candidate at 1,208 bytes.
- The retained detailed byte-local bitfield record naturally produces the
  observed single-byte bitfield shifts but compiles to 1,194 bytes instead
  of the complete target's 1,204 bytes.
- Small compiler-layout probes showed that cross-byte bitfield declarations
  can widen memory reads; these were not incorporated. A naturally typed
  16-bit little-endian temporary did not change the tested load ordering.

No compiler-option search, forced register/storage declaration, artificial
alignment, inline assembly, packing attribute, or dummy control flow was
used. Source plausibility passes under the reviewed toolkit.

## Validation and future integration

The retained local verification script is
`/home/user/.codex-work/ffta-ulw/080C8570/check_recovery.py`. It compiles the
parked source with the complete current game include tree and standard
agbcc `-mthumb-interwork -O2`, then separately executes the actual ROM body
and freshly linked recovery using Unicorn. The diagnostic linker resolves
the named table to its actual address; this is not an official typed-link
or successful-match proof. All generated binary artifacts are removed.

The run passes 7,168 paired cases: 1,600 use explicit synthetic record-table
overlays and 5,568 use pristine ROM bytes with first/fallback indices 0..115
and every supported selector. It observes 6,678 returns and 490 bounded
non-returning executions. The latter include all 208 invalid low-byte
selectors and redirect cycles; instruction budgets are reported as bounded
observations, not universal termination proofs. No helper stubs are used.

Checks cover all 501 target and all 497 candidate instructions, exact ordered
record-byte reads, expected result values, low-eight-bit argument handling,
unmodified table memory, only the appropriate saved-register stack writes,
and restored callee-saved registers/SP/return control on terminating paths.

Reproduction from the game root:

```sh
export PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp
export PATH=/home/user/armtc/root/usr/bin:$PATH
python3 /home/user/.codex-work/ffta-ulw/080C8570/check_recovery.py Parked/080C8570/080C8570.c
python3 /home/user/.codex-work/ffta-ulw/kit-reviewed-98fb667/tools/plausible.py Parked/080C8570/080C8570.c
```

The detailed tagged `CategoryRecord` here is **not C-type-compatible** with
the existing anonymous three-member `CategoryRecord` declaration of the
same global in active `080C94D0.c`, even though category offset and stride
agree. That active source is unchanged. Any future promotion must first
coordinate one compatible record declaration across both translation units
and independently reverify `080C94D0`; this parked recovery is not part of
the active build.
