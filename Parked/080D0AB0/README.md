# 080D0AB0: filtered record-pointer collection, not a match

## Disposition and complete extents

The retained ordinary C recovery is plausible but not byte-identical. There is
no active source, private header, or successful match report for this address.
No intrinsic unmatchability or original-source provenance is claimed.

- Complete target: `[0x080D0AB0,0x080D0B48)`, 152 bytes / 67 instructions.
- Target code: `[0x080D0AB0,0x080D0B36)`, 134 bytes. The two zero bytes at
  `0x080D0B36` are internal alignment. Four literal words occupy
  `[0x080D0B38,0x080D0B48)`; there is no jump table.
- Target SHA-256:
  `b508e9d294d75e3a687b04d1379e3cfc5f0116b8d02b6c820ca1c6143957cde6`.
- Candidate: exactly one 144-byte `STT_FUNC`, 64 reachable instructions, and
  144-byte `.text`. Code ends at `0x080D0B30`; its four literal words occupy
  `[0x080D0B30,0x080D0B40)`. No extra outlined helper or veneer is present.
- Candidate typed-linked SHA-256:
  `c2f566a4f1bf0c770d60f512b7f3e95dc87d1757dc5e7e90b57c2b8e59cd0fee`.
- At identical addresses, 21 of the 144 overlapping bytes agree, 123 differ,
  and eight target bytes are absent. This is not a matching prefix.

The frozen `kit-reviewed-2e2a664` matcher rejects the complete compiled symbol
with `compiled symbol is shorter than the indexed span: 144 < 152`. Raw closed
CFG checks accept the actual target and diagnostic linked candidate separately;
strict scoped plausibility has no findings. The final ELF has no unresolved
symbols. These checks do not make the recovery a MATCH or a saved-report proof.

## Natural forms and remaining differences

The initial straightforward byte-view traversal, with the range test expressed
directly, emitted 144 bytes. Meaningful address-private inline operations for
the shared ten-bit ID and excluded-range calculation were also tried, using
ordinary `static inline` without forcing attributes. That form retained the
target's normalized Boolean range result but emitted 160 bytes / 71 instructions
and saved an additional high register. The unused private header was removed.

The retained direct form initializes the result count before reading the head.
It has the same 24-byte save footprint as the target, but the compiler collapses
the normalized range predicate to a direct branch and hoists the `0x400` mask
out of the loop. Register allocation, branch addresses, literal placement, and
alignment also differ. No compiler flags were varied, and no forced storage,
register, alignment, dummy control flow, volatile access, or assembly was used.

The definition flags are naturally assembled from two bytes. Both real loads
remain in the compiled body without forced reads, including the low byte whose
bits do not ultimately affect the mask test.

## Recovered interface and ordered behavior

The compatible interface is `u32(u8 **output, u32 limit)`. Only incoming R0 and
the full word in R1 are consumed; no incoming R2/R3 or stack argument is read.
All returning paths produce a full-word count. This does not uniquely establish
the original nominal pointer or integer typedefs. There are no calls or local
stack allocations, and the 24-byte saves preserve R4-R8 and return control.

The head pointer is loaded once from `0x02000000 + 0x28C8`. Each node supplies
a record pointer at offset zero and its next pointer at offset eight. The
previous-pointer slot at offset four is unused by this routine; its layout is
also observed in the related traversal recovery. The terminating nonnull node
is processed, unlike routines that deliberately exclude a sentinel node.

For each node, in order:

1. Read record bytes zero and one and form the ten-bit identifier
   `byte0 | ((byte1 & 3) << 8)`.
2. Reject identifiers in inclusive range `0x150..0x166`, using the observed
   low-16-bit subtraction test.
3. Otherwise read record byte two and reject any nonzero `byte2 & 0x1C`.
4. Otherwise read bytes `+0x41` then `+0x42` of the 70-byte definition selected
   by that identifier at `0x0855AE4C`. Combine them little-endian and reject
   flag `0x400`.
5. On acceptance, optionally store the record pointer to the output word and
   advance that pointer, increment the unsigned count, and stop if the count
   equals the full input limit.
6. Unless stopped, reload the node's next pointer after the optional output
   store and continue while it is nonnull.

A null head returns zero. A null output still performs counting and applies the
same post-increment limit test. A zero limit does not cause an initial return;
the equality can only become true after unsigned count wrap. The recovery does
not introduce a capacity check or an unconditional limit clamp. There are no
non-stack writes other than output words, but aliases can affect later reads;
the source intentionally preserves output-before-next-load ordering.

## Memory, type, and proof limits

The existing opaque `g_state_02000000` declaration is retained with a local
state view. The existing named binding for `g_table_0855AE4C` supplies an
unsized array of 70-byte rows. The target compiler independently gives Node
size 12/alignment 4, record/previous/next offsets 0/4/8, State head offset
`0x28C8`, and definition-row size 70. No packing or invented allocation length
is used. These access layouts do not prove the original nominal global type
or complete game allocation extents.

The C domain requires valid readable node, record, and definition elements;
aligned pointer-word accesses; and sufficient writable output storage when
output is nonnull. It does not promise arbitrary-alias safety, list ownership,
acyclicity, or termination. The original entry is supported here by the prior
function boundary, this prologue and complete CFG, and the following distinct
prologue at `0x080D0B48`, not by an independently established inbound reference.
The local CFG and named-data profile is supported; this attempt fails actual
code generation rather than an unsupported helper or verifier feature.

## Bounded execution evidence

168 returning fixtures were executed against both actual ROM and the freshly
compiled linked candidate, plus two paired instruction-budget cases: 340
executions in total. There are no helper calls or stubs. All RAM and list
records were synthetic; definition flag bytes were explicitly overlaid for
the tested identifiers, without changing function instructions or literals.

Every returning pair agrees with an independent ordered-access model on full
RAM, returned count, exact ordered reads and output stores, preserved R4-R11,
SP restoration, and return control. Instruction-literal fetches and the exact
24-byte save area are excluded from cross-binary data-trace comparison; the
remaining IWRAM is unchanged. Coverage is 67/67 target and 64/64 candidate
instructions.

Cases include ID-range boundaries and ten-bit masking, category and definition
flag bits, both definition-byte loads, empty and mixed lists, terminal-node
acceptance, null output, limits 0/1/2/3/4/`0x80000000`/`0xFFFFFFFF`, finite
positive-limit traversals of cyclic lists, and a byte-view overlap with output
storage whose subsequent read observes the stored pointer representation.
That last fixture is target-specific synthetic memory evidence, not a portable
pointer-representation or arbitrary-alias guarantee.

An eligible zero-limit cycle and an entirely excluded cycle did not return
within 10,000 instructions in either body. This is only budgeted evidence:
in particular, the eligible zero-limit cycle can reach the limit after
`2^32` acceptances. No finite trace equality or nontermination theorem is
claimed for those two runs.

The normal compiler recipe is `cpp -nostdinc -undef -I include`, unchanged
`agbcc -mthumb-interwork -O2`, then `arm-none-eabi-as -mthumb-interwork` and
typed absolute object bindings for the two named globals. Generated compiler,
ELF, probe, and emulator artifacts were removed after verification.
