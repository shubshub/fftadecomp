# 0x08064DB4 — recovered, not matching

The retained ordinary C recovery is plausible and behaviorally corroborated,
but it does not reproduce the complete ROM bytes. It is not an active match.
There is no active source or saved match report for this address.

## Complete target and candidate

The complete target is `[0x08064DB4,0x08064E2C)`, 120 bytes / 47 reachable
instructions. Its code ranges are `[0x08064DB4,0x08064DD2)`,
`[0x08064DDC,0x08064E16)`, and `[0x08064E1C,0x08064E2C)`: 104 code bytes.
Two internal zero halfwords at 0x08064DD2 and 0x08064E16 are included.
Three referenced words are at 0x08064DD4 (`0x02000000`), 0x08064DD8
(`0x00003C28`), and 0x08064E18 (`0x020020D0`). No following function bytes
or external alignment are counted.

Target SHA-256:
`de098f143ecea09415f046577aaf9ba0bd9cf2e7d6584717e626b4f0c9c04dc4`.

The retained candidate has exactly one emitted FUNC and a 120-byte .text,
also containing 47 reachable instructions, 104 code bytes, three literal
words, and two internal zero halfwords. Its first code range ends at
0x08064DCE, first alignment is there, first two pool words are at
0x08064DD0/0x08064DD4, and code resumes at 0x08064DD8. The remaining
code/pool/alignment boundaries agree with the target.

Linked candidate SHA-256:
`c6b60260606a1ea41d02cfab2f4b55b5373833014a319dddb039a2b7df3a0984`.

Retained source SHA-256:
`e9dea29ac8739ed88f55a677ba3ecb319b7a74e8f581cbbe3bee16bf03be0fa0`.

Fresh frozen 4847c93 compilation, canonical typed linking, whole-symbol
extent validation, ordinary direct-call CFG checks, and plausibility pass.
The official verdict is **NOT MATCHING — bytes differ**, not an unsupported
profile or a short-symbol rejection for this retained form. Exactly 96/120
bytes agree at the same offsets and 37/47 instructions agree at the same
addresses. The tool's aligned presentation reports 107/120 bytes and 39/47
instructions; those are not positional equality counts.

The differences are category dispatch/block ordering and placement of the
first two literals. ROM tests category 1 with an equality branch, then uses
an unsigned range branch before the category-0 fallthrough. The candidate
uses an ordinary if/else equality chain. Every byte from 0x08064DE2 through
the end is identical, including the full later helper calls and return paths.

## Bounded natural attempts

1. An ordinary `switch` with cases 0, 1 and default produced 116 bytes / 47
   instructions. It put the default block first, used a different comparison
   order, and needed no internal zero halfwords. The complete-symbol gate
   rejected 116 < 120 before a match claim.
2. The retained `if (category == 1)`, `else if (category == 0)`, `else` form
   produces the full 120-byte / 47-instruction body described above. It keeps
   natural equality classification, all observed operations and helper calls.

No compiler flags, register variables, artificial case labels, forced storage,
alignment, volatile accesses, inline assembly, or extra control flow were
introduced. No byte-prefix comparison, padded symbol, or claimed exact match
was used to conceal the discrepancy.

## Interface and ordered behavior

A compatible interface is `u32 func_08064DB4(void)`. Locally it consumes no
incoming register or stack argument and returns full r0 = 13 or 14. That
range does not uniquely establish the original nominal return width or
exclude unused original formal parameters.

The local tagged `SelectionIndexView` matches the neighboring selection
caller's view; it reads the unsigned halfword at global `0x02000000 + 0x3C28`.
The opaque `extern u8 g_state_02000000[]` remains the existing binding form.
The target compiler confirms this view's member offset 0x3C28, size 0x3C2C,
and alignment 4, plus canonical `Record.field_04` at offset 4 and Record
size 16. These are grounded local views, not original type/allocation proofs.

1. Call `u32 func_080CE4DC(u16,u8)` with the index and selector 0x12.
   Compare the full returned word: 0 selects item 0x33/counter 1; 1 selects
   item 0x94/counter 2; every other value selects item 0x11E/counter 4.
2. Store the selected item as a full word at `0x020020D0 + 4` before calling
   `u8 func_080CB320(u16)`.
3. If the predicate's low byte is nonzero, call `u8 func_080C95A8(u16)` for
   the selected counter. Unless already 255, increment with byte narrowing
   and call the existing `void func_080C95C0(u16,u32)` boundary. Return 14.
4. Otherwise call `s32 func_080CA900(u16,u8)` with the item and quantity 1,
   ignore its result, and return 13, including when the inventory is full.

The selected real CE4DC field uses record bytes 0x10/0x11 and returns 0..255.
No byte narrowing is added to its established full-word declaration. CB320
continues past matching records with zero quantity, so a later nonzero
duplicate selects the counter path. CA900 instead updates the first matching
identifier, or the first empty record if none matches. Its byte wrap before
the upper-99 cap remains real helper behavior; no inventory invariant is
invented to simplify it.

Ordinary execution requires accessible fixed globals, an accessible selected
70-byte table row, the normal 361 four-byte inventory records, the observed
counter bytes, and a valid stack. No original table length, allocation,
unique-identifier, empty-record-quantity, concurrency, or general alias
invariant is asserted. This caller's three item IDs all select the normal
inventory bank. There is no allocator or engine callback in this selected
actual call chain. Ordinary direct-call verification is not a universal
transitive callee proof; CB320's separate standalone alias-join verifier
limitation is not bypassed or changed by this recovery.

## Fresh bounded behavior evidence

The retained reproducer performs 48 paired cases / 96 executions of the
actual target and freshly linked candidate. Every helper is actual ROM:
CE4DC's selector-0x12 dispatch/field path, CB320, CA900, C95A8 and C95C0.
No helper, allocator, callback, or engine result is modeled. There are 44
synthetic table-row fixtures and four pristine ROM-row slices; all RAM is
explicitly synthetic, not evidence of actual game allocation invariants.

Cases cover categories 0, 1, 2 and 255, counters 0/254/255, first/last matches,
matching zero quantities, later nonzero duplicates, all-zero duplicates,
first/last empty records, an exhausted bank, and empty-ID records with
quantities 99/255. Unrelated incoming registers vary. A separate byte-operation
oracle checks exact ordered state/table reads and writes, helper call arguments,
results, complete EWRAM, nonstack IWRAM, r4-r11 preservation, SP and return.

All 47/47 caller instructions execute on each side. Observed helper coverage
is 26 CE4DC instructions, 37/44 CB320, 94/106 CA900, and 8/8 for each counter
helper. Unused accessor selectors, zero-ID and special-bank paths are not
claimed as covered by these caller fixtures. Maximum measured stack depth is
36 bytes, including the real inventory adder; counter paths peak at 24 bytes.

All 48 complete nonstack read traces **differ** at the first two caller
literal loads because their pool addresses moved. State/table access traces,
all writes and calls are equal; after excluding only caller-pool reads, the
entire remaining nonstack event sequences agree. There is no blanket claim
of identical literal-inclusive read footprints, exhaustive behavior, or
universal helper-domain safety.

## Reproduction and cleanup

`/home/user/.codex-work/ffta-ulw/08064DB4-author/check_behavior.py` creates an
isolated disk-backed root with the current complete header set, current maps,
the parked source at its canonical source path, and a symlink to the existing
ROM. It runs the frozen official matcher with `--no-write`, repeats typed
compilation/linking and layout checks, then performs the paired executions.
Temporary roots, assembly, objects, ELF and raw binaries are self-cleaned.
Only the small reproducer and text log remain outside this parked directory.

No MATCH report or successful saved-report replay is claimed. The rejected
active diagnostic was removed together with the active source. Root owns
reservation release and any future publication or matching attempt.
