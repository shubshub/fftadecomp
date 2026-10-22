# 0x08006C88 — parked, not matching

The retained natural free-list search has tested matching behavior but a
different complete instruction sequence. It is not a byte-exact match and has
no active source, private header or saved matching report.

## Complete-symbol evidence

- Target: `[0x08006C88,0x08006D36)`, 174 bytes / 87 reachable Thumb instructions.
- Target SHA256: `7753b4551e4d959c458be6fb052231a28bdd00592aa2a47c75f066aeb2de5dd5`.
- All 174 target bytes are code. There are no literal pools, jump tables or internal alignment bytes. The zero halfword at `[0x08006D36,0x08006D38)` is external and excluded.
- Retained candidate: exactly one emitted `STT_FUNC`, 182 bytes / 91 instructions, with no relocations or emitted helper functions.
- Candidate SHA256: `d4c24bf6f12fd46c68d46e5eace319208912e9a867b6943fbf1ffb4305a4a028`.
- Candidate `.text` is 184 bytes; the final `c0 46` halfword is assembler alignment outside the 182-byte function symbol and is excluded.
- Exactly 30/174 overlapping same-position bytes and nine same-address instructions agree. The candidate has eight additional function bytes, not eight additional target bytes.
- Frozen toolkit `a39dbf9` accepts the complete leaf CFG and source plausibility, then reports `NOT MATCHING - bytes differ`. There is no matching-report replay claim.

The ordinary matcher displays a ROM window as long as the candidate. Its
182-byte target display consequently extends eight bytes beyond this function
and includes external alignment and the following function. That display is
not evidence that the target is 182 bytes. The independent comparison uses
the actual 174-byte target and the complete 182-byte candidate separately;
neither is truncated or promoted on a prefix comparison.

The differences include the placement of the saved owner copy, register
allocation for bytewise field decoding and offset-to-pointer results, loop
rotation, and duplicated forward-link decoding. The candidate has an extra
unconditional backward-loop branch at `0x08006CF0`; it is unreachable for the
stable-memory search invariant described below. These are genuine emitted
code differences, not an unsupported verifier feature.

## Bounded natural representations

All attempts used standard agbcc `-mthumb-interwork -O2`.

1. Ordinary private inline helpers decoded a little-endian unsigned halfword
   and an owner-relative pointer directly from its byte pair. A backward
   `do` loop and forward `while` loop produced 182 bytes / 91 instructions.
2. Widening the meaningful field-reader result to `u32`, without changing its
   byte-derived value, produced 218 bytes / 109 instructions. This was not
   retained.
3. A pre-tested backward loop with its initial upper candidate explicitly set
   produced 192 bytes / 96 instructions. This was not retained.
4. The retained header separates loading a little-endian halfword from
   decoding an already-loaded numeric offset. The main function retains the
   original `do`/`while` representation. It emits exactly the same 182-byte
   body as the first candidate.

The two private helpers represent genuinely repeated field and pointer
operations. Their original inline provenance is unknown. They have no forced
inline attributes, and no helper survives as a separate function. No compiler
flag sweep, register forcing, artificial control flow, volatile access,
packing, assembly, storage forcing or padding was used. These bounded
attempts do not establish that every possible natural source is unmatchable.

## Interface and ordered behavior

The compatible recovered interface is:

```
void func_08006C88(void *owner, u16 count, u8 **before, u8 **selected);
```

All four register arguments are consumed. The count uses only the low 16 bits;
there are no incoming stack arguments, helper calls or local frame. Both
bodies save r4-r7/LR, restore the preserved registers and return through the
saved LR. No meaningful scalar result is returned. Original nominal owner
and block types are not uniquely established.

The function first writes null through `selected`, then through `before`.
Only afterward does it read the owner's free-list starting offset from bytes
`+0x02` and `+0x03`, low byte first. Every encoded link is an unsigned
little-endian halfword: zero means null; otherwise the pointer is
`(u8 *)owner + 4 * offset`. No null or allocation guard is added.

A null initial block returns with just the two initialization stores. Otherwise
the block size is read bytewise at `+0x06/+0x07` and compared against the
narrowed count:

- If the initial size is at least the count, the search moves backward using
  link bytes `+0x08/+0x09`. It retains the previous candidate as the upper
  block, then tests the new lower block's size. When that lower size is below
  the count, it also reloads the upper block's size before accepting the pair.
- If the initial size is below the count, the search moves forward using
  link bytes `+0x0A/+0x0B`. At each step it rereads the lower block's size and,
  when that is below the count, reads the upper block's size. It stops on the
  bracket or a null upper pointer.

The observed repeated size reads and short-circuit ordering remain present;
they were not simplified using assumed list ordering. On the nonempty path,
the final stores are `before` first, then `selected`. Thus aliasing the two
output pointers leaves the selected pointer as the final value. There are no
other nonstack writes.

For a stable, properly linked size-ascending list, the outputs bracket the
first block whose size is at least `count`: its predecessor and that block.
Either endpoint can be null. Count zero is not rejected. This useful
interpretation does not turn malformed links or unsorted metadata into valid
allocator state, and the source does not add such validation.

## Author verification

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/08006C88-check/check_recovery.py`:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/08006C88-check/check_recovery.py
```

It freshly compiles this Parked C and private header in a disk-backed isolated
root with all current headers and frozen toolkit `a39dbf9`. It checks the one
complete ELF symbol and distinguishes both true extents before executing the
actual ROM body and complete candidate. No helper is stubbed or modeled;
neither body calls a helper.

- 139 pairs, or 278 executions, comprise 137 returning pairs and two cyclic
  pairs stopped at the 3,000-instruction budget. All arena/output/stack RAM is
  explicitly synthetic.
- Every returning execution agrees with a separate byte-operation oracle on
  exact ordered nonstack reads and writes and complete EWRAM. A separate
  sorted-list bracket calculation checks the pointer results independently
  of the search's traversal direction.
- Returning pairs also agree on all nonstack IWRAM, SP, return target and
  r4-r11. The incidental return-address value in r0 is checked as a machine
  effect, not advertised as a C scalar result. Instruction-fetch and stack
  traces are not claimed identical.
- Coverage is 87/87 target instructions and 90/91 candidate instructions.
  Candidate `0x08006CF0` follows the condition that both the new lower block
  and retained upper block are too small in the backward search. Its retained
  upper block is always large enough under stable memory, so that extra branch
  is not dynamically covered or claimed reachable in this domain.
- Cases cover empty and singleton lists; all starting positions in an
  eight-block list; ties; head/tail exhaustion; sizes and counts
  0/1/7/8/9/`0x0100`/`0xFFFF`; high incoming count bits; different link offsets;
  and nine cases with the two output arguments pointing to the same pointer
  object. Unrelated incoming registers vary across fixtures.
- The two deliberately cyclic link fixtures do not return in either body.
  Only the initial null-output stores occur, and both retain the same EWRAM.
  Finite budget observations are not a universal termination theorem or an
  assertion that arbitrary cyclic metadata is valid allocator state.

## Limits

The intended C domain requires live readable owner/block storage, valid
owner-relative pointer arithmetic within that storage, readable metadata bytes,
and aligned writable output-pointer objects. Tests use output storage disjoint
from arena metadata, apart from the explicitly tested equality of the two
outputs. They do not establish arbitrary output/header overlays, effective-type
legality for arbitrary RAM aliases, invalid pointers, MMIO, concurrent mutation,
allocator capacity, ownership or universal termination. No original allocation
bound or missing safety check was inferred.

The source/header remain Parked and contribute no active match or compiled-byte
credit. Further work would require a genuinely justified natural representation,
not a verifier change or acceptance of the extra candidate bytes.
