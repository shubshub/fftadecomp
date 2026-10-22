# 081443FC: forward byte/word copy

**Parked: the natural recovery is not byte-identical.** The complete target
and candidate are both 98 bytes / 49 instructions, but 12 register-operand
bytes differ. The official frozen 4847c93 matcher reports `NOT MATCHING -
bytes differ`; this is not a verifier-profile limitation. No active source,
MATCH report or strict MATCH replay is claimed.

## Complete symbol evidence

- Target: `[0x081443FC, 0x0814445E)`, entirely 98 code bytes / 49
  instructions, with no literal pool, table or internal alignment.
- Target SHA256:
  `aa822d873bad381a62e3c3e07b06003a41beea59bc3edc791f7e316eb08b7ebb`.
- Candidate SHA256:
  `41cd7e4c5f71ca3083741f5881525355bd1ce438800f0c01939a347bf32a2d47`.
- The fresh ELF has exactly one 98-byte FUNC and no relocation. Its `.text`
  section is 100 bytes because of the following external `c046` assembler
  padding. ROM has external `0000` at `0x0814445E..0x08144460`; neither
  padding halfword belongs to this function. The separate next prologue
  starts at `0x08144460`.
- Both complete bodies pass the frozen closed-leaf CFG checker. Scoped
  plausibility has no findings. Target-compiler assertions confirm u8 size
  one, u32 size/alignment four and pointer size four.
- Same-address equality is 86/98 bytes and 37/49 instructions. These are
  diagnostic full-symbol positional counts, not matching credit.

The differences are confined to the aligned word-copy phase and its cursor
transitions. The ROM retains the word source in r3 and destination in r1;
the candidate uses r1 and r4. The corresponding initial and final cursor
copies also differ. The word load/store widths, loop counts, branches,
instruction locations, saved registers and byte-copy phase agree. No
instruction substitution, prefix comparison or padding substitution was used.

## Bounded natural forms

The unchanged default flags were `-mthumb-interwork -O2`.

1. Byte cursors for the generic copy, with branch-local word cursors
   initialized from the original void-pointer arguments: 98 bytes / 49
   instructions, with the register differences described above.
2. Initialize those word cursors by casting the current byte cursors,
   making the byte-to-word-to-byte phases explicit: the identical candidate
   bytes. This readable form is retained.

No further register-allocation, declaration-order or scheduling variants were
attempted. There was no flag sweep, forced register/storage, inline assembly,
pragma, volatile access, manufactured CFG or inert work. This is a local
recovery result, not a claim that an honest exact recovery is impossible.

## Interface and effects

The compatible interface remains
`void *func_081443FC(void *destination, const void *source, u32 byte_count)`,
matching the existing Parked 08005EF8 declaration. All three full inputs are
consumed; original r3 is overwritten before use. There are no additional
arguments, helpers or local stack frame. The original destination is returned
unchanged, with 12 bytes of saved registers restored.

For an initial length at most 15, or either pointer not word aligned, the
function copies only forward byte read/write pairs. Otherwise it copies
four consecutive word pairs per 16-byte group, then remaining whole words,
then remaining bytes. Each load precedes its paired store; pointers advance
forward. A zero length makes no source/destination access. Nothing is
retained elsewhere and no hardware transfer or allocator is involved.

The ordinary source domain requires adequately backed readable/writable
nonwrapping spans and suitable lifetimes. Describing it as memcpy-like
requires nonoverlap; it is not memmove. The aligned word branch also uses
u32 lvalues, so the local C recovery does not establish a portable generic
effective-type guarantee for every arbitrary object representation. Actual
toolchain machine behavior is separately tested; synthetic RAM is not a
proof of all ISO C object-lifetime or alias domains. No restrict annotation,
extra guard, allocation bound or universal pointer-validity claim is added.

Actual inbound BL at `0x08005F32` establishes a direct caller. That caller's
12-byte count always follows the byte path, independent of alignment. This
does not prove the whole caller's allocation or lifetime discipline.

## Focused behavioral evidence

The retained reproducer freshly builds the parked source, verifies the
complete ELF/type/CFG/plausibility facts and reproduces the official nonmatch
in a disk-backed isolated root. It then runs 15 paired actual-ROM/candidate
fixtures, 30 executions, covering all 49 instructions in each body.

Twelve disjoint synthetic-RAM cases exercise lengths 0, 1, 12, 15, 16, 19,
20, 31, 65 and three independently misaligned-pointer combinations. Three
additional overlap cases are explicitly machine-only diagnostics, with
destination above or below source and aligned or byte-copy paths. They are
not C memcpy/memmove correctness claims.

A separately specified mutable-memory oracle checks the exact ordered data
read/write widths and values, complete fixture RAM, unchanged nonstack
IWRAM, original-destination return, unrelated incoming r3 values, r4-r11,
SP/return and 12-byte save depth. Instruction fetches and stack accesses are
excluded from ordered data traces; saved ABI is checked separately. No
helper or callback models are used. These are bounded finite tests, not a
proof for impossible backed spans near the full u32 length limit.

The retained author reproducer is
`/home/user/.codex-work/ffta-ulw/081443FC-author/check.py`; `check.log` records
the successful run. Run with FFTA_ROM unset, `PYTHONDONTWRITEBYTECODE=1`,
`TMPDIR=/home/user/tmp` and `/home/user/armtc/root/usr/bin` on PATH. It cleans
its temporary build tree, retaining only small text evidence. No ROM or
compiled binary is stored with this parked recovery.
