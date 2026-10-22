# 080094BC — Parked, not a match

## Verdict

The complete ROM body is `[0x080094BC,0x080096B0)`: 500 bytes,
187 instructions, 382 code bytes, two 40-byte switch tables, eight literal
words and six internal zero-alignment bytes. The previous index stopped at
`0x080096A8`, omitting the reached literals at `0x080096A8` and `0x080096AC`.
The next indexed function really starts at `0x080096B0`; the parent linear
dump's introductory next-entry label was incorrect.

The natural source compiles with the fixed agbcc `-mthumb-interwork -O2`
flags to a complete **496-byte/189-instruction** function. A diagnostic-only
typed link at the original address differs in 366 positions over the full
500-byte comparison, including four missing tail bytes. The first difference
is offset zero: ROM `70b5` saves r4-r6/LR, while the candidate `f0b5` also
saves r7. Other differences include word-wide bitfield reads, a cached default
pointer, masks, branch offsets, table locations and literal placement. No
source/flag/register search was performed.

The unchanged approved toolkit separately exits 1 before emitting a report:
`call target must be an undefined addressed function`. The source uses the
canonical `memcpy`, not an addressed compiler-library alias. The four-byte
copy at `0x081443FC` is bound only in the diagnostic ELF/test harness.
A separate layout diagnostic on both the actual ROM and candidate also
rejects their two switches: `switch words must describe an adjacent table
and forward local cases`. The current profile supports one such table, not
this pair. Neither diagnostic is official verification, and the genuine byte
mismatch remains even without these profile exclusions. There is no MATCH
report and no successful-report strict replay claim.

## Recovered behavior

The two inputs are narrowed to unsigned bytes. A nonzero second input reads
a setting; zero changes it. The active state pointer is loaded from
`0x02009188`, with settings at state `+0x1BCC`. Settings occupy four bytes:

| Option | Field | Read/write meaning |
| --- | --- | --- |
| 0 | byte 2 bits 0-1 | two-bit value |
| 1 | byte 0 bit 0 | low bit of value |
| 2 | byte 0 bits 1-2 | two-bit value, then timing helper |
| 3 | byte 0 bits 3-4 | read boolean; write clears both and sets bit 3 if nonzero |
| 4 | byte 0 bit 6 | boolean |
| 5 | byte 1 bit 0 | boolean |
| 6 | byte 0 bit 7 | boolean |
| 7 | byte 1 bit 1 | boolean |
| 8 | byte 1 bits 2-4 | three-bit value |
| 9 | all four bytes | compare/reset against defaults `02 00 00 00` at `0x0851BA4E` |

Writes call `08017B68` on state `+0x2F0` and the signed byte at `+0x321`.
Its u16 result is converted to s16 before multiplying by four. The active
pointer is reloaded, then the selected byte is read at current state
`+0x338 + 4*index`, even for an out-of-range write option. Options 0-8 modify
the initially cached settings pointer. Option 9 returns 1 without a copy
when the selected byte is zero; otherwise it reloads the active pointer,
copies four default bytes to the current state's settings and returns 0.
Out-of-range reads return 0 without calling the clamp helper.

## Source and target-type limits

The first natural form is preserved in the disk evidence. Two correctness
repairs precede the final freeze: `memcpy`'s size argument uses `unsigned
long`, as the compiler's `ginclude/stddef.h` defines size_t, rather than the
project's incompatible `unsigned int` u32; the default-byte source is
`const u8 *`, not a 4-aligned `Settings *` at a merely 2-aligned address.
These repairs leave all 496 linked candidate bytes unchanged and remove the
built-in declaration warning. The only plausibility finding is the retained
`rom-address` suspect for the actual read-only default-byte pointer. No
allowlist or suppression was added.

Bitfield allocation is target/compiler-specific, not portable ISO C layout.
Fourteen compile-time assertions and thirteen independently checked aggregate
layout rows establish size 4, alignment 4, field positions and relevant
signed conversions for this compiler. A valid aligned live state/settings
object, compatible helper interfaces, and a backing allocation containing
every accessed slot remain source-level premises. Signed narrowing follows
this compiler; the scaled s16 index stays within int range. The index is not
unconditionally nonnegative: a zero limit can produce `0xFFFF`, then index
-1. No whole-game allocation or object-lifetime claim follows.

The candidate emits some **32-bit settings reads where ROM reads one byte**.
Tests therefore initialize all four aligned settings bytes. A negative
control removes definedness of byte 3: a ROM option-0 read still succeeds,
but the candidate is rejected on its wider read. Equivalence is not claimed
for partially initialized, misaligned, volatile/MMIO or concurrently changed
settings. Cached pointers and global reloads are preserved under the stated
returning-call assumptions; the rebind tests do not prove actual asynchronous
mutation or whole-game lifetime/separation.

## Evidence and reproduction

Disk evidence is under
`/home/user/.codex-work/ffta-ulw/080094BC-author/`.
`probe.py` constructs a private fixture from immutable `game-next-e299a92`,
copies all nine headers, applies only the proposed caller metadata repair,
and runs the unchanged `kit-software-double-candidate-v3` match command.
`probe.json` pins source, headers, both function maps, data map, tools,
compiler, ROM, default bytes and full helper bodies. `metadata.patch` is a
proposal only. No shared maps or production source were changed.

The original ELF has exactly four `R_ARM_THM_CALL` and 22 local-section
`R_ARM_ABS32` relocations (two table pointers and twenty case words). The
diagnostic link checks each typed Thumb target, each local word, complete
function extent, no veneers/stubs, no unresolved relocations and no changes
outside those relocation slots. Its full `.text` is the 496-byte function;
there is no external padding.

`check.py` freshly recompiles and passes 134 executions against a separately
written byte-mask/effect oracle: 126 execute every reached helper body
directly, while eight explicitly replace the entire clamp call with a model
that returns the chosen index and rebinds the active state. The other calls
remain actual in those eight runs. The model deliberately clobbers caller-
saved registers and flags, preserves callee-saved registers and SP, and is
not presented as the behavior of the actual clamp. The actual clamp does
not rebind the global.

All 187 ROM and 189 candidate instructions are reached. Actual-helper
coverage is `096B0:20/23`, `17B68:26/26`, `09920:26/26`, and
`1443FC:23/49` instructions. The compare's nonpositive-length path and
memcpy's bulk/aligned paths are outside the caller's fixed four-byte domain.
Eight negative controls detect scalar/mask changes, unsigned-index drift,
wrong copy length/return, missing selection initialization, the widened
settings read and a modeled callee-saved violation. An additional narrow-read
control confirms the ROM/candidate definedness distinction. Checks cover
exact helper arguments/returns, writes and preserved RAM, read initialization,
both return ISAs, saved r4-r11 and balanced SP. No BIOS model is used.

Run on a copy of the frozen evidence directory to keep its manifest intact:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 probe.py
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

Both scripts use self-cleaning disk fixtures and compare immutable inputs
again before reporting success. Generated object/ELF/assembly files are not
retained. This is a bounded Parked recovery, not a verified promotion or a
whole-project completion claim.
